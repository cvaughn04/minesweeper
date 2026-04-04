# =============================================================================
# File: tests/CMakeLists.txt
#
# Abstract:
#   Date        Description                              Developer
#   ----------  ---------------------------------------  -----------------
#   2026-03-28  Add GTest CTest integration              R. Vaughn
#   2026-03-30  Add test_field_find_neighbors.cpp        C. Vaughn
#   2026-03-31  Add test_field_is_flag.cpp               C. Vaughn
#   2026-04-03  Add test_input_move_cursor.cpp           C. Vaughn
#   2026-04-03  Add test_input_get_difficulty.cpp        C. Vaughn
#   2026-04-03  Add more Field test files                N. Schweikhart
#   2026-04-04  Add test_common_seconds_to_time_struct   R. Vaughn
#   2026-04-04  Add test_common_int_to_coords            R. Vaughn
#   2026-04-04  Add test_common_coords_to_int            R. Vaughn
#   2026-04-04  Add test_common_coords_to_cursor_pos     R. Vaughn
# =============================================================================

include(GoogleTest)

add_executable(minesweeper_tests
    test_common.cpp
    test_common_seconds_to_time_struct.cpp
    test_common_int_to_coords.cpp
    test_common_coords_to_int.cpp
    test_common_coords_to_cursor_position.cpp
    test_field_find_neighbors.cpp
    test_field_is_flag.cpp
    test_input_move_cursor.cpp
    test_input_get_difficulty.cpp
    test_field_is_number.cpp
    test_field_game_lost.cpp
    test_field_fill_mines.cpp
    test_field_create_2D_Vector.cpp
)

target_link_libraries(minesweeper_tests
    PRIVATE
        minesweeper_lib
        GTest::gtest_main
)

gtest_discover_tests(minesweeper_tests)
