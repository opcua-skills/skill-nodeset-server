/* This Source Code Form is subject to the terms of the Apache
 * License, v. 2.0. If a copy of the Apache License was not distributed with this
 * file, You can obtain one at https://www.apache.org/licenses/LICENSE-2.0.
 *
 *    Copyright 2020 (c) Stefan Profanter, fortiss GmbH
 */


#ifndef PICK_SKILL_HPP
#define PICK_SKILL_HPP


#include <base/SkillBase.hpp>
#include "GraspSkill.hpp"
#include "MoveToAbsPosSkill.hpp"
#include <utility>

#define NAMESPACE_LIN_AXIS_GRIPPER "https://example.com/UA/Examples/LinearAxisWithGripper/"


namespace skill {

    using namespace base;

    class PickSkill : virtual public base::SkillBase {


    protected:
        const size_t nsDiIdx;
        const size_t nsLinAxisGripperId;
        GraspSkill *graspSkill;
        MoveToAbsPosSkill *moveToAbsPosSkill;

    public:

        explicit PickSkill(
                const std::shared_ptr<skill::OpcUaServer>&  _server,
                const UA_NodeId& skillNodeId,
                const std::string& eventSourceName,
                GraspSkill *graspSkill,
                MoveToAbsPosSkill *moveToAbsPosSkill
        ) :
                SkillBase(_server, skillNodeId, eventSourceName),
                nsDiIdx(UA_Server_getNamespaceIdByName(server, NAMESPACE_URI_DI)),
                nsLinAxisGripperId(UA_Server_getNamespaceIdByName(server, NAMESPACE_LIN_AXIS_GRIPPER)),
                graspSkill(graspSkill),
                moveToAbsPosSkill(moveToAbsPosSkill) {
            // use dynamic cast to make sure polymorphic resolution is correct
            auto selfProgram = dynamic_cast<Program*>(this);

            {
                LockedServer ls = server->getLocked();
                if (UA_Server_setNodeContext(ls.get(), skillNodeId, selfProgram) != UA_STATUSCODE_GOOD) {
                    throw std::runtime_error("Adding method context failed");
                }
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
                    &UA_TYPES[UA_TYPES_DOUBLE],
                    &UA_TYPES[UA_TYPES_DOUBLE]
            };
            if (!checkInputArguments(server->getLogger(), inputSize, input, 2, expected))
                return UA_STATUSCODE_BADINVALIDARGUMENT;

            // Cast the input arguments
            double span = *(UA_Double*)input[0].data;
            double position = *(UA_Double*)input[0].data;

            UA_LOG_INFO(server->getLogger(), UA_LOGCATEGORY_USERLAND,
                        "--> PickSkill - Start: span = %f, position = %f", span, position);

            // start long-running execution in new thread to not block the main server loop.
            // This callback is still in the main server loop.
            std::thread t = std::thread([this, span, position]() {

                pick(span, position);

                UA_LOG_INFO(server->getLogger(), UA_LOGCATEGORY_USERLAND,
                            "--> PickSkill - finished");

                if (!transition(ProgramStateNumber::READY)) {
                    UA_LOG_ERROR(server->getLogger(), UA_LOGCATEGORY_USERLAND, "Failed to make transition after skill execution finished");
                }
            });
            t.detach();

            return UA_STATUSCODE_GOOD;
        }

        void pick(double span, double position) {
            moveToAbsPosSkill->moveToPositionWithTransitions(position);
            graspSkill->graspWithTransitions(span, 0.5);
        }

    };
}


#endif //PICK_SKILL_HPP
