/* This Source Code Form is subject to the terms of the Apache
 * License, v. 2.0. If a copy of the Apache License was not distributed with this
 * file, You can obtain one at https://www.apache.org/licenses/LICENSE-2.0.
 *
 *    Copyright 2020 (c) Stefan Profanter, fortiss GmbH
 */


#include <csignal>

#include <open62541/plugin/log_stdout.h>
#include <open62541/server.h>
#include <open62541/server_config_default.h>
#include <skills/ReleaseSkill.hpp>
#include <skills/MoveToAbsPosSkill.hpp>
#include <skills/PickSkill.hpp>

/* Files created by CMake from the nodeset */
#include "skills_example_nodeids.h"
#include "namespace_skills_generated.h"
#include "namespace_skills_example_generated.h"
#include "namespace_di_generated.h"

#include "skills/GraspSkill.hpp"

static volatile UA_Boolean running = true;

static void stopHandler(UNUSED_ATTR int sig) {
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


    UA_Server* server = UA_Server_new();
    UA_ServerConfig_setDefault(UA_Server_getConfig(server));

    UA_StatusCode retval;
    /* create nodes from nodeset */
    if (namespace_skills_generated(server) != UA_STATUSCODE_GOOD) {
        UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Could not add the skill nodeset. "
                                                           "Check previous output for any error.");
        retval = UA_STATUSCODE_BADUNEXPECTEDERROR;
    } else if (namespace_di_generated(server) != UA_STATUSCODE_GOOD) {
        UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Could not add the DI nodeset. "
                                                           "Check previous output for any error.");
        retval = UA_STATUSCODE_BADUNEXPECTEDERROR;
    } else if (namespace_skills_example_generated(server) != UA_STATUSCODE_GOOD) {
        UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Could not add the skill example nodeset. "
                                                           "Check previous output for any error.");
        retval = UA_STATUSCODE_BADUNEXPECTEDERROR;
    } else {
        // Do some additional stuff with the nodes

        /*UA_UInt16 nsIdx = UA_Server_addNamespace(server, "http://yourorganisation.org/test/");

        UA_NodeId testInstanceId = UA_NODEID_NUMERIC(nsIdx, UA_EXAMPLE_NSID_TESTINSTANCE);

        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "The testInstance has ns=%d;id=%d",
                    testInstanceId.namespaceIndex, testInstanceId.identifier.numeric);*/

        skill::UA_ServerConfig_setUriName(UA_Server_getConfig(server),
                                          "skill.example.linear-axis",
                                          "Skills Example - Linear Axis");

        std::shared_ptr<skill::OpcUaServer> uaServer = std::make_shared<skill::OpcUaServer>(server);

        skill::GraspSkill graspSkill(uaServer,
                                     UA_NODEID_NUMERIC(
                                             skill::UA_Server_getNamespaceIdByName(uaServer, NAMESPACE_LIN_AXIS_GRIPPER),
                                             UA_SKILLS_EXAMPLEID_LINAXISWITHGRIPPER_SKILLS_GRASPSKILL
                                     ),
                                     "Grasp"
        );

        skill::ReleaseSkill releaseSkill(uaServer,
                                     UA_NODEID_NUMERIC(
                                             skill::UA_Server_getNamespaceIdByName(uaServer, NAMESPACE_LIN_AXIS_GRIPPER),
                                             UA_SKILLS_EXAMPLEID_LINAXISWITHGRIPPER_SKILLS_RELEASESKILL
                                     ),
                                     "Release"
        );

        skill::MoveToAbsPosSkill moveToAbsPosSkill(uaServer,
                                     UA_NODEID_NUMERIC(
                                             skill::UA_Server_getNamespaceIdByName(uaServer, NAMESPACE_LIN_AXIS_GRIPPER),
                                             UA_SKILLS_EXAMPLEID_LINAXISWITHGRIPPER_SKILLS_MOVETOABSPOSSKILL
                                     ),
                                     "MoveToAbsPos"
        );

        skill::PickSkill pickSkill(uaServer,
                                     UA_NODEID_NUMERIC(
                                             skill::UA_Server_getNamespaceIdByName(uaServer, NAMESPACE_LIN_AXIS_GRIPPER),
                                             UA_SKILLS_EXAMPLEID_LINAXISWITHGRIPPER_SKILLS_PICKSKILL
                                     ),
                                     "Pick",
                                     &graspSkill,
                                     &moveToAbsPosSkill
        );


        if ((retval = UA_Server_run_startup(server)) != UA_STATUSCODE_GOOD) {
            UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Cannot startup server: %s", UA_StatusCode_name(retval));
        }

        while (running) {
            uaServer->iterate();
        }

        if ((retval = UA_Server_run_shutdown(server)) != UA_STATUSCODE_GOOD) {
            UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Cannot shutdown server: %s", UA_StatusCode_name(retval));
        }
    }

    UA_Server_delete(server);
    return retval == UA_STATUSCODE_GOOD ? EXIT_SUCCESS : EXIT_FAILURE;
}