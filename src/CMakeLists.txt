
set(SOURCES
    standardpaths.c
    path.c
    features.c
)

configure_file (
  "${PROJECT_SOURCE_DIR}/cmake/csystem_config.h.in"
  "${PROJECT_BINARY_DIR}/csystem_config.h"
  )

add_library(csystem ${SOURCES})



install(TARGETS csystem DESTINATION lib)
install(DIRECTORY ${PROJECT_ROOT}/include/csystem DESTINATION include)
install(FILES ${PROJECT_BINARY_DIR}/csystem_config.h DESTINATION include/csystem)
