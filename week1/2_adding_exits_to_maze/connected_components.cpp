#include <iostream>
#include <vector>
#include <functional>
#include <cstring>

using std::vector;
using std::pair;

int number_of_components(vector<vector<int> > &adj) {
  int res = 0;
  bool mark[adj.size()];
  memset(mark, false, sizeof(mark));
  std::function<void(int)> dfs;
  dfs = [&](int v) {
    mark[v] = true;
    for (int w: adj[v]) {
      if (!mark[w]) dfs(w);
    }
  };
  for (int i = 0; i < adj.size(); i++) {
    if (!mark[i]) {
      res ++;
      dfs(i);
    }
  }
  
  return res;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << number_of_components(adj);
}
