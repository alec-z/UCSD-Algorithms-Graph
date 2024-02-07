#include <iostream>
#include <vector>
#include <cstring>
#include <functional>

using std::vector;
using std::pair;




int reach(vector<vector<int> > &adj, int x, int y) {
  //write your code here
  bool mark[adj.size()];
  memset(mark,false,sizeof(mark));
  std::function<void(int)> dfs;

  dfs = [&](int v) {
    mark[v] = true;
    for (int w : adj[v]) {
      if (!mark[w]) dfs(w);
    }
  };
  dfs(x);
  return mark[y];
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
  int x, y;
  std::cin >> x >> y;
  std::cout << reach(adj, x - 1, y - 1);
}
