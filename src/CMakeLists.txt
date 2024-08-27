set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_STATIC_LIBRARY_PREFIX "")

file(GLOB SRC "./*.cpp")

add_library(neolib STATIC ${SRC})
target_include_directories(neolib PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)
