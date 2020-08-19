/* This Source Code Form is subject to the terms of the Apache
 * License, v. 2.0. If a copy of the Apache License was not distributed with this
 * file, You can obtain one at https://www.apache.org/licenses/LICENSE-2.0.
 *
 *    Copyright 2020 (c) Stefan Profanter, fortiss GmbH
 */


#ifndef SKILLS_OPCUA_PROGRAMSTATE_H
#define SKILLS_OPCUA_PROGRAMSTATE_H
#pragma once

#include <utility>
#include <map>
#include <memory>

#ifdef UA_ENABLE_AMALGAMATION
#include "open62541.h"
#else

#include <open62541/types.h>

#endif

namespace skill {

    namespace base {

        enum class ProgramStateNumber : UA_UInt32 {
            INVALID = 0,
            HALTED = 11,
            READY = 12,
            RUNNING = 13,
            SUSPENDED = 14
        };

        const std::map<ProgramStateNumber, std::string> ProgramStateName = {
                {ProgramStateNumber::INVALID,   "INVALID"},
                {ProgramStateNumber::HALTED,    "HALTED"},
                {ProgramStateNumber::READY,     "READY"},
                {ProgramStateNumber::RUNNING,   "RUNNING"},
                {ProgramStateNumber::SUSPENDED, "SUSPENDED"},
        };

        class ProgramState {
        public:
            ProgramState() = delete;

            explicit ProgramState(
                    const ProgramStateNumber number,
                    std::shared_ptr<UA_NodeId> id,
                    const UA_LocalizedText name
            )
                    : number(number), id(std::move(id)), name(name) {
            };

            UA_LocalizedText getName() const { return name; };

            const UA_NodeId* getId() const { return id.get(); };

            ProgramStateNumber getNumber() const { return number; };

        private:
            const ProgramStateNumber number;
            const std::shared_ptr<UA_NodeId> id;
            const UA_LocalizedText name;
        };
    }
}

#endif //SKILLS_OPCUA_PROGRAMSTATE_H
