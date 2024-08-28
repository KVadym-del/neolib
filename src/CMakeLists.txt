set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_SHARED_LIBRARY_PREFIX "")

file(GLOB SRC "./*.cpp")

add_library(neolib_obj OBJECT ${SRC})

set_property(TARGET neolib_obj PROPERTY POSITION_INDEPENDENT_CODE 1)

add_library(neolib_static STATIC $<TARGET_OBJECTS:neolib_obj>)
add_library(neolib SHARED $<TARGET_OBJECTS:neolib_obj>)
target_include_directories(neolib_static PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)
target_include_directories(neolib PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)
