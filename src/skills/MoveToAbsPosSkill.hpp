/* This Source Code Form is subject to the terms of the Apache
 * License, v. 2.0. If a copy of the Apache License was not distributed with this
 * file, You can obtain one at https://www.apache.org/licenses/LICENSE-2.0.
 *
 *    Copyright 2020 (c) Stefan Profanter, fortiss GmbH
 */


#ifndef MoveToAbsPos_SKILL_HPP
#define MoveToAbsPos_SKILL_HPP


#include <base/SkillBase.hpp>
#include <utility>

#include <skills_example_nodeids.h>
#define NAMESPACE_LIN_AXIS_GRIPPER "https://example.com/UA/Examples/LinearAxisWithGripper/"


namespace skill {

    using namespace base;

    class MoveToAbsPosSkill : virtual public base::SkillBase {

    private:
        double currentPosition = 0;

    protected:
        const size_t nsDiIdx;
        const size_t nsLinAxisGripperId;

        UA_StatusCode setCurrentPositionOutputParam(UA_Double position) {
            currentPosition = position;
            UA_NodeId currentPosId = UA_NODEID_NUMERIC(nsLinAxisGripperId,
                                                       UA_SKILLS_EXAMPLEID_LINAXISWITHGRIPPER_SKILLS_MOVETOABSPOSSKILL_STATEMACHINE_RUNNING_CONTINUOUSPARAMETER_OUTPUTPARAMETER_CURRENTPOSITION);

            UA_Variant v;
            UA_Variant_init(&v);
            UA_Variant_setScalar(&v, &position, &UA_TYPES[UA_TYPES_DOUBLE]);
            LockedServer ls = server->getLocked();
            return UA_Server_writeValue(ls.get(), currentPosId, v);
        }

    public:

        explicit MoveToAbsPosSkill(
                const std::shared_ptr<skill::OpcUaServer>&  _server,
                const UA_NodeId& skillNodeId,
                const std::string& eventSourceName
        ) :
                SkillBase(_server, skillNodeId, eventSourceName),
                nsDiIdx(UA_Server_getNamespaceIdByName(server, NAMESPACE_URI_DI)),
                nsLinAxisGripperId(UA_Server_getNamespaceIdByName(server, NAMESPACE_LIN_AXIS_GRIPPER)) {
            // use dynamic cast to make sure polymorphic resolution is correct
            auto selfProgram = dynamic_cast<Program*>(this);

            {
                LockedServer ls = server->getLocked();
                if (UA_Server_setNodeContext(ls.get(), skillNodeId, selfProgram) != UA_STATUSCODE_GOOD) {
                    throw std::runtime_error("Adding method context failed");
                }
            }

            UA_StatusCode retval = setCurrentPositionOutputParam(0);
            if (retval != UA_STATUSCODE_GOOD) {
                throw std::runtime_error("Cannot set current position output param: " + std::string(UA_StatusCode_name(retval)));
            }
            if (!SkillBase::transition(ProgramStateNumber::READY)) {
                UA_LOG_ERROR(server->getLogger(), UA_LOGCATEGORY_USERLAND, "Failed to make transition after skill init");
            }
        }


        UA_StatusCode startMethod(
                const UA_NodeId* sessionId,
                void* sessionHandle,
                const UA_NodeId* methodId,
                void* methodContext,
                const UA_NodeId* objectId,
                void* objectContext,
                size_t inputSize,
                const UA_Variant* input,
                size_t outputSize,
                UA_Variant* output
        ) override {

            // Check if the input arguments are correct
            const UA_DataType* expected[] = {
                    &UA_TYPES[UA_TYPES_DOUBLE]
            };
            if (!checkInputArguments(server->getLogger(), inputSize, input, 1, expected))
                return UA_STATUSCODE_BADINVALIDARGUMENT;

            // Cast the input arguments
            double position = *(UA_Double*)input[0].data;

            UA_LOG_INFO(server->getLogger(), UA_LOGCATEGORY_USERLAND,
                        "--> MoveToAbsPosSkill - Start: position = %f", position);


            UA_StatusCode retval = setCurrentPositionOutputParam(0);
            if (retval != UA_STATUSCODE_GOOD)
                return retval;
            // start long-running execution in new thread to not block the main server loop.
            // This callback is still in the main server loop.
            std::thread t = std::thread([this, position]() {

                moveToPosition(position);

                UA_LOG_INFO(server->getLogger(), UA_LOGCATEGORY_USERLAND,
                            "--> MoveToAbsPosSkill - finished");

                if (!transition(ProgramStateNumber::READY)) {
                    UA_LOG_ERROR(server->getLogger(), UA_LOGCATEGORY_USERLAND, "Failed to make transition after skill execution finished");
                }
            });
            t.detach();

            return UA_STATUSCODE_GOOD;
        }

        void moveToPosition(double position) {
            // we simulate 100 steps
            double stepSize = (position - currentPosition)/100.0;

            // simulate axis movement by increasing the current position in 100 steps and waiting a bit
            for (size_t i=0; i<100; i++) {
                UA_StatusCode retval = setCurrentPositionOutputParam(currentPosition + stepSize);
                if (retval != UA_STATUSCODE_GOOD) {
                    UA_LOG_ERROR(server->getLogger(), UA_LOGCATEGORY_USERLAND, "Cannot set current position output param: %s", UA_StatusCode_name(retval));
                    break;
                }
                UA_LOG_INFO(server->getLogger(), UA_LOGCATEGORY_USERLAND,
                            "--> MoveToAbsPosSkill - Position: %f", currentPosition);
                std::this_thread::sleep_for(std::chrono::milliseconds(20));
            }
        }

        bool moveToPositionWithTransitions(double position) {
            if (!transition(ProgramStateNumber::RUNNING)) {
                UA_LOG_ERROR(server->getLogger(), UA_LOGCATEGORY_USERLAND, "Failed to make transition before skill execution");
                return false;
            }

            UA_LOG_INFO(server->getLogger(), UA_LOGCATEGORY_USERLAND,
                        "--> MoveToAbsPosSkill - Start: position = %f", position);

            moveToPosition(position);

            UA_LOG_INFO(server->getLogger(), UA_LOGCATEGORY_USERLAND,
                        "--> MoveToAbsPosSkill - finished");
            if (!transition(ProgramStateNumber::READY)) {
                UA_LOG_ERROR(server->getLogger(), UA_LOGCATEGORY_USERLAND, "Failed to make transition after skill execution finished");
                return false;
            }
            return true;
        }

    };
}


#endif //MoveToAbsPos_SKILL_HPP
