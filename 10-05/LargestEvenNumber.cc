/*
 LargestEvenNumber.cc
 Author: Andrea Bisbano
 Date: 28/12/17
 Problem: https://practice.geeksforgeeks.org/problems/largest-even-number/0
 Solution:
  The idea of this solution is to look for the smallest even digit of the input number and put it as the last
  digit of the result, while the remaining digits are sorted in reverse order.
  To do so, the algorithm uses the counting sort on the digits. After the counting phase, it searches for the
  smallest even number and if it's succesful it stores it. Then it decreases the counter for that digit.
  After that, the remaining digits are sorted in reverse order and stored in the solution.
  In the end, if none even number was found, when the algorithm finish sorting digits the solution in complete,
  otherwise it has to do an extra step and put the previously saved digit at the end of the solution.
 Time cost: O(N+M), is the same cost of the counting sort, where N is the number of digits and M the number
            of possible values for each digit (i.e it's a constant, 10).
 Space cost: O(1)
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
  for (int32_t i = 9; i >= 0; --i) {
    str.insert(position, counter[i], i + OFFSET);
    position += counter[i];
  }

  if (last) {
    str.insert(position, 1, last);
  }

}

int main() {
  size_t T;
  std::string str;

  std::cin >> T;
  assert(T >= 1 && T <= 100);

  for (size_t i = 0; i < T; ++i) {
    std::cin >> str;
    assert(str.length() >= 1 && str.length() <= 1000);
    largestEvenNumber(str);
    std::cout << str << "\n";
  }

  return 0;
}
