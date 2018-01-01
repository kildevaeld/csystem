
set(SOURCES 
    csystem.cpp
)

add_library(csystem++ ${SOURCES})
target_link_libraries(csystem++ csystem)

set_target_properties(csystem++ PROPERTIES CMAKE_CXX_STANDARD 11)


install(TARGETS csystem++ DESTINATION lib)
#install(DIRECTORY ${PROJECT_ROOT}/include/csystem DESTINATION include)
#install(FILES ${PROJECT_BINARY_DIR}/csystem_config.h DESTINATION include/csystem)
