# ----------------------------------------------
# Add subdirectory

	include_directories(${CMAKE_SOURCE_DIR}/include/executor)
	add_subdirectory(executor)

# ----------------------------------------------
# Executable + define linking libraries

	SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
	add_executable(executor main.cpp)
	add_dependencies(executor ${DEPENDENCIES})
	target_link_libraries(executor ${LIBRARIES})

# -----------------------------------------
# Write variables to parent CMakeLists.txt

	SET(LIBRARIES ${LIBRARIES} PARENT_SCOPE)
	SET(DEPENDENCIES ${DEPENDENCIES} PARENT_SCOPE)
	SET(SRC ${SRC} PARENT_SCOPE)

#----------------------------------------
# Additional options

	SET(CMAKE_BUILD_TYPE Release)