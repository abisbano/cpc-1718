/*
  Megacity.cc

  author: Andrea Bisbano
  date: 18/11/17
  problem: http://codeforces.com/problemset/problem/424/B?locale=en

  solution description:

 The idea is to consider each city in increasing distance from the center and for each of them compute the
  total population. When the value reach the given threshold (one million in this case) we simply return
  the distance of the last considered city as the required radius, if we reach the last element and the sum
  is less than one million we simply return the special value -1,
 To do so we use a support class that stores the distance from the center and the population of a given city.
 We don't need to store the coordinates of each city because we consider that each one has a unique pair.

 The cost in time of this algorithm is O(nlogn + n), so O(nlogn) since we need to sort the elements and,
  after sorting, read them at most one time. We don't need additional space for this solution.

*/

#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>
#include <algorithm>

#define MAX_COORDINATE 10000
#define POPULATION 1000000

class City {
  // We store directly the distance from the origin (we assume every city has unique coordinates)
  double Distance;
  int Population;
public:
  City(int X, int Y, int P) : Population(P) {
    Distance = sqrt(X*X + Y*Y);
  }

  City(double D, int P) : Distance(D), Population(P) {}

  double getDistance() const {
    return Distance;
  }

  int getPopulation() const {
    return Population;
  }

  friend bool operator<(const City& lhs, const City& rhs) {
    // If two city are at the same distance, we sort first the one with higher population.
    if (lhs.getDistance() == rhs.getDistance()) {
      return lhs.getPopulation() > rhs.getPopulation();
    }
    return lhs.getDistance() < rhs.getDistance();
  }

};

double computeMegacity(std::vector<City> Vec, int TotalPopulation) {

  std::sort(Vec.begin(), Vec.end());
  for(City C : Vec) {
    TotalPopulation += C.getPopulation();
    if (TotalPopulation >= POPULATION)
      return C.getDistance();
  }
  return -1;
}

int main() {
  int Cities;
  int StartingPopulation;
  std::vector<City> Neighbors;

  std::cin >> Cities;
  assert(Cities >= 1 && Cities <= 1000);
  std::cin >> StartingPopulation;
  assert(StartingPopulation >= 1 && StartingPopulation < POPULATION);
  Neighbors.reserve(Cities);

  int X, Y, Population;
  for (int i = 0; i < Cities; ++i) {
    // We consider the input is valid (i.e. there aren't two city with same coordinates)
    //  so we don't perform any check on the input value.
    std::cin >> X;
    assert(X >= -MAX_COORDINATE && X <= MAX_COORDINATE);
    std::cin >> Y;
    assert(Y >= -MAX_COORDINATE && Y <= MAX_COORDINATE);
    std::cin >> Population;
    assert(Population >= 1 && Population <= POPULATION);
    Neighbors.emplace_back(X,Y,Population);
  }

  double Result = computeMegacity(Neighbors, StartingPopulation);
  std::cout.precision(8);
  std::cout << Result << std::endl;
}
