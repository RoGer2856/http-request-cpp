cmake_minimum_required(VERSION 3.25)

project(http-request-cpp)

include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

file(GLOB_RECURSE ${PROJECT_NAME}_header_files "${CMAKE_CURRENT_LIST_DIR}/src/*.h")
file(GLOB_RECURSE ${PROJECT_NAME}_cpp_files "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")

find_package(CURL)
find_package(jsoncpp)

add_executable(${PROJECT_NAME}
	${${PROJECT_NAME}_header_files}
	${${PROJECT_NAME}_cpp_files}
)

target_link_libraries(${PROJECT_NAME} PRIVATE CURL::libcurl jsoncpp)
