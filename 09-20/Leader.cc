/*
  Leader.cc

  author: Andrea Bisbano
  date: 06/10/17
  problem: http://practice.geeksforgeeks.org/problems/leaders-in-an-array/0#ExpectOP
 
  solution description:
    This solution uses a basic algorithm to find the maximum element of an array
      (we keep a current maximimum and we scan the array updating that
      value if a higher element is found).
    Scanning the array in reverse order let us find leaders each time
      we update the current maximum, since every element already seen
      is smaller or equal than that.
    This solution has time complexity O(n) since it requires to read
      each element of the array only one time.
*/

#include <iostream>
#include <vector>
#include <cassert>


void printLeaders(const std::vector<int> &Vec) {
  std::vector<int> Leaders;
  Leaders.reserve(Vec.size());

  int Max = Vec.back();

  Leaders.push_back(Max);

  for (auto It = Vec.rbegin() + 1, End = Vec.rend(); It != End; ++It) {
    if (*It > Max) {
      Max = *It;
      Leaders.push_back(Max);
    }
  }

  for (auto It = Leaders.rbegin(), End = Leaders.rend(); It != End; ++It) {
    std::cout << *It << " ";
  }
  std::cout << std::endl;
}

int main() {

  int TestCases = 0;
  std::cin >> TestCases;
  assert(TestCases > 0 && TestCases <= 100);

  std::vector<int> Vec;
  int Size = 0;
  int Value = 0;

  for (int i = 0; i < TestCases; ++i) {
    std::cin >> Size;
    assert(Size > 0 && Size <=100);
    Vec.reserve(Size);
    for (int j = 0; j < Size; ++j) {
      std::cin >> Value;
      assert(Value >= 0 && Value <= 100);
      Vec.push_back(Value);
    }
    printLeaders(Vec);
    Vec.clear();
  }
}
