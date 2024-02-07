#include <iostream>
#include <vector>
#include <functional>

using std::vector;
using std::pair;

#define VISITED 1
#define REMOVED 2

int acyclic(vector<vector<int> > &adj) {
  vector<char> mark(adj.size(), 0);
  std::function<bool(int)> dfs_found_cycle;
  dfs_found_cycle = [&](int v) {
    mark[v] = VISITED;
    for (int w : adj[v]) {
      if (mark[w] == VISITED) {
        return true;
      } else if (mark[w] == 0) {
        if (dfs_found_cycle(w)) return true;
      }
    }
    mark[v] = REMOVED;
    return false;
  };

  for (int i = 0; i < adj.size(); i++) {
    if (mark[i] == 0) {
      if (dfs_found_cycle(i)) {
        return 1;
      }
    }
  }

  //write your code here
  return 0;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  std::cout << acyclic(adj);
}
