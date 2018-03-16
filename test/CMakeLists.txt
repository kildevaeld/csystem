
FILE(GLOB TESTS "*.c")

set(SOURCES
    ${TESTS}
)

add_executable(cs_test ${SOURCES})
target_link_libraries(cs_test csystem csystem_crypto unity)
add_test(cs_test cs_test)
