
set(SOURCES
    standardpaths.c
    path.c
    file.c
    #dir.c
    features.c
    string.c
)

configure_file (
  "${PROJECT_SOURCE_DIR}/cmake/csystem_config.h.in"
  "${PROJECT_BINARY_DIR}/csystem_config.h"
  )

if(CS_BUILD_SHARED)
  add_library(csystem SHARED ${SOURCES})
else()
  add_library(csystem STATIC ${SOURCES})
endif(CS_BUILD_SHARED)


target_include_directories(csystem PUBLIC ${PROJECT_ROOT}/include)

install(TARGETS csystem DESTINATION lib)
install(DIRECTORY ${PROJECT_ROOT}/include/csystem DESTINATION include)
install(FILES ${PROJECT_BINARY_DIR}/csystem_config.h DESTINATION include/csystem)
