set(BUILD_GMOCK OFF CACHE BOOL "Builds the googlemock subproject")
set(INSTALL_GTEST OFF CACHE BOOL "Enable installation of googletest")

include(GoogleTest)

add_subdirectory("${PROJECT_SOURCE_DIR}/extern/googletest" "extern/googletest")

file(GLOB SOURCES "../src/pi_*.cpp")

add_executable(test_pi_double test_pi_double.cpp ${SOURCES})
add_executable(test_pi_multi test_pi_multi.cpp ${SOURCES})

target_link_libraries(test_pi_double gtest gtest_main mpfr)
target_link_libraries(test_pi_multi gtest gtest_main mpfr)

add_custom_target(test_pi_inout ALL DEPENDS test_pi_inout COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/test_pi_inout test_pi_inout)

add_test(test_pi_double test_pi_double)
add_test(test_pi_multi test_pi_multi)
add_test(test_pi_inout test_pi_inout)
