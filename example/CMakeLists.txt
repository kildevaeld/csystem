
add_executable(csystem_example main.cpp)
add_executable(cs main.c)

target_link_libraries(csystem_example csystem++)
target_link_libraries(cs csystem_terminal)