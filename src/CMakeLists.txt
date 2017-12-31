
set(SOURCES
    standardpaths.c
    path.c
    features.c
)

add_library(csystem ${SOURCES})


install(TARGETS csystem DESTINATION lib)
install(DIRECTORY ${PROJECT_ROOT}/include/csystem DESTINATION include)

