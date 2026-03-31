# =============================================================================
# File: tests/CMakeLists.txt
#
# Abstract:
#   Date        Description                              Developer
#   ----------  ---------------------------------------  -----------------
#   2026-03-28  Add GTest CTest integration              R. Vaughn
#   2026-03-30  Add test_field_find_neighbors.cpp        C. Vaughn
# =============================================================================

include(GoogleTest)

add_executable(minesweeper_tests
    test_common.cpp
    test_field_find_neighbors.cpp
)

target_link_libraries(minesweeper_tests
    PRIVATE
        minesweeper_lib
        GTest::gtest_main
)

gtest_discover_tests(minesweeper_tests)
