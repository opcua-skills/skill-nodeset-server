/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 *
 *    Copyright (c) 2020 fortiss GmbH, Stefan Profanter
 *    All rights reserved.
 */

#include <utility>

#include <utility>

#include <utility>

#ifndef SKILLS_OPCUA_PROGRAM_H
#define SKILLS_OPCUA_PROGRAM_H
#pragma once

#ifdef UA_ENABLE_AMALGAMATION
#include "open62541.h"
#else

#include <open62541/server.h>

#endif

#ifndef UA_ENABLE_SUBSCRIPTIONS_EVENTS
#error open62541 Events are required
#endif

#include <algorithm>
#include <vector>
#include "helper.hpp"
#include "FiniteStateMachine.hpp"
#include "ProgramState.hpp"
#include "ProgramTransition.hpp"

namespace skill {

    namespace base {

        class Program : public FiniteStateMachine {
        public:


            explicit Program(
                    const std::vector<ProgramState>& states,
                    const std::vector<ProgramTransition>& transitions,
                    std::shared_ptr<skill::OpcUaServer> _server,
                    const UA_NodeId& stateMachineNodeId,
                    const std::string& eventSourceName
            )
                    : FiniteStateMachine(states, transitions, std::move(_server), stateMachineNodeId, eventSourceName) {

                LockedServer ls = server->getLocked();
                UA_QualifiedName stateMachineBrowseName;
                UA_Server_readBrowseName(ls.get(), stateMachineNodeId, &stateMachineBrowseName);


                // Add data sources
                std::shared_ptr<UA_NodeId> currentStateNodeId =
                        UA_Server_getObjectComponentId(ls.get(), stateMachineNodeId,
                                                       UA_QUALIFIEDNAME(0, const_cast<char*>("CurrentState")));


                UA_DataSource dataSource{};
                UA_StatusCode retval;
                dataSource.write = nullptr;
                dataSource.read = Program::readCurrentStateNumber;
                std::shared_ptr<UA_NodeId> currentStateNumberNodeId =
                        UA_Server_getObjectPropertyId(ls.get(), *currentStateNodeId,
                                                      UA_QUALIFIEDNAME(0, const_cast<char*>("Id")));
                UA_Server_setNodeContext(ls.get(), *currentStateNumberNodeId, this);
                retval = UA_Server_setVariableNode_dataSource(ls.get(),
                                                              *currentStateNumberNodeId,
                                                              dataSource);
                if (retval != UA_STATUSCODE_GOOD) {
                    throw std::runtime_error("Adding data sources failed");
                }

                std::shared_ptr<UA_NodeId> lastTransitionNodeId =
                        UA_Server_getObjectComponentId(ls.get(), stateMachineNodeId,
                                                       UA_QUALIFIEDNAME(0, const_cast<char*>("LastTransition")));
                dataSource.read = Program::readLastTransitionNumber;
                std::shared_ptr<UA_NodeId> lastTransitionNumberNodeId =
                        UA_Server_getObjectPropertyId(ls.get(), *lastTransitionNodeId,
                                                      UA_QUALIFIEDNAME(0, const_cast<char*>("Id")));
                UA_Server_setNodeContext(ls.get(), *lastTransitionNumberNodeId, this);
                retval = UA_Server_setVariableNode_dataSource(ls.get(), *lastTransitionNumberNodeId,
                                                              dataSource);
                if (retval != UA_STATUSCODE_GOOD) {
                    throw std::runtime_error("Adding data sources failed");
                }

                dataSource.read = Program::readLastTransitionTime;
                std::shared_ptr<UA_NodeId> lastTransitionTimeNodeId =
                        UA_Server_getObjectPropertyId(ls.get(), *lastTransitionNodeId,
                                                      UA_QUALIFIEDNAME(0, const_cast<char*>("TransitionTime")));
                UA_Server_setNodeContext(ls.get(), *lastTransitionTimeNodeId, this);
                retval = UA_Server_setVariableNode_dataSource(ls.get(), *lastTransitionTimeNodeId,
                                                              dataSource);
                if (retval != UA_STATUSCODE_GOOD) {
                    throw std::runtime_error("Adding data sources failed");
                }

                // add method callback
                retval = UA_Server_setMethodNode_callback(ls.get(),
                                                          *(UA_Server_getObjectComponentId(ls.get(), stateMachineNodeId,
                                                                                           UA_QUALIFIEDNAME(stateMachineBrowseName.namespaceIndex,
                                                                                                            const_cast<char*>("Start")))),
                                                          &Program::startMethodCallback);
                if (retval != UA_STATUSCODE_GOOD) {
                    throw std::runtime_error("Adding start method failed");
                }
                retval = UA_Server_setMethodNode_callback(ls.get(),
                                                          *(UA_Server_getObjectComponentId(ls.get(), stateMachineNodeId,
                                                                                           UA_QUALIFIEDNAME(stateMachineBrowseName.namespaceIndex,
                                                                                                            const_cast<char*>("Reset")))),
                                                          &Program::resetMethodCallback);
                if (retval != UA_STATUSCODE_GOOD) {
                    throw std::runtime_error("Adding reset method failed");
                }

                retval = UA_Server_setMethodNode_callback(ls.get(),
                                                          *(UA_Server_getObjectComponentId(ls.get(), stateMachineNodeId,
                                                                                           UA_QUALIFIEDNAME(stateMachineBrowseName.namespaceIndex,
                                                                                                            const_cast<char*>("Suspend")))),
                                                          &Program::suspendMethodCallback);
                if (retval != UA_STATUSCODE_GOOD) {
                    throw std::runtime_error("Adding suspend method failed");
                }

                retval = UA_Server_setMethodNode_callback(ls.get(),
                                                          *(UA_Server_getObjectComponentId(ls.get(), stateMachineNodeId,
                                                                                           UA_QUALIFIEDNAME(stateMachineBrowseName.namespaceIndex,
                                                                                                            const_cast<char*>("Resume")))),
                                                          &Program::resumeMethodCallback);
                if (retval != UA_STATUSCODE_GOOD) {
                    throw std::runtime_error("Adding resume method failed");
                }
                retval = UA_Server_setMethodNode_callback(ls.get(),
                                                          *(UA_Server_getObjectComponentId(ls.get(), stateMachineNodeId,
                                                                                           UA_QUALIFIEDNAME(stateMachineBrowseName.namespaceIndex,
                                                                                                            const_cast<char*>("Halt")))),
                                                          &Program::haltMethodCallback);
                if (retval != UA_STATUSCODE_GOOD) {
                    throw std::runtime_error("Adding halt method failed");
                }
            }

            ~Program() override = default;

            UA_UtcTime getLastTransitionTime() const { return lastTransitionTime; }

            static UA_StatusCode readCurrentStateNumber(
                    UNUSED_ATTR UA_Server* server,
                    UNUSED_ATTR const UA_NodeId* sessionId,
                    UNUSED_ATTR void* sessionContext,
                    UNUSED_ATTR const UA_NodeId* nodeId,
                    void* nodeContext,
                    UNUSED_ATTR UA_Boolean sourceTimeStamp,
                    UNUSED_ATTR const UA_NumericRange* range,
                    UA_DataValue* dataValue
            ) {
                if (!nodeContext)
                    return UA_STATUSCODE_BADINTERNALERROR;
                auto* self = static_cast<Program*>(nodeContext);
                auto stateNumber = static_cast<UA_UInt32>(self->getCurrentState()->getNumber());
                UA_Variant_setScalarCopy(&dataValue->value, &stateNumber, &UA_TYPES[UA_TYPES_UINT32]);
                dataValue->hasValue = true;
                return UA_STATUSCODE_GOOD;
            }

            static UA_StatusCode readLastTransitionNumber(
                    UNUSED_ATTR UA_Server* server,
                    UNUSED_ATTR const UA_NodeId* sessionId,
                    UNUSED_ATTR void* sessionContext,
                    UNUSED_ATTR const UA_NodeId* nodeId,
                    void* nodeContext,
                    UNUSED_ATTR UA_Boolean sourceTimeStamp,
                    UNUSED_ATTR const UA_NumericRange* range,
                    UA_DataValue* dataValue
            ) {
                if (!nodeContext)
                    return UA_STATUSCODE_BADINTERNALERROR;
                auto* self = static_cast<Program*>(nodeContext);
                auto transitionNum = self->getLastTransition()->getNumber();
                UA_Variant_setScalarCopy(&dataValue->value, &transitionNum, &UA_TYPES[UA_TYPES_UINT32]);
                dataValue->hasValue = true;
                return UA_STATUSCODE_GOOD;
            }

            static UA_StatusCode readLastTransitionTime(
                    UNUSED_ATTR UA_Server* server,
                    UNUSED_ATTR const UA_NodeId* sessionId,
                    UNUSED_ATTR void* sessionContext,
                    UNUSED_ATTR const UA_NodeId* nodeId,
                    void* nodeContext,
                    UNUSED_ATTR UA_Boolean sourceTimeStamp,
                    UNUSED_ATTR const UA_NumericRange* range,
                    UA_DataValue* dataValue
            ) {
                if (!nodeContext)
                    return UA_STATUSCODE_BADINTERNALERROR;
                auto* self = static_cast<Program*>(nodeContext);
                UA_UtcTime lastTransitionTime = self->getLastTransitionTime();
                UA_Variant_setScalarCopy(&dataValue->value, &lastTransitionTime,
                                         &UA_TYPES[UA_TYPES_UTCTIME]);
                dataValue->hasValue = true;
                return UA_STATUSCODE_GOOD;
            }


        protected:

            UA_UtcTime lastTransitionTime = 0;

            virtual UA_StatusCode startMethod(
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
            ) = 0;

            virtual UA_StatusCode resumeMethod(
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
            ) = 0;

            virtual UA_StatusCode resetMethod(
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
            ) = 0;

            virtual UA_StatusCode haltMethod(
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
            ) = 0;

            virtual UA_StatusCode suspendMethod(
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
            ) = 0;

        private:
            bool isTransitionAllowed(
                    ProgramStateNumber from,
                    ProgramStateNumber to,
                    bool log = false
            ) const {
                for (const auto& transition : transitions) {
                    if ((transition.getFrom() == from) && (transition.getTo() == to))
                        return true;
                }
                if (log)
                    UA_LOG_WARNING(server->getLogger(), UA_LOGCATEGORY_USERLAND,
                                   "Transition not allowed: %s -> %s",
                                   ProgramStateName.at(from).c_str(),
                                   ProgramStateName.at(to).c_str());
                return false;
            }

            static UA_StatusCode startMethodCallback(
                    UNUSED_ATTR UA_Server* server,
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
            ) {
                if (!objectContext)
                    return UA_STATUSCODE_BADINTERNALERROR;
                auto* self = static_cast<Program*>(objectContext);

                if (!self->isTransitionAllowed(self->getCurrentState()->getNumber(), ProgramStateNumber::RUNNING,
                                               true)) {
                    return UA_STATUSCODE_BADSTATENOTACTIVE;
                }


                UA_StatusCode retVal = self->startMethod(sessionId, sessionHandle,
                                                         methodId, methodContext,
                                                         objectId, objectContext,
                                                         inputSize, input,
                                                         outputSize, output);
                if (retVal != UA_STATUSCODE_GOOD) {
                    return retVal;
                }

                if (!self->transition(ProgramStateNumber::RUNNING)) {
                    return UA_STATUSCODE_BADSTATENOTACTIVE;
                }

                return UA_STATUSCODE_GOOD;
            }


            static UA_StatusCode resetMethodCallback(
                    UNUSED_ATTR UA_Server* server,
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
            ) {
                if (!objectContext)
                    return UA_STATUSCODE_BADINTERNALERROR;
                auto* self = static_cast<Program*>(objectContext);

                if (!self->isTransitionAllowed(self->getCurrentState()->getNumber(), ProgramStateNumber::READY, true)) {
                    return UA_STATUSCODE_BADSTATENOTACTIVE;
                }

                UA_StatusCode retVal = self->resetMethod(sessionId, sessionHandle,
                                                         methodId, methodContext,
                                                         objectId, objectContext,
                                                         inputSize, input,
                                                         outputSize, output);
                if (retVal != UA_STATUSCODE_GOOD) {
                    return retVal;
                }

                if (!self->transition(ProgramStateNumber::READY)) {
                    return UA_STATUSCODE_BADSTATENOTACTIVE;
                }

                return UA_STATUSCODE_GOOD;
            }


            static UA_StatusCode haltMethodCallback(
                    UNUSED_ATTR UA_Server* server,
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
            ) {
                if (!objectContext)
                    return UA_STATUSCODE_BADINTERNALERROR;
                auto* self = static_cast<Program*>(objectContext);

                if (!self->isTransitionAllowed(self->getCurrentState()->getNumber(), ProgramStateNumber::HALTED,
                                               true)) {
                    return UA_STATUSCODE_BADSTATENOTACTIVE;
                }

                UA_StatusCode retVal = self->haltMethod(sessionId, sessionHandle,
                                                        methodId, methodContext,
                                                        objectId, objectContext,
                                                        inputSize, input,
                                                        outputSize, output);
                if (retVal != UA_STATUSCODE_GOOD) {
                    return retVal;
                }

                if (!self->transition(ProgramStateNumber::HALTED)) {
                    return UA_STATUSCODE_BADSTATENOTACTIVE;
                }

                return UA_STATUSCODE_GOOD;
            }

            static UA_StatusCode suspendMethodCallback(
                    UNUSED_ATTR UA_Server* server,
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
            ) {
                if (!objectContext)
                    return UA_STATUSCODE_BADINTERNALERROR;
                auto* self = static_cast<Program*>(objectContext);

                if (!self->isTransitionAllowed(self->getCurrentState()->getNumber(), ProgramStateNumber::SUSPENDED,
                                               true)) {
                    return UA_STATUSCODE_BADSTATENOTACTIVE;
                }

                UA_StatusCode retVal = self->suspendMethod(sessionId, sessionHandle,
                                                           methodId, methodContext,
                                                           objectId, objectContext,
                                                           inputSize, input,
                                                           outputSize, output);
                if (retVal != UA_STATUSCODE_GOOD) {
                    return retVal;
                }

                if (!self->transition(ProgramStateNumber::SUSPENDED)) {
                    return UA_STATUSCODE_BADSTATENOTACTIVE;
                }

                return UA_STATUSCODE_GOOD;
            }

            static UA_StatusCode resumeMethodCallback(
                    UNUSED_ATTR UA_Server* server,
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
            ) {
                if (!objectContext)
                    return UA_STATUSCODE_BADINTERNALERROR;
                auto* self = static_cast<Program*>(objectContext);

                if (!self->isTransitionAllowed(self->getCurrentState()->getNumber(), ProgramStateNumber::RUNNING,
                                               true)) {
                    return UA_STATUSCODE_BADSTATENOTACTIVE;
                }

                UA_StatusCode retVal = self->resumeMethod(sessionId, sessionHandle,
                                                          methodId, methodContext,
                                                          objectId, objectContext,
                                                          inputSize, input,
                                                          outputSize, output);
                if (retVal != UA_STATUSCODE_GOOD) {
                    return retVal;
                }

                if (!self->transition(ProgramStateNumber::RUNNING)) {
                    return UA_STATUSCODE_BADSTATENOTACTIVE;
                }

                return UA_STATUSCODE_GOOD;
            }

        };
    }
}


#endif //SKILLS_OPCUA_PROGRAM_H
