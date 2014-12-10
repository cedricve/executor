# @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
# Build library

set(SRC
	Executor.cpp)

add_library(EXECUTOR_LIBRARY ${SRC})
set(DEPENDENCIES ${DEPENDENCIES} EXECUTOR_LIBRARY)
set(LIBRARIES ${LIBRARIES} EXECUTOR_LIBRARY)

# -------------------------------------------
# Write variables to parent CMakeLists.txt

set(SRC ${SRC} PARENT_SCOPE)
set(DEPENDENCIES ${DEPENDENCIES} PARENT_SCOPE)
set(LIBRARIES ${LIBRARIES} PARENT_SCOPE)