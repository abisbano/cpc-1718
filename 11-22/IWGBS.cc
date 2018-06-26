/*
 IWGBS.cc
 Author: Andrea Bisbano
 Date: 22/01/18
 Problem: http://www.spoj.com/problems/IWGBS/
 Solution:
  The number of N digits numbers is equal to the number of n-1 digits number with a leading `1'
  plus the number of n-2 digits number with a leading `01'. Computing that number is equivalent to
  compute the nth Fibonacci's number starting from F0 = 1 and F1 = 2.
  The solution computes the required number using a DP algorithm: starting from F1 and F2, it computes
  the number using precedent results.
  Here the main problem was to add support for integers of more than 64 bits.
 Time cost: O(N) to compute the Nth Fibonacci's number.
 Space cost: O(N) to store the previous results.
*/

#include<vector>
#include<iostream>
#include<sstream>
#include<cassert>
#include<iterator>

class BigInt {
  std::vector<uint8_t> digits;
  uint8_t maybeGetDigit(size_t) const;
public:
  BigInt();
  BigInt(int64_t);
  BigInt(const BigInt&);
  BigInt operator+(const BigInt&);

  friend std::ostream& operator<<(std::ostream&, const BigInt&);
};

uint8_t toChar(uint8_t a) {
  return a + 48;
}

uint8_t BigInt::maybeGetDigit(size_t i) const {
  if (i >= this->digits.size()) {
    return 0;
  }
  return this->digits[i];
}

BigInt::BigInt() { }

BigInt::BigInt(int64_t val) {
  while (val > 0) {
    digits.push_back(val % 10);
    val /= 10;
  }
}

BigInt::BigInt(const BigInt &a) {
  this->digits.reserve(a.digits.size());
  std::copy(a.digits.begin(), a.digits.end(), std::back_inserter(this->digits));
}

BigInt BigInt::operator+(const BigInt &a) {
  BigInt result;

  size_t size = std::max(this->digits.size(), a.digits.size());

  uint8_t digit;
  uint8_t carry = 0;

  result.digits.reserve(size + 1);

  for (size_t i = 0; i < size; ++i) {
    digit = this->maybeGetDigit(i) + a.maybeGetDigit(i) + carry;
    result.digits.push_back(digit % 10);
    carry = digit/10;
  }
  if (carry != 0) {
    result.digits.push_back(carry);
  }
  return result;
}

std::ostream& operator<<( std::ostream& out, const BigInt &a) {
  if (a.digits.empty()) {
    out << "0";
  } else {
    for (auto it = a.digits.rbegin(), end = a.digits.rend();
         it != end; ++it) {
      out << toChar(*it);
    }
  }
  return out;
}

BigInt fib(uint64_t n) {
  if (n == 0) return 0;
  std::vector<BigInt> result;
  result.reserve(n+1);
  result.emplace_back(1);
  result.emplace_back(2);
  for (size_t i = 2; i <= n; ++i) {
    result.push_back(result[i-1] + result[i-2]);
  }
  return result[n];

}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  uint64_t n;

  std::cin >> n;

  std::cout << fib(n) << "\n";
}
