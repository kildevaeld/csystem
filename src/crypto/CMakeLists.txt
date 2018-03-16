


if (CSYSTEM_CRYPTO_MBEDTLS)
    include_directories(${PROJECT_SOURCE_DIR}/vendor/mbedtls/include)
    set(SOURCES 
        crypto-mbedtls.c
    )
    set(TARGET_DEFINITIONS CSYSTEM_USE_MBEDTLS)
    set(TARGET_LIBRARIRES mbedcrypto)
endif(CSYSTEM_CRYPTO_MBEDTLS)

if (CSYSTEM_CRYPTO_COMMONCRYPTO)
    set(SOURCES 
        crypto-macos.c
    )
    find_library(SECURITY_LIBRARY Security)
    set(TARGET_LIBRARIRES ${SECURITY_LIBRARY})
endif(CSYSTEM_CRYPTO_COMMONCRYPTO)

set(SOURCES ${SOURCES} crypto.c)

add_library(csystem_crypto ${SOURCES})
target_link_libraries(csystem_crypto ${TARGET_LIBRARIRES})
target_compile_definitions(csystem_crypto PRIVATE ${TARGET_DEFINITIONS})