#include <algorithm>
#include <iostream>
#include <vector>
#include <functional>

using std::vector;
using std::pair;

int number_of_strongly_connected_components(vector<vector<int> > adj) {
  int result = 0;
  int n = adj.size();
  vector<vector<int>> adj_r(n, vector<int>());;;
  for (int v = 0; v < n; v++) {
    for (int w: adj[v]) {
      adj_r[w].push_back(v);
    }
  }

  vector<bool> mark(n, false);
  vector<int> order;
  
  std::function<void(int)> dfs_topo_r;
  dfs_topo_r = [&](int v) {
    mark[v] = true;
    for (int w: adj_r[v]) {
      if (!mark[w]) dfs_topo_r(w);
    }
    order.push_back(v);
  };

  for (int i = 0; i < n; i++) {
    if (!mark[i]) dfs_topo_r(i);
  }

  for (int i = 0; i < n; i++) {mark[i] = false;}

  std::function<void(int)> dfs;
  dfs = [&](int v) {
    mark[v] = true;
    for (int w: adj[v]) {
      if (!mark[w]) dfs(w);
    }
  };

  for (int i = n - 1; i >= 0; i--) {
    int v = order[i];
    if (!mark[v]) {
      result++;
      dfs(v);
    }    
  }


  //write your code here
  return result;
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
  std::cout << number_of_strongly_connected_components(adj);
}
