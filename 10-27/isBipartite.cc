/*
 IsBipartite.cc
 Author: Andrea Bisbano
 Date: 16/01/18
 Problem: https://practice.geeksforgeeks.org/problems/bipartite-graph/1
 Solution:
  This algorithm apply a 2-coloration to a graph. Every node is initialized with color 0 (e.g. no color),
  then one node is colored with a color and all adjacents without a color with the opposite, and so on.
  If a node has an adjacent which is already colored with the same color, then the algorithm stops
  because the graph is not bipartite.
 Time cost: O(n^2) because the graph is represented with a adjacency matrix.
 Space cost: O(1)
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
    if (color[i] == 0)
      color[i] = 1;
    for (int j = 0; j < V; ++j) {
      if (G[i][j] == 0) continue;
      if (color[i] == color[j])
        return false;
      color[j] = (color[i] == 1) ? 2 : 1;
    }
  }

  return true;

}
