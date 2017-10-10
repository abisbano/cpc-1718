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
 */

#include<vector>
#include<iostream>
#include<cassert>
#include<climits>

void kadane(const std::vector<int> &Vec) {
  int MaxSum = INT_MIN;
  int Sum;
  for (auto I = Vec.begin(), End = Vec.end(); I != End; ++I) {
    Sum = 0;
    for (auto J = I; J != End; ++J) {
      Sum += *J;
      if (Sum > MaxSum) MaxSum = Sum;
    }
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
