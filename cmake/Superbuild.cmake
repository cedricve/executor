include( ExternalProject )

# --------------------------------------------------------------------------
# Look for GIT, check if it's installed

    find_package(Git)

    if(NOT GIT_FOUND)
      message(ERROR "Cannot find git. git is required for Executor")
    endif()

    option(USE_GIT_PROTOCOL ON)
    if(NOT USE_GIT_PROTOCOL)
      set(git_protocol "http")
    else()
      set(git_protocol "git")
    endif()


# --------------------------------------------------------------------------
# Testing with Googletest

    if(TESTS_ENABLED)
        include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/External-Googletest.cmake)
        set(TEST_DEPENDENCIES ${TEST_DEPENDENCIES} googletest)
    endif()