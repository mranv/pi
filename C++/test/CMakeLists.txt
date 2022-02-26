include(GoogleTest)

add_subdirectory("${PROJECT_SOURCE_DIR}/extern/googletest" "extern/googletest")

file(GLOB SOURCES "../src/pi_*.cpp")

add_executable(test_pi_double test_pi_double.cpp ${SOURCES})
target_link_libraries(test_pi_double gtest gmock gtest_main mpfr)

add_test(test_pi_double test_pi_double)
