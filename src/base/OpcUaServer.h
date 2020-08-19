/* This Source Code Form is subject to the terms of the Apache
 * License, v. 2.0. If a copy of the Apache License was not distributed with this
 * file, You can obtain one at https://www.apache.org/licenses/LICENSE-2.0.
 *
 *    Copyright 2020 (c) Stefan Profanter, fortiss GmbH
 */


#ifndef SKILLS_OPCUASERVER_H
#define SKILLS_OPCUASERVER_H

#ifdef UA_ENABLE_AMALGAMATION
#include "open62541.h"
#else

#include <open62541/server.h>

#endif

#include <base/synchronized.hpp>

// use recursive mutex to allow multiple locks within the same thread, but not between different threads
typedef locked_ptr<UA_Server, std::recursive_mutex> LockedServer;
UNUSED_ATTR typedef synchronized<UA_Server> MutexedServer;

namespace skill {

        class OpcUaServer {
        private:
            std::recursive_mutex serverMutex;
        protected:


            UA_Server* server = nullptr;

        public:

            explicit OpcUaServer(
                    UA_Server* server
            ): server(server) {

            }


            virtual ~OpcUaServer() = default;

            void iterate(bool waitInternal = false) {
                std::lock_guard<std::recursive_mutex> lc(serverMutex);
                UA_Server_run_iterate(server, waitInternal);
            }

            LockedServer getLocked() {
                return LockedServer{server, serverMutex};
            }

            UA_Logger* getLogger() {
                return &UA_Server_getConfig(server)->logger;
        };
    };
}


#endif //SKILLS_OPCUASERVER_H
