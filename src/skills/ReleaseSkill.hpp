/* This Source Code Form is subject to the terms of the Apache
 * License, v. 2.0. If a copy of the Apache License was not distributed with this
 * file, You can obtain one at https://www.apache.org/licenses/LICENSE-2.0.
 *
 *    Copyright 2020 (c) Stefan Profanter, fortiss GmbH
 */


#ifndef RELEASE_SKILL_HPP
#define RELEASE_SKILL_HPP


#include <base/SkillBase.hpp>
#include <utility>

#define NAMESPACE_LIN_AXIS_GRIPPER "https://example.com/UA/Examples/LinearAxisWithGripper/"


namespace skill {

    using namespace base;

    class ReleaseSkill : virtual public base::SkillBase {


    protected:
        const size_t nsDiIdx;
        const size_t nsLinAxisGripperId;

    public:

        explicit ReleaseSkill(
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
            double span = *(UA_Double*)input[0].data;

            UA_LOG_INFO(server->getLogger(), UA_LOGCATEGORY_USERLAND,
                        "--> ReleaseSkill - Start: span = %f", span);

            // start long-running execution in new thread to not block the main server loop.
            // This callback is still in the main server loop.
            std::thread t = std::thread([this, span]() {

                release(span);

                UA_LOG_INFO(server->getLogger(), UA_LOGCATEGORY_USERLAND,
                            "--> ReleaseSkill - finished");

                if (!transition(ProgramStateNumber::READY)) {
                    UA_LOG_ERROR(server->getLogger(), UA_LOGCATEGORY_USERLAND, "Failed to make transition after skill execution finished");
                }
            });
            t.detach();

            return UA_STATUSCODE_GOOD;
        }

        void release(double span) {
            // just sleep for a second. Normally you would here now control the gripper
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

    };
}


#endif //RELEASE_SKILL_HPP
