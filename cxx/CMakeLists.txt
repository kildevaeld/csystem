
set(SOURCES 
    csystem.cpp
)

add_library(csystem++ ${SOURCES})
target_link_libraries(csystem++ csystem)

set_target_properties(csystem++ PROPERTIES CMAKE_CXX_STANDARD 11)