############################## Subfolders #####################################
# --- Policies table test
#add_subdirectory(./policies_manager)

if (BUILD_TESTS_WITH_HMI)
  add_subdirectory(./rpc)
endif()

###############################################################################

include_directories (
  ../../../src/thirdPartyLibs/gmock-1.7.0/include
  ../../../src/thirdPartyLibs/gmock-1.7.0/gtest/include
  ../../../src/components/application_manager/include
  ../../../src/components/smart_objects/include
  ../../../src/components/formatters/include/
  ../../../src/components/utils/include/
  ../../../src//thirdPartyLibs/jsoncpp/include/
    ${CMAKE_BINARY_DIR}/src/components/
)

set(LIBRARIES
    gtest
    gtest_main
    gmock
    gmock_main
    ApplicationManager
    formatters
    jsoncpp
    MOBILE_API
    HMI_API
    SmartObjects
    apr-1
    aprutil-1
)

#create_test("test_APIVersionConverterV1Test" "./api_converter_v1_test.cpp" "${LIBRARIES}")
create_test("test_formatters_commands" "./formatters_commands.cc" "${LIBRARIES}")
#create_test("test_schema_factory_test" "./schema_factory_test.cc" "${LIBRARIES}")
add_library("test_FormattersCommandsTest" "./formatters_commands.cc")
