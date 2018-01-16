/*
  XTotalShapes.cc

  author: Andrea Bisbano
  date: 15/01/18
  problem: https://practice.geeksforgeeks.org/problems/x-total-shapes/0

  solution description:
 TO BE WRITTEN
*/

#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <stack>
#include <tuple>

uint64_t countXShapes(std::vector<std::vector<bool>> &Matrix) {
  size_t N = Matrix.size() - 2;
  size_t M = Matrix[0].size() - 2;

  uint64_t result = 0;
  std::stack<std::pair<size_t, size_t>> st;

  for (size_t i = 1; i <= N; ++i) {
    for (size_t j = 1; j <= M; ++j) {

      if (Matrix[i][j]) {
        // new shape
        ++result;
        std::cout << i << " " << j << std::endl;
        st.push(std::make_pair(i,j));
        while(!st.empty()) {
          auto vert = st.top();
          st.pop();
          size_t x = vert.first;
          size_t y = vert.second;
          if (Matrix[x][y]) {
            Matrix[x][y] = false;
              st.push(std::make_pair(x-1, y));
              st.push(std::make_pair(x, y-1));
              st.push(std::make_pair(x+1, y));
              st.push(std::make_pair(x, y+1));
          }
        }
      }

    }
  }
  return result;

}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  size_t testCases;

  size_t N, M;
  std::string s;
  std::vector<std::vector<bool>> Matrix;

  std::cin >> testCases;

  for (size_t i = 0; i < testCases; ++i) {
    std::cin >> N >> M;

    Matrix.push_back(std::vector<bool>(M+2,false));
    for (size_t j = 0; j < N; ++j) {
      std::vector<bool> line(M+2, false);
      std::cin >> s;
      for (size_t k = 0; k < M; ++k) {
        if (s[k] == 'O') {
          line[k+1] = false;
        } else {
          line[k+1] = true;
        }
      }
      Matrix.push_back(line);
    }

    Matrix.push_back(std::vector<bool>(M+2,false));

    std::cout <<  countXShapes(Matrix) << std::endl;
  }
}
