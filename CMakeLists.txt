cmake_minimum_required( VERSION 2.8.3 )
project(Executor)


# ----------------------------------------------
# Enable tests

	set(TESTS_ENABLED 0)
	if(TESTS_ENABLED)
		include(CTest)
	endif()
	
# ----------------------------------------------
# Variables

	set(DEPENDENCIES "")
	set(TEST_DEPENDENCIES "")
	set(LIBRARIES "")
	set(SRC "")

# ----------------------------------------------
# Build all the dependencies

	include(cmake/Superbuild.cmake)

# ----------------------------------------------
# Link source and tests (if enabled)

	add_subdirectory(src)
	if(TESTS_ENABLED)
		add_subdirectory(test)
	endif()