/*
 Megacity.cc
 Author: Andrea Bisbano
 Date: 18/11/17
 Problem: http://codeforces.com/problemset/problem/424/B?locale=en
 Solution:
  We sort the cities by distance from the center. The we compute the total population
  using one city at the time and starting from the nearest to the center.
  If and when the computation reaches the given threshold (1000000) it returns the distance of
  the last considered city, otherwise, if it doesn't reach that value and it has
  already considered all the cities, it returns the special result -1.
 Time cost: O(nlogn) to sort the elements.
 Space cost: O(1)
*/

#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>
#include <algorithm>

#define MAX_COORDINATE 10000
#define POPULATION 1000000

class city {
  // We store directly the distance from the origin (we assume every city has unique coordinates)
  double distance;
  uint64_t population;
public:
  city(int64_t x, int64_t y, uint64_t p) : population(p) {
    distance = sqrt(x*x + y*y);
  }

  city(double d, uint64_t p) : distance(d), population(p) { }

  double getDistance() const {
    return distance;
  }

  uint64_t getPopulation() const {
    return population;
  }

  friend bool operator<(const city& lhs, const city& rhs) {
    // If two city are at the same distance, we sort first the one with higher population.
    if (lhs.distance == rhs.distance) {
      return lhs.population > rhs.population;
    }
    return lhs.distance < rhs.distance;
  }

};

double computeMegacity(std::vector<city> vec, uint64_t totalPopulation) {
  std::sort(vec.begin(), vec.end());
  for(city c : vec) {
    totalPopulation += c.getPopulation();
    if (totalPopulation >= POPULATION)
      return c.getDistance();
  }
  return -1;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  size_t cities;
  uint64_t startingPopulation;
  std::vector<city> neighbors;
  int64_t x, y;
  uint64_t population;

  std::cin >> cities;
  assert(cities >= 1 && cities <= 1000);
  std::cin >> startingPopulation;
  assert(startingPopulation >= 1 && startingPopulation < POPULATION);
  neighbors.reserve(cities);

  for (size_t i = 0; i < cities; ++i) {
    std::cin >> x;
    assert(x >= -MAX_COORDINATE && x <= MAX_COORDINATE);
    std::cin >> y;
    assert(y >= -MAX_COORDINATE && y <= MAX_COORDINATE);
    std::cin >> population;
    assert(population >= 1 && population <= POPULATION);
    neighbors.emplace_back(x, y, population);
  }

  std::cout.precision(8);
  std::cout << computeMegacity(neighbors, startingPopulation) << "\n";
}
