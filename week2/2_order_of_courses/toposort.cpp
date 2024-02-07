#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>

using std::vector;
using std::pair;
using std::swap;

void dfs(vector<vector<int> > &adj, vector<int> &used, vector<int> &order, int x) {
  //write your code here
}     

vector<int> toposort(vector<vector<int> > adj) {
  int n = adj.size();
  vector<bool> mark(n, false);
  vector<int> order;
  //write your code here
  std::function<void(int)> dfs_topo;
  dfs_topo = [&](int v) {
    mark[v] = true;
    for (int w: adj[v]) {
      if (!mark[w]) {
        dfs_topo(w);
      }
    }
    order.push_back(v);
  };
  for (int i = 0; i < n; i++) {
    if (!mark[i]) {
      dfs_topo(i);
    }
  }
  for (int i = n - 1; i > (n - 1) / 2; i--) {
    swap(order[i], order[n - 1 - i]);
  }
  return order;
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
  vector<int> order = toposort(adj);
  for (size_t i = 0; i < order.size(); i++) {
    std::cout << order[i] + 1 << " ";
  }
}
