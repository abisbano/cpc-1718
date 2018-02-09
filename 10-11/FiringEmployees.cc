/*
  FiringEmployees.cc

  author: Andrea Bisbano
  date: 02/01/18
  problem: https://practice.geeksforgeeks.org/problems/firing-employees/0

  solution description:
 The idea of this solution it to arrange the data to create a tree where every node has as father
  its immediate senior. In this representation Mr. Alfred will be the root and the height of a node
  is the number of seniors of that employee.





*/

#include <iostream>
#include <cassert>
#include <vector>
#include <stack>
#include <cmath>


void generatePrimes(std::vector<bool> &primes) {
  uint32_t n = primes.size();
  uint32_t square = (uint32_t) sqrt(n);
  for (uint32_t i = 2; i < square; ++i) {
    if (primes[i]) {
      uint32_t x = i*i;
      while(x < n) {
        primes[x] = false;
        x += i;
      }
    }
  }
}

int firingEmployees(const std::vector<uint32_t> &vec) {

  size_t size = vec.size();

  std::vector<std::vector<uint32_t>> positions(size + 1, std::vector<uint32_t>());

  for (size_t i = 0; i < size; ++i) {
    positions[vec[i]].push_back(i+1);
  }

  std::vector<uint32_t> seniors(size+1, 0);

  std::stack<uint32_t> stack;

  stack.push(positions[0].front());
  for (size_t i = 1; i <= size; ++i) {
    auto list = positions[stack.top()];
    stack.pop();
    for (auto pos : list) {
      seniors[pos] = 1 + seniors[vec[pos-1]];
      stack.push(pos);
    }
  }

  std::vector<bool> primes(2*(size+1), true);
  generatePrimes(primes);

  int firedEmployees = 0;
  for (size_t i = 1; i <= size; ++i) {
    if (seniors[i] && primes[seniors[i] + i]) {
      ++firedEmployees;
    }
  }

  return firedEmployees;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  uint32_t testCases;
  std::vector<uint32_t> vec;
  size_t size;
  uint32_t value;

  std::cin >> testCases;
  assert(testCases >= 1 && testCases <= 1000);

  for (int i = 0; i < testCases; ++i) {
    std::cin >> size;
    assert(size >= 1 && size <= 100000);
    for (size_t j = 0; j < size; ++j) {
      std::cin >> value;
      assert(value >= 0 && value <= size);
      vec.push_back(value);
    }
    std::cout << firingEmployees(vec) << std::endl;
    vec.clear();
  }

  return 0;
}
