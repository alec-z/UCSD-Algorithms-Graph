#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using std::vector;
using std::queue;
#define MAX_INT std::numeric_limits<int>::max()

int distance(vector<vector<int> > &adj, int s, int t) {
  //write your code here
  queue<int> q;
  int n = adj.size();
  vector<int> distances(n, MAX_INT);
  q.push(s);
  distances[s] = 0;
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    for (int w: adj[v]) {
      if (distances[w] == MAX_INT) {
        distances[w] = distances[v] + 1;
        q.push(w);
      }
    }
  }
  return distances[t] == MAX_INT ? -1 : distances[t];
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
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, s, t);
}
