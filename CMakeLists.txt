cmake_minimum_required(VERSION 3.2)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(ipfilter VERSION ${PROJECT_VERSION})

option(WITH_GOOGLE_TEST "Whether to build Google tets" ON)

configure_file(version.h.in version.h)

add_executable(ip_filter main.cpp ip_pool.cpp)


add_library(ipfilter_ver lib.cpp)




set_target_properties(ip_filter ipfilter_ver PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
        )

target_include_directories(ipfilter_ver
        PRIVATE "${CMAKE_BINARY_DIR}"
        )

target_link_libraries(ip_filter PRIVATE
        ipfilter_ver
        )


if(WITH_GOOGLE_TEST)
    add_subdirectory(./googletest EXCLUDE_FROM_ALL)
    add_executable(google_test_version test_version_g.cpp ippool.cpp ip_pool.cpp ip_pool.h)

    set_target_properties(google_test_version PROPERTIES
            CXX_STANDARD 17
            CXX_STANDARD_REQUIRED ON
            )

    target_link_libraries(google_test_version
            gtest_main
            ipfilter_ver
            )
endif()

if (MSVC)
    target_compile_options(ip_filter PRIVATE
            /W4
            )
    target_compile_options(ipfilter_ver PRIVATE
            /W4
            )
    if(WITH_GOOGLE_TEST)
        target_compile_options(google_test_version PRIVATE
                /W4
                )
    endif()
else ()
    target_compile_options(ip_filter PRIVATE
            -Wall -Wextra -pedantic -Werror
            )
    target_compile_options(ipfilter_ver PRIVATE
            -Wall -Wextra -pedantic -Werror
            )
    if(WITH_GOOGLE_TEST)
        target_compile_options(google_test_version PRIVATE
                -Wall -Wextra -pedantic -Werror
                )
    endif()
endif()

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT zholu008@gmail.com)
include(CPack)

if(WITH_GOOGLE_TEST)
    enable_testing()
    include(GoogleTest)
    gtest_discover_tests(google_test_version)
endif()