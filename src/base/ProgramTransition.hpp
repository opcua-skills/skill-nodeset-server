/* This Source Code Form is subject to the terms of the Apache
 * License, v. 2.0. If a copy of the Apache License was not distributed with this
 * file, You can obtain one at https://www.apache.org/licenses/LICENSE-2.0.
 *
 *    Copyright 2020 (c) Stefan Profanter, fortiss GmbH
 */

#include <utility>

#include <utility>

#ifndef SKILLS_OPCUA_PROGRAMTRANSITION_H
#define SKILLS_OPCUA_PROGRAMTRANSITION_H
#pragma once

#include "ProgramState.hpp"


namespace skill {

    namespace base {

        enum class ProgramTransitionNumber {
            HALTED_TO_READY = 1,
            READY_TO_RUNNING = 2,
            RUNNING_TO_HALTED = 3,
            RUNNING_TO_READY = 4,
            RUNNING_TO_SUSPENDED = 5,
            SUSPENDED_TO_RUNNING = 6,
            SUSPENDED_TO_HALTED = 7,
            SUSPENDED_TO_READY = 8,
            READY_TO_HALTED = 9,
        };

        class ProgramTransition {
        public:
            explicit ProgramTransition(
                    const ProgramTransitionNumber number,
                    std::shared_ptr<UA_NodeId> id,
                    const UA_LocalizedText name,
                    ProgramStateNumber from,
                    ProgramStateNumber to
            ) : number(number),
                id(std::move(id)),
                name(name),
                from(from), to(to) {};

            UA_LocalizedText getName() const { return name; };

            const UA_NodeId* getId() const { return id.get(); };

            ProgramTransitionNumber getNumber() const { return number; };

            ProgramStateNumber getFrom() const { return from; };

            ProgramStateNumber getTo() const { return to; };

        private:
            const ProgramTransitionNumber number;
            const std::shared_ptr<UA_NodeId> id;
            const UA_LocalizedText name;
            const ProgramStateNumber from;
            const ProgramStateNumber to;

        };
    }
}

#endif //SKILLS_OPCUA_PROGRAMTRANSITION_H
