#include "brica/assocvec.hpp"
#include "gtest/gtest.h"

TEST(assocvec, basic) {
  brica::AssocVec<int, int> map;

  for (int i = 0; i < 10; ++i) {
    map[i] = i;
  }

  for (int i = 0; i < 10; ++i) {
    ASSERT_EQ(i, map[i]);
  }

  for (int i = 0; i < 10; ++i) {
    ASSERT_EQ(i, map.index(i));
  }

  map[-1] = -1;
  ASSERT_EQ(-1, map.index(0));
}
