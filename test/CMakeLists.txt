# ----------------------------------------------
# Get all files, starting with prefix "test_"

	FILE(GLOB TEST_SRC test_*.cpp)

# ----------------------------------------------
# Add subdirectory

	include_directories(${CMAKE_SOURCE_DIR}/include/executor)

# ----------------------------------------------
# Create test binary

	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
	set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/test/bin)
	add_executable(executor-test ${TEST_SRC})
	add_dependencies(executor-test ${TEST_DEPENDENCIES} ${DEPENDENCIES})
	target_link_libraries(executor-test ${LIBRARIES} ${GOOGLETEST_LIBRARIES})
	add_test(testing-executor ${CMAKE_SOURCE_DIR}/test/bin/executor-test)

# ----------------------------------------------
# Create make check command

	add_custom_target(check COMMAND executor-test)
	add_dependencies(check executor-test)
	add_test(test "${CMAKE_COMMAND}" --build ${CMAKE_BINARY_DIR} --target executor-test)

# ----------------------------------------------
# Execute script "GTEST..", create a test for each file

	include("${PROJECT_SOURCE_DIR}/test/script/gtest_add.cmake")
	gtest_add_tests("${EXECUTABLE_OUTPUT_PATH}/executor-test" "" ${TEST_SRC})