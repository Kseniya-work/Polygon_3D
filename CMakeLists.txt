# build project process:
# cd polygon_3D/build/
# cmake -DCMAKE_BUILD_TYPE=Debug(Release) polygon_3D/source/
# cmake --build . --target install

cmake_minimum_required(VERSION 3.0)

project(polygon_3D)

include_directories(${PROJECT_SOURCE_DIR}/..)
message(${PROJECT_SOURCE_DIR})

set(SOURCES
    ${PROJECT_SOURCE_DIR}/polygon_3D/polygon_3D.cpp
)

set(TEST_SOURCES
    ${PROJECT_SOURCE_DIR}/test/test_call.cpp
)

set(OUTPUT_PATH "${CMAKE_BINARY_DIR}/..")
set(CMAKE_INSTALL_RPATH "${CMAKE_BINARY_DIR}/..")
message("CMAKE_INSTALL_RPATH: " ${CMAKE_INSTALL_RPATH})

if(NOT CMAKE_BUILD_TYPE) 
    set(CMAKE_BUILD_TYPE Release)
endif()
message("cmake_build_type: " ${CMAKE_BUILD_TYPE})

set(TARGET_EXE_NAME test_call)

add_executable(${TARGET_EXE_NAME} 
    ${TEST_SOURCES}
)

install(
    TARGETS ${TARGET_EXE_NAME} ${TARGET_LIB_NAME}
    RUNTIME DESTINATION ${OUTPUT_PATH}
    CONFIGURATIONS ${CMAKE_BUILD_TYPE}
)