#include <iostream>
#include <queue>
#include <vector>

using std::queue;
using std::vector;

int bipartite(vector<vector<int> > &adj) {
  // write your code here
  int n = adj.size();
  queue<int> q;
  vector<int> colors(n, 0);  // 0 uncolored, 1 white, -1 black.
  for (int i = 0; i < n; i++) {
    if (colors[i] != 0) continue;
    q.push(i);
    colors[i] = 1;
    while (!q.empty()) {
      int v = q.front();
      q.pop();
      for (int w : adj[v]) {
        if (colors[w] == 0) {
          colors[w] = -colors[v];
          q.push(w);
        } else if (colors[w] == colors[v]) {
          return 0;
        }
      }
    }
  }
  return 1;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << bipartite(adj);
}
