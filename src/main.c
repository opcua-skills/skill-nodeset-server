//
// Created by profanter on 30/07/2020.
// Copyright (c) 2020 fortiss GmbH. All rights reserved.
//

#include <stdbool.h>
#include <signal.h>
#include <stdio.h>

#include <open62541/plugin/log_stdout.h>
#include <open62541/server.h>
#include <open62541/server_config_default.h>

/* Files created by CMake from the nodeset */
#include "skill_nodeset_nodeids.h"
#include "skill_nodeset_example_nodeids.h"
#include "di_nodeids.h"
#include "my_company_nodeids.h"
#include "namespace_skill_nodeset_generated.h"
#include "namespace_skill_nodeset_example_generated.h"
#include "namespace_di_generated.h"
#include "namespace_my_company_generated.h"

static volatile UA_Boolean running = true;
static void stopHandler(int sig) {
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "received ctrl-c");
    running = false;
}

int main(
        int argc,
        char* argv[]
) {
    signal(SIGINT, stopHandler);
    signal(SIGTERM, stopHandler);
    signal(SIGUSR1, stopHandler);


    UA_Server *server = UA_Server_new();
    UA_ServerConfig_setDefault(UA_Server_getConfig(server));

    UA_StatusCode retval;
    /* create nodes from nodeset */
    if(namespace_skill_nodeset_generated(server) != UA_STATUSCODE_GOOD) {
        UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Could not add the skill nodeset. "
                                                           "Check previous output for any error.");
        retval = UA_STATUSCODE_BADUNEXPECTEDERROR;
    } else if(namespace_skill_nodeset_example_generated(server) != UA_STATUSCODE_GOOD) {
        UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Could not add the skill example nodeset. "
                                                           "Check previous output for any error.");
        retval = UA_STATUSCODE_BADUNEXPECTEDERROR;
    }  else if(namespace_di_generated(server) != UA_STATUSCODE_GOOD) {
        UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Could not add the DI nodeset. "
                                                           "Check previous output for any error.");
        retval = UA_STATUSCODE_BADUNEXPECTEDERROR;
    }  else if(namespace_my_company_generated(server) != UA_STATUSCODE_GOOD) {
        UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Could not add the MYCompany nodeset. "
                                                           "Check previous output for any error.");
        retval = UA_STATUSCODE_BADUNEXPECTEDERROR;
    } else {
        // Do some additional stuff with the nodes

        /*UA_UInt16 nsIdx = UA_Server_addNamespace(server, "http://yourorganisation.org/test/");

        UA_NodeId testInstanceId = UA_NODEID_NUMERIC(nsIdx, UA_EXAMPLE_NSID_TESTINSTANCE);

        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "The testInstance has ns=%d;id=%d",
                    testInstanceId.namespaceIndex, testInstanceId.identifier.numeric);*/

        retval = UA_Server_run(server, &running);
    }

    UA_Server_delete(server);
    return retval == UA_STATUSCODE_GOOD ? EXIT_SUCCESS : EXIT_FAILURE;
}