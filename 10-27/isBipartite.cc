/*
  IsBipartite.cc

  author: Andrea Bisbano
  date: 16/01/18
  problem: https://practice.geeksforgeeks.org/problems/bipartite-graph/1

  solution description:
 TO BE WRITTEN
*/

/*
 Please note that it's Function problem i.e.
 you need to write your solution in the form of Function(s) only.
 Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


/*The function takes an adjacency matrix representation of the graph (g)
 and an integer(v) denoting the no of vertices as its arguments.
 You are required to complete below method */

//#define MAX 300
#include <vector>

bool isBipartite(int G[][MAX],int V) {

  std::vector<int> color(V,0);

  for (int i = 0; i < V; ++i) {
    if (G[i][i] == 1)
      return false;
    if (color[i] == 0)
      color[i] = 1;
    int c = color[i];
    for (int j = 0; j < V; ++j) {
      if (G[i][j] == 0) continue;
      if (color[i] == color[j])
        return false;
      color[j] = (color[i] == 1) ? 2 : 1;
    }
  }

  return true;

}
