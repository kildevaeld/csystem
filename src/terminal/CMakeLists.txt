




set(SOURCES ${SOURCES} 
    terminal.c
    form.c
)

add_library(csystem_terminal ${SOURCES})
target_link_libraries(csystem_terminal csystem)
#target_link_libraries(csystem_terminal ${TARGET_LIBRARIRES})
#target_compile_definitions(csystem_terminal PRIVATE ${TARGET_DEFINITIONS})