set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 26)

file(GLOB SRC "./*.cpp")

add_executable(neolib_test ${SRC})
target_include_directories(neolib_test PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src/include)
target_link_libraries(neolib_test neolib_static)
