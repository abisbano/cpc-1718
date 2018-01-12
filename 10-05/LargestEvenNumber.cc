/*
  LargestEvenNumber.cc

  author: Andrea Bisbano
  date: 28/12/17
  problem: https://practice.geeksforgeeks.org/problems/largest-even-number/0

  solution description:

 The idea of this solution is to look for the smallest even digit of the input number and put it as the last
  digit of the result, while the remaining digits are sorted in reverse order.
 To do so, we use the counting sort algorithm on the digits. After the counting phase, we search for the
  smallest even number and if it's found we store it and we decrease the counter for that digit.
 After that, the remaining digits are sorted in reverse order and stored in the solution.
 At that point, if there isn't any even number, we sorted all the digits and the solution is complete,
  otherwise we still have to add the previously stored number at the end of the sequence.
 The cost of this algorithm is the same of the counting sort, so it's O(N+M), where N is the number
  of digits and M is the number of possible digits (i.e. it is constant, 10). This algorithm doesn't require
  additional space.

*/

#include <iostream>
#include <cassert>
#include <vector>

#define OFFSET 48

void largestEvenNumber(std::string &str) {

  std::vector<uint32_t> counter(10, 0);
  size_t n = str.size();
  for (size_t i = 0; i < n; ++i) {
    ++counter[str[i] - OFFSET];
  }

  str.clear();

  char last = 0;

  // Looking for minimum even number or, if there isn't any, minimum number.
  for (size_t i = 0; i < 10; i += 2) {
    if (counter[i] > 0) {
      // Found.
      last = i + OFFSET;
      --counter[i];
      break;
    }
  }

  size_t position = 0;
  for (int i = 9; i >= 0; --i) {
    str.insert(position, counter[i], i + OFFSET);
    position += counter[i];
  }

  if (last) {
    str.insert(position, 1, last);
  }

}

int main() {
  int testCases;
  std::string str;

  std::cin >> testCases;
  assert(testCases >= 1 && testCases <= 100);

  for (int i = 0; i < testCases; ++i) {
    std::cin >> str;
    assert(str.length() >= 1 && str.length() <= 1000);
    largestEvenNumber(str);
    std::cout << str << std::endl;
  }

  return 0;
}
