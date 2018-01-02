
set(SOURCES 
    csystem.cpp
)

if(CS_BUILD_SHARED)
  add_library(csystem++ SHARED ${SOURCES})
else()
  add_library(csystem++ STATIC ${SOURCES})
endif(CS_BUILD_SHARED)

target_link_libraries(csystem++ csystem)
install(TARGETS csystem++ DESTINATION lib)
#install(DIRECTORY ${PROJECT_ROOT}/include/csystem DESTINATION include)
#install(FILES ${PROJECT_BINARY_DIR}/csystem_config.h DESTINATION include/csystem)
