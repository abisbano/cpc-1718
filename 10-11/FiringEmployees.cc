/*
 FiringEmployees.cc
 Author: Andrea Bisbano
 Date: 02/01/18
 Problem: https://practice.geeksforgeeks.org/problems/firing-employees/0
 Solution:
  The idea of this solution is to create a tree where each node has as father its immediate senior.
  Mr. Alfred will be the root of that tree and the height of any node the number of its seniors.
  Then we computes the prime numbers up to 2n using the sieve of Eratosthenes. After that, it's
  immediate to compute if a employee is in the black list or not.
 Time cost: O(nloglogn) beacuse the cost is dominated by the cost of the sieve of Eratosthenes.
 Space cost: O(n) because we need to store the primes up to 2n, where n is the number of emplyees.
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

uint32_t firingEmployees(const std::vector<uint32_t> &vec) {

  size_t size = vec.size();
  std::vector<std::vector<uint32_t>> positions(size + 1, std::vector<uint32_t>());

  // positions: for each i, it contains a vector containing the subordinates of i.
  for (size_t i = 0; i < size; ++i) {
    positions[vec[i]].push_back(i+1);
  }

  // seniors: for each i contains the number of seniors of that emplyee.
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

  uint32_t firedEmployees = 0;
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

  uint32_t T;
  std::vector<uint32_t> vec;
  size_t size;
  uint32_t value;

  std::cin >> T;
  assert(T >= 1 && T <= 1000);

  for (size_t i = 0; i < T; ++i) {
    std::cin >> size;
    assert(size >= 1 && size <= 100000);
    for (size_t j = 0; j < size; ++j) {
      std::cin >> value;
      assert(value >= 0 && value <= size);
      vec.push_back(value);
    }
    std::cout << firingEmployees(vec) << "\n";
    vec.clear();
  }

  return 0;
}
