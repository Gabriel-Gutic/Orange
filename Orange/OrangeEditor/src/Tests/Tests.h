#pragma once


#define CHECK_TEST(expr) if (!(expr)) { ASSERT(expr, "Test failed!"); } else { PRINT("Test passed!"); }
