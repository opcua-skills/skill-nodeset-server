/* This Source Code Form is subject to the terms of the Apache
 * License, v. 2.0. If a copy of the Apache License was not distributed with this
 * file, You can obtain one at https://www.apache.org/licenses/LICENSE-2.0.
 *
 *    Copyright 2020 (c) Stefan Profanter, fortiss GmbH
 */


#ifndef SKILLS_OPCUA_SKILL_BASE_H
#define SKILLS_OPCUA_SKILL_BASE_H
#pragma once

#include <utility>
#include <future>
#include <memory>
#include <vector>
#include "Program.hpp"
#include "helper.hpp"
#include "skills_nodeids.h"

#define NAMESPACE_URI_SKILLS "http://opcfoundation.org/UA/Skills/"

namespace skill {

    namespace base {

        class SkillBase : public Program {
        private:

            std::function<void()> implDeleter = nullptr;

        public:
            explicit SkillBase(
                    const std::shared_ptr<skill::OpcUaServer>& _server,
                    const UA_NodeId& skillNodeId,
                    const std::string& eventSourceName
            ) :
                    Program(generateStates(_server),
                            generateTransitions(_server),
                            _server,
                            *UA_Server_getObjectComponentId(_server, skillNodeId,
                                                            UA_QUALIFIEDNAME(UA_Server_getNamespaceIdByName(_server, NAMESPACE_URI_SKILLS),
                                                                             const_cast<char*>("StateMachine"))),
                            eventSourceName),
                    nsSkillsId(UA_Server_getNamespaceIdByName(server, NAMESPACE_URI_SKILLS)),
                    skillTransitionEventTypeId(UA_NODEID_NUMERIC(nsSkillsId, UA_SKILLSID_SKILLSTATETRANSITIONEVENTTYPE)) {
                // halted state location
                currentState = &states[0];

                // default value to avoid segfaults due to being null
                lastTransition = &transitions[0];
            }

            ~SkillBase() override {
                if (implDeleter != nullptr)
                    implDeleter();
            };

            bool transition(ProgramStateNumber nextState) override {
                return Program::transition(nextState, skillTransitionEventTypeId);
            }

        protected:
            const size_t nsSkillsId;
            const UA_NodeId skillTransitionEventTypeId;

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
                return UA_STATUSCODE_BADNOTIMPLEMENTED;
            }

            UA_StatusCode resumeMethod(
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
                return UA_STATUSCODE_BADNOTIMPLEMENTED;
            }

            UA_StatusCode resetMethod(
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
                return UA_STATUSCODE_BADNOTIMPLEMENTED;
            }

            UA_StatusCode haltMethod(
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
                return UA_STATUSCODE_BADNOTIMPLEMENTED;
            }

            UA_StatusCode suspendMethod(
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
                return UA_STATUSCODE_BADNOTIMPLEMENTED;
            }

        private:
            static std::vector<ProgramState> generateStates(const std::shared_ptr<skill::OpcUaServer>& server) {
                LockedServer ls = server->getLocked();

                return {ProgramState(ProgramStateNumber::HALTED,
                                     UA_Server_getObjectComponentId(ls.get(), UA_NODEID_NUMERIC(0, UA_NS0ID_PROGRAMSTATEMACHINETYPE),
                                                                    UA_QUALIFIEDNAME(0, const_cast<char*>("Halted"))),
                                     UA_LOCALIZEDTEXT(const_cast<char*>("en-US"), const_cast<char*>("Halted"))),
                        ProgramState(ProgramStateNumber::READY,
                                     UA_Server_getObjectComponentId(ls.get(), UA_NODEID_NUMERIC(0, UA_NS0ID_PROGRAMSTATEMACHINETYPE),
                                                                    UA_QUALIFIEDNAME(0, const_cast<char*>("Ready"))),
                                     UA_LOCALIZEDTEXT(const_cast<char*>("en-US"), const_cast<char*>("Ready"))),
                        ProgramState(ProgramStateNumber::RUNNING,
                                     UA_Server_getObjectComponentId(ls.get(), UA_NODEID_NUMERIC(0, UA_NS0ID_PROGRAMSTATEMACHINETYPE),
                                                                    UA_QUALIFIEDNAME(0, const_cast<char*>("Running"))),
                                     UA_LOCALIZEDTEXT(const_cast<char*>("en-US"), const_cast<char*>("Running"))),
                        ProgramState(ProgramStateNumber::SUSPENDED,
                                     UA_Server_getObjectComponentId(ls.get(), UA_NODEID_NUMERIC(0, UA_NS0ID_PROGRAMSTATEMACHINETYPE),
                                                                    UA_QUALIFIEDNAME(0, const_cast<char*>("Suspended"))),
                                     UA_LOCALIZEDTEXT(const_cast<char*>("en-US"), const_cast<char*>("Suspended")))};
            }

            static std::vector<ProgramTransition>
            generateTransitions(const std::shared_ptr<skill::OpcUaServer>& server) {

                LockedServer ls = server->getLocked();
                return {ProgramTransition(ProgramTransitionNumber::HALTED_TO_READY,
                                          UA_Server_getObjectComponentId(ls.get(), UA_NODEID_NUMERIC(0, UA_NS0ID_PROGRAMSTATEMACHINETYPE),
                                                                         UA_QUALIFIEDNAME(0,
                                                                                          const_cast<char*>("HaltedToReady"))),
                                          UA_LOCALIZEDTEXT(const_cast<char*>("en-US"), const_cast<char*>("Halted to Ready")),
                                          ProgramStateNumber::HALTED, ProgramStateNumber::READY),
                        ProgramTransition(ProgramTransitionNumber::READY_TO_RUNNING,
                                          UA_Server_getObjectComponentId(ls.get(), UA_NODEID_NUMERIC(0, UA_NS0ID_PROGRAMSTATEMACHINETYPE),
                                                                         UA_QUALIFIEDNAME(0,
                                                                                          const_cast<char*>("ReadyToRunning"))),
                                          UA_LOCALIZEDTEXT(const_cast<char*>("en-US"), const_cast<char*>("Ready to Running")),
                                          ProgramStateNumber::READY, ProgramStateNumber::RUNNING),
                        ProgramTransition(ProgramTransitionNumber::RUNNING_TO_HALTED,
                                          UA_Server_getObjectComponentId(ls.get(), UA_NODEID_NUMERIC(0, UA_NS0ID_PROGRAMSTATEMACHINETYPE),
                                                                         UA_QUALIFIEDNAME(0,
                                                                                          const_cast<char*>("RunningToHalted"))),
                                          UA_LOCALIZEDTEXT(const_cast<char*>("en-US"), const_cast<char*>("Running to Halted")),
                                          ProgramStateNumber::RUNNING, ProgramStateNumber::HALTED),
                        ProgramTransition(ProgramTransitionNumber::RUNNING_TO_READY,
                                          UA_Server_getObjectComponentId(ls.get(), UA_NODEID_NUMERIC(0, UA_NS0ID_PROGRAMSTATEMACHINETYPE),
                                                                         UA_QUALIFIEDNAME(0,
                                                                                          const_cast<char*>("RunningToReady"))),
                                          UA_LOCALIZEDTEXT(const_cast<char*>("en-US"), const_cast<char*>("Running to Ready")),
                                          ProgramStateNumber::RUNNING, ProgramStateNumber::READY),
                        ProgramTransition(ProgramTransitionNumber::RUNNING_TO_SUSPENDED,
                                          UA_Server_getObjectComponentId(ls.get(), UA_NODEID_NUMERIC(0, UA_NS0ID_PROGRAMSTATEMACHINETYPE),
                                                                         UA_QUALIFIEDNAME(0,
                                                                                          const_cast<char*>("RunningToSuspended"))),
                                          UA_LOCALIZEDTEXT(const_cast<char*>("en-US"),
                                                           const_cast<char*>("Running to Suspended")),
                                          ProgramStateNumber::RUNNING, ProgramStateNumber::SUSPENDED),
                        ProgramTransition(ProgramTransitionNumber::SUSPENDED_TO_RUNNING,
                                          UA_Server_getObjectComponentId(ls.get(), UA_NODEID_NUMERIC(0, UA_NS0ID_PROGRAMSTATEMACHINETYPE),
                                                                         UA_QUALIFIEDNAME(0,
                                                                                          const_cast<char*>("SuspendedToRunning"))),
                                          UA_LOCALIZEDTEXT(const_cast<char*>("en-US"),
                                                           const_cast<char*>("Suspended to Running")),
                                          ProgramStateNumber::SUSPENDED, ProgramStateNumber::RUNNING),
                        ProgramTransition(ProgramTransitionNumber::SUSPENDED_TO_HALTED,
                                          UA_Server_getObjectComponentId(ls.get(), UA_NODEID_NUMERIC(0, UA_NS0ID_PROGRAMSTATEMACHINETYPE),
                                                                         UA_QUALIFIEDNAME(0,
                                                                                          const_cast<char*>("SuspendedToHalted"))),
                                          UA_LOCALIZEDTEXT(const_cast<char*>("en-US"),
                                                           const_cast<char*>("Suspended to Halted")),
                                          ProgramStateNumber::SUSPENDED, ProgramStateNumber::HALTED),
                        ProgramTransition(ProgramTransitionNumber::SUSPENDED_TO_READY,
                                          UA_Server_getObjectComponentId(ls.get(), UA_NODEID_NUMERIC(0, UA_NS0ID_PROGRAMSTATEMACHINETYPE),
                                                                         UA_QUALIFIEDNAME(0,
                                                                                          const_cast<char*>("SuspendedToReady"))),
                                          UA_LOCALIZEDTEXT(const_cast<char*>("en-US"), const_cast<char*>("Suspended to Ready")),
                                          ProgramStateNumber::SUSPENDED, ProgramStateNumber::READY),
                        ProgramTransition(ProgramTransitionNumber::READY_TO_HALTED,
                                          UA_Server_getObjectComponentId(ls.get(), UA_NODEID_NUMERIC(0, UA_NS0ID_PROGRAMSTATEMACHINETYPE),
                                                                         UA_QUALIFIEDNAME(0,
                                                                                          const_cast<char*>("ReadyToHalted"))),
                                          UA_LOCALIZEDTEXT(const_cast<char*>("en-US"), const_cast<char*>("Ready to Halted")),
                                          ProgramStateNumber::READY, ProgramStateNumber::HALTED)};
            }

        };


    }
}

#endif //SKILLS_OPCUA_SKILL_BASE_H
