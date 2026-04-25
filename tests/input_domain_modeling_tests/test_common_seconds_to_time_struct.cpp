/*
 * =============================================================================
 * File: tests/test_common_seconds_to_time_struct.cpp
 *
 * Abstract:
 *   Date        Description                              Developer
 *   ----------  ---------------------------------------  -----------------
 *   2026-04-04  Common::secondsToTimeStruct test cases   R. Vaughn
 * =============================================================================
 */

#include <gtest/gtest.h>
#include <common.h>

// B1 - sub-minute, single-digit seconds
// seconds < 60 and seconds < 10 → minutes "00", seconds zero-padded
TEST(SecondsToTimeStructTest, SubMinute_SingleDigitSeconds) {
    auto result = Common::secondsToTimeStruct(5);
    EXPECT_EQ(result.minutes, "00");
    EXPECT_EQ(result.seconds, "05");
}

// B2 - sub-minute, double-digit seconds
// seconds < 60 and seconds >= 10 → minutes "00", seconds not padded
TEST(SecondsToTimeStructTest, SubMinute_DoubleDigitSeconds) {
    auto result = Common::secondsToTimeStruct(45);
    EXPECT_EQ(result.minutes, "00");
    EXPECT_EQ(result.seconds, "45");
}

// B3 - exact minute boundary, single-digit minutes
// seconds == 60 → minutes "01", seconds "00"
TEST(SecondsToTimeStructTest, ExactMinuteBoundary_SingleDigitMinutes) {
    auto result = Common::secondsToTimeStruct(60);
    EXPECT_EQ(result.minutes, "01");
    EXPECT_EQ(result.seconds, "00");
}

// B4 - exact minute boundary, double-digit minutes
// seconds == 600 → minutes "10", seconds "00"
TEST(SecondsToTimeStructTest, ExactMinuteBoundary_DoubleDigitMinutes) {
    auto result = Common::secondsToTimeStruct(600);
    EXPECT_EQ(result.minutes, "10");
    EXPECT_EQ(result.seconds, "00");
}

// B5 - over one minute, single-digit minutes, single-digit seconds remainder
// seconds / 60 < 10 and seconds % 60 < 10 → both fields zero-padded
TEST(SecondsToTimeStructTest, OverOneMinute_SingleDigitMinutes_SingleDigitRemainder) {
    auto result = Common::secondsToTimeStruct(65);
    EXPECT_EQ(result.minutes, "01");
    EXPECT_EQ(result.seconds, "05");
}

// B6 - over one minute, single-digit minutes, double-digit seconds remainder
// seconds / 60 < 10 and seconds % 60 >= 10 → minutes zero-padded, seconds not
TEST(SecondsToTimeStructTest, OverOneMinute_SingleDigitMinutes_DoubleDigitRemainder) {
    auto result = Common::secondsToTimeStruct(75);
    EXPECT_EQ(result.minutes, "01");
    EXPECT_EQ(result.seconds, "15");
}

// B7 - over one minute, double-digit minutes, double-digit seconds remainder
// seconds / 60 >= 10 and seconds % 60 >= 10 → neither field zero-padded
TEST(SecondsToTimeStructTest, OverOneMinute_DoubleDigitMinutes_DoubleDigitRemainder) {
    auto result = Common::secondsToTimeStruct(615);
    EXPECT_EQ(result.minutes, "10");
    EXPECT_EQ(result.seconds, "15");
}
