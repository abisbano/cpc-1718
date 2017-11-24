/*
  Kadane.cc

  author: Andrea Bisbano
  date: 10/10/17
  problem: http://practice.geeksforgeeks.org/problems/kadanes-algorithm/0

  solution description:
  First naive sultion, given `i' the first element of a subarray, at each step
  of the main loop we calculate the sum of each subarray with i as first element.
  This solution has cast in time of O(n^2) since we need also a inner loop to
  compute the sum of each subarray.
 
  A better solution exploit two properties of the subarray with maximum sum:
  1. Sum of values of each subarray of the optimum subarray is positive.
     Consider the array [3 -4 5], here the sum of subarray [3 -4] is -1. If
     we consider the whole array as solution, the result is 4, instead if we
     remove that subarray we see there's a better solution (which is 5).
  2. The value that precede the first value of the optimal subarray is 
     a negative one. This is easier to prove: if that value is positive, then
     we might add it to the solution to have an higher value.
  Using these two properties we can iterate only one time over the element
  of the array, so the cost in time is O(n).

 */

#include<vector>
#include<iostream>
#include<cassert>
#include<climits>

void kadane(const std::vector<int> &Vec) {
  int MaxSum = INT_MIN;
  int Sum = 0;
  for (auto It = Vec.begin(), End = Vec.end(); It != End; ++It) {
  /* We use this if statment to apply both properties:
     1. if the sum till now is negative, we start over
     2. a negative element as head of the subarray implies property 1
  */
    if (Sum > 0)
      Sum += *It;
    else
      Sum = *It;

    if (Sum > MaxSum)
      MaxSum = Sum;
  }

  std::cout << MaxSum << std::endl;
}

int main() {

  int TestCases;
  std::cin >> TestCases;
  assert(TestCases > 0 && TestCases <= 200);

  std::vector<int> Vec;
  int Size;
  int Element;

  for (int i = 0; i < TestCases; ++i) {
    std::cin >> Size;
    assert(Size > 0 && Size <= 1000);

    Vec.reserve(Size);

    for (int j = 0; j < Size; ++j) {
      std::cin >> Element;
      assert(Element >= -100 && Element <= 100);
      Vec.push_back(Element);
    }

    kadane(Vec);
    Vec.clear();
  }
}
