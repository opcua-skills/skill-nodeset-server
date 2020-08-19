/* This Source Code Form is subject to the terms of the Apache
 * License, v. 2.0. If a copy of the Apache License was not distributed with this
 * file, You can obtain one at https://www.apache.org/licenses/LICENSE-2.0.
 *
 *    Copyright 2020 (c) Stefan Profanter, fortiss GmbH
 */



#ifndef ROBOTICS_COMMON_OPCUA_HELPER_H
#define ROBOTICS_COMMON_OPCUA_HELPER_H
#pragma once

#include <future>
#include <utility>

#ifdef UA_ENABLE_AMALGAMATION
#include "open62541.h"
#else

#include <open62541/server_config_default.h>
#include <open62541/client.h>
#include <open62541/plugin/pki_default.h>
#include <open62541/plugin/accesscontrol_default.h>

#if ((UA_OPEN62541_VER_MAJOR >= 1) && (UA_OPEN62541_VER_MINOR >= 1))

#include <open62541/plugin/nodestore_default.h>

#endif


#if ((UA_OPEN62541_VER_MAJOR >= 1) && (UA_OPEN62541_VER_MINOR >= 1))

#include <open62541/plugin/nodestore_default.h>

#endif

#include <open62541/client_config_default.h>

#endif


#include <exception>
#include <sstream>

#define NAMESPACE_URI_DI "http://opcfoundation.org/UA/DI/"

#define UNUSED_ATTR __attribute__((unused))

#include <map>
#include <set>
#include "OpcUaServer.h"

namespace skill {

    namespace base {
        class NodeNotFoundException : public std::exception {
        private:
            std::string message_;
        public:
            explicit NodeNotFoundException(
                    const std::string& nodeId,
                    const std::string& additionalInfo = ""
            ) {
                message_ = "OPC UA NodeNotFound Exception: " + nodeId;

                if (additionalInfo.length())
                    message_ += " " + additionalInfo;
            }

            const char* what() const noexcept override {
                return message_.c_str();
            }
        };

        inline UA_StatusCode
        UA_ServerConfig_setUriName(
                UA_ServerConfig* uaServerConfig,
                const char* uri,
                const char* name
        ) {
            // delete pre-initialized values
            UA_String_deleteMembers(&uaServerConfig->applicationDescription.applicationUri);
            UA_LocalizedText_deleteMembers(&uaServerConfig->applicationDescription.applicationName);

            std::string opcUaUri(uri);
            std::string opcUaName(name);

            uaServerConfig->applicationDescription.applicationUri = UA_String_fromChars(opcUaUri.c_str());
            uaServerConfig->applicationDescription.applicationName.locale = UA_STRING_NULL;
            uaServerConfig->applicationDescription.applicationName.text = UA_String_fromChars(opcUaName.c_str());

            for (size_t i = 0; i < uaServerConfig->endpointsSize; i++) {
                UA_String_deleteMembers(&uaServerConfig->endpoints[i].server.applicationUri);
                UA_LocalizedText_deleteMembers(
                        &uaServerConfig->endpoints[i].server.applicationName);

                UA_String_copy(&uaServerConfig->applicationDescription.applicationUri,
                               &uaServerConfig->endpoints[i].server.applicationUri);

                UA_LocalizedText_copy(&uaServerConfig->applicationDescription.applicationName,
                                      &uaServerConfig->endpoints[i].server.applicationName);
            }

            return UA_STATUSCODE_GOOD;
        }

        inline std::shared_ptr<UA_NodeId> UA_Server_getObjectChildId(
                UA_Server* server,
                const UA_NodeId objectId,
                const UA_QualifiedName childName,
                const UA_NodeId reference
        ) {
            UA_RelativePathElement rpe;
            UA_RelativePathElement_init(&rpe);
            rpe.referenceTypeId = reference;
            rpe.isInverse = false;
            rpe.includeSubtypes = false;
            rpe.targetName = childName;

            UA_BrowsePath bp;
            UA_BrowsePath_init(&bp);
            bp.startingNode = objectId;
            bp.relativePath.elementsSize = 1;
            bp.relativePath.elements = &rpe;

            UA_StatusCode retval;
            UA_BrowsePathResult bpr = UA_Server_translateBrowsePathToNodeIds(server, &bp);
            retval = bpr.statusCode;
            if (retval != UA_STATUSCODE_GOOD || bpr.targetsSize < 1) {
                UA_BrowsePathResult_deleteMembers(&bpr);
                std::string qualifiedName = "ns=" + std::to_string(childName.namespaceIndex) + ";"
                                            + std::string(reinterpret_cast<char const*>(childName.name.data),
                                                          childName.name.length);
                std::string errorMessage = std::string(UA_StatusCode_name(retval));
                throw NodeNotFoundException(qualifiedName, errorMessage);
            }

            UA_NodeId* nodeId = UA_NodeId_new();

            UA_NodeId_copy(&bpr.targets[0].targetId.nodeId, nodeId);

            UA_BrowsePathResult_deleteMembers(&bpr);

            return std::shared_ptr<UA_NodeId>(nodeId, UA_NodeId_delete);
        }

        inline std::shared_ptr<UA_NodeId> UA_Server_getObjectChildId(
                const std::shared_ptr<OpcUaServer>& uaServer,
                const UA_NodeId objectId,
                const UA_QualifiedName childName,
                const UA_NodeId reference
        ) {
            LockedServer ls = uaServer->getLocked();
            return UA_Server_getObjectChildId(ls.get(), objectId, childName, reference);

        }

        inline std::shared_ptr<UA_NodeId>
        UA_Server_getObjectComponentId(
                UA_Server* server,
                const UA_NodeId objectId,
                const UA_QualifiedName componentName
        ) {
            return UA_Server_getObjectChildId(server, objectId, componentName,
                                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT));
        }

        inline std::shared_ptr<UA_NodeId>
        UA_Server_getObjectComponentId(
                const std::shared_ptr<OpcUaServer>& uaServer,
                const UA_NodeId objectId,
                const UA_QualifiedName componentName
        ) {
            return UA_Server_getObjectChildId(uaServer, objectId, componentName,
                                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT));
        }

        inline std::shared_ptr<UA_NodeId>
        UA_Server_getObjectComponentId_or_Null(
                UA_Server* server,
                const UA_NodeId objectId,
                const UA_QualifiedName componentName
        ) {
            try {
                return UA_Server_getObjectChildId(server, objectId, componentName,
                                                  UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT));
            } catch (NodeNotFoundException& ex) {
                return nullptr;
            }
        }


        inline std::shared_ptr<UA_NodeId>
        UA_Server_getObjectPropertyId(
                UA_Server* server,
                const UA_NodeId objectId,
                const UA_QualifiedName propertyName
        ) {
            return UA_Server_getObjectChildId(server, objectId, propertyName,
                                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASPROPERTY));
        }

        inline std::shared_ptr<UA_NodeId>
        UA_Server_getObjectPropertyId(
                const std::shared_ptr<OpcUaServer>& uaServer,
                const UA_NodeId objectId,
                const UA_QualifiedName propertyName
        ) {
            return UA_Server_getObjectChildId(uaServer, objectId, propertyName,
                                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASPROPERTY));
        }

        bool checkInputArguments(
                UA_Logger* logger,
                size_t inputSize,
                const UA_Variant* input,
                size_t expectedSize,
                const UA_DataType* expectedTypes[]
        ) {
            if (inputSize != expectedSize) {
                UA_LOG_WARNING(logger, UA_LOGCATEGORY_USERLAND, "Given input argument count does not match expected count %zu != %zu", inputSize, expectedSize);
                return false;
            }
            for (size_t i = 0; i < inputSize; i++) {
                if (input[i].type != expectedTypes[i]) {
                    UA_LOG_WARNING(logger, UA_LOGCATEGORY_USERLAND, "Given input argument %lu is not of expected type %s != %s", i + 1,
                                   input[i].type->typeName,
                                   expectedTypes[i]->typeName);
                    return false;
                }
            }
            return true;
        }

        inline UA_UInt16 UA_Server_getNamespaceIdByName(
                UA_Server* uaServer,
                const char* nsid
        ) {
            size_t nsIdTmp = 0;
            UA_String nsUri = UA_String_fromChars(nsid);
            UA_StatusCode retval = UA_Server_getNamespaceByName(uaServer, nsUri, &nsIdTmp);
            UA_String_clear(&nsUri);
            if (retval != UA_STATUSCODE_GOOD) {
                throw std::runtime_error("Could not find server namespace: " + std::string(nsid));
            }
            return (UA_UInt16) nsIdTmp;
        }

        inline UA_UInt16 UA_Server_getNamespaceIdByName(
                const std::shared_ptr<OpcUaServer>& uaServer,
                const char* nsid
        ) {
            LockedServer ls = uaServer->getLocked();
            return UA_Server_getNamespaceIdByName(ls.get(), nsid);
        }

    }
}


#endif //ROBOTICS_COMMON_OPCUA_HELPER_H
