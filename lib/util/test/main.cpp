

#include "gtest/gtest.h"
#include "task.hpp"

namespace
{
  ott::util::task<int> foo() {
    co_return 42;
  }
  ott::util::task<int> bar() 
  {
    const auto result = foo();
    const int i = co_await result;
    co_return i + 23;
  }
}

TEST(initial_Test, simple_test)
{
  bar();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
