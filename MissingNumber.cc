/*
  MissingNumber.cc

  author: Andrea Bisbano
  date: 18/10/17
  problem: http://practice.geeksforgeeks.org/problems/missing-number-in-array/0
 
  solution description:
   This solution exploit the property of xor operation
     a ^ b ^ a = b
   Let N be the length of the given array A and T be the xor of the
   expected elements of the array (T = 1 ^ 2 ^ ... ^ N)
   We compute S, the xor of the elements of the array:
     S = A[1] ^ A[2] ^ ... ^ A[N-1]
   The solution is R = T ^ S.
   That's true because the array A contains N-1 different element
     from 1 to N.
   The cost in time is O(N) because we can use the same loop to
     compute directly the solution S.
   The extra space needed for this algorithm is O(logN) bits, since we
     need to allocate just a variabial which can store the maximum
     value of the array.
*/

#include <iostream>
#include <cassert>

int main() {

  int TestCases = 0;
  std::cin >> TestCases;
  assert(TestCases > 0 && TestCases <= 200);

  int Size = 0;
  int Value = 0;

  for (int i = 0; i < TestCases; ++i) {
    std::cin >> Size;
    assert(Size > 0 && Size <= 1000);
    int Result = 0;
    for (int j = 1; j < Size; ++j) {
      // We start the loop from 1 to simplify the computation.
      std::cin >> Value;
      assert(Value >= 0 && Value <= 1000);
      Result ^= j;
      Result ^= Value;
    }
    Result ^= Size;
    std::cout << Result << std::endl;
  }
}
