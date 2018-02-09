/*
  MissingNumber.cc

  author: Andrea Bisbano
  date: 18/10/17
  problem: http://practice.geeksforgeeks.org/problems/missing-number-in-array/0
 
  description:
   This solution exploit the property of xor operation
     a ^ b ^ a = b
   Let N be the length of the given array A and T be the xor of the
   expected elements of the array (T = 1 ^ 2 ^ ... ^ N)
   We compute S, the xor of the elements of the array:
     S = A[1] ^ A[2] ^ ... ^ A[N-1]
   The solution is R = T ^ S.
   That's true because the array A contains N-1 different element from 1 to N.

  time cost: O(N) because we need to scan one time all the elemnts of th  array.
  space cost: O(1) because we need to store only a extra variable to store the xor od the array.
*/

#include <iostream>
#include <cassert>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  size_t T = 0;
  size_t size = 0;
  uint32_t val = 0;
  uint32_t result;

  std::cin >> T;
  assert(T > 0 && T <= 200);

  for (size_t i = 0; i < T; ++i) {
    std::cin >> size;
    assert(size > 0 && size <= 1000);
    result = 0;
    for (size_t j = 1; j < size; ++j) {
      // We start the loop from 1 to simplify the computation.
      std::cin >> val;
      assert(val >= 0 && val <= 1000);
      result ^= j;
      result ^= val;
    }
    result ^= size;
    std::cout << result << "\n";
  }
}
