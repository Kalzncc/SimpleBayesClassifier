cmake_minimum_required(VERSION 3.0.0)
project(Bayes_classifier VERSION 0.1.0)

include(CTest)
enable_testing()



add_compile_options(-D__DEBUG)


# aux_source_directory(src/tools TOOLS_FILES)
# add_library(TOOLS_LIB ${TOOLS_FILES})

# aux_source_directory(src/func_lib FUNC_FILES)
# add_library(FUNC_LIB ${FUNC_FILES})

# aux_source_directory(src/_debug DEBUG_FILES)
# add_library(DEBUG_LIB ${DEBUG_FILES})

aux_source_directory(src SRC_FILE)

add_executable(Bayes_classifier ${SRC_FILE})


# target_link_libraries(ANN FUNC_LIB)
# target_link_libraries(ANN TOOLS_LIB)
# target_link_libraries(ANN DEBUG_LIB)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
