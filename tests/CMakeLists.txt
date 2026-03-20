include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
)

# Prevent GoogleTest from overriding our compiler/linker options (Windows)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_executable(numops_tests test_numops.cpp)

target_link_libraries(numops_tests
  PRIVATE
    numops::numops
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(numops_tests)
