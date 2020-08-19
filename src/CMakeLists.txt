
add_definitions(
        -Wall
        -Wcast-qual
        -Werror
        -Wextra
        -Wformat
        -Wformat-security
        -Winit-self
        -Wmultichar
        -Wno-overlength-strings
        -Wno-unused-parameter
        -Wpointer-arith
        -Wstrict-overflow
        -Wuninitialized
        -fPIC
        -fvisibility=hidden
        -Wno-ignored-qualifiers
        -Wno-sign-conversion
        -pipe)

set(GENERATE_OUTPUT_DIR "${CMAKE_BINARY_DIR}/src_generated/")

file(MAKE_DIRECTORY "${GENERATE_OUTPUT_DIR}")
include_directories("${GENERATE_OUTPUT_DIR}")
include_directories("${CMAKE_CURRENT_LIST_DIR}")

ua_generate_nodeset_and_datatypes(
        NAME "skills"
        TARGET_PREFIX "${PROJECT_NAME}"
        FILE_CSV "${PROJECT_SOURCE_DIR}/deps/skill-nodeset/Published/Skills/Opc.Ua.Skills/SkillsModel.csv"
        FILE_BSD "${PROJECT_SOURCE_DIR}/deps/skill-nodeset/Published/Skills/Opc.Ua.Skills/Opc.Ua.Skills.Types.bsd"
        OUTPUT_DIR "${GENERATE_OUTPUT_DIR}"
        NAMESPACE_IDX 2
        FILE_NS "${PROJECT_SOURCE_DIR}/deps/skill-nodeset/Published/Skills/Opc.Ua.Skills/Opc.Ua.Skills.NodeSet2.xml"
        INTERNAL
)

ua_generate_nodeset_and_datatypes(
        NAME "di"
        TARGET_PREFIX "${PROJECT_NAME}"
        FILE_CSV "${open62541_NODESET_DIR}/DI/OpcUaDiModel.csv"
        FILE_BSD "${open62541_NODESET_DIR}/DI/Opc.Ua.Di.Types.bsd"
        OUTPUT_DIR "${GENERATE_OUTPUT_DIR}"
        NAMESPACE_IDX 3
        FILE_NS "${open62541_NODESET_DIR}/DI/Opc.Ua.Di.NodeSet2.xml"
        INTERNAL
)

ua_generate_nodeset_and_datatypes(
        NAME "skills_example"
        TARGET_PREFIX "${PROJECT_NAME}"
        FILE_CSV "${PROJECT_SOURCE_DIR}/deps/skill-nodeset/Published/LinearAxisWithGripper/Example.LinearAxisWithGripper/LinearAxisWithGripperModel.csv"
        FILE_BSD "${PROJECT_SOURCE_DIR}/deps/skill-nodeset/Published/LinearAxisWithGripper/Example.LinearAxisWithGripper/Example.LinearAxisWithGripper.Types.bsd"
        OUTPUT_DIR "${GENERATE_OUTPUT_DIR}"
        NAMESPACE_IDX 4
        FILE_NS "${PROJECT_SOURCE_DIR}/deps/skill-nodeset/Published/LinearAxisWithGripper/Example.LinearAxisWithGripper/Example.LinearAxisWithGripper.NodeSet2.xml"
        DEPENDS "skills" "di"
        INTERNAL
)



add_executable(nodeset-example-server
               ${UA_NODESET_SKILLS_SOURCES}
               ${UA_TYPES_SKILLS_SOURCES}
               ${UA_NODESET_SKILLS_EXAMPLE_SOURCES}
               ${UA_TYPES_SKILLS_EXAMPLE_SOURCES}
               ${UA_NODESET_DI_SOURCES}
               ${UA_TYPES_DI_SOURCES}
               main.cpp
               base/helper.hpp
               base/FiniteStateMachine.hpp
               base/ProgramState.hpp
               base/ProgramTransition.hpp
               base/Program.hpp
               base/SkillBase.hpp
               skills/GraspSkill.hpp
               )

add_dependencies(nodeset-example-server
                 ${PROJECT_NAME}-ns-skills_example
                 )

target_link_libraries(nodeset-example-server open62541::open62541)