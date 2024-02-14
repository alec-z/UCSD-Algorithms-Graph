#include <iostream>
#include <vector>
#include <limits>

using std::vector;
#define MAX_INT std::numeric_limits<int>::max()
int negative_cycle(vector<vector<int> > &adj, vector<vector<int> > &cost) {
  //write your code here
  int n = adj.size();
  vector<int> distance(n, MAX_INT);
  vector<bool> mark(n, false);
  for (int s = 0; s < n; s++) {
    if (mark[s]) continue;
    for (int i = 0; i < n; i++) distance[i] = MAX_INT;
    distance[s] = 0;
    mark[s] = true;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        for (int k = 0; k < adj[j].size(); k++) {
          int je = adj[j][k];
          int jw = cost[j][k];
          if (distance[j] < MAX_INT && distance[j] + jw < distance[je]) {
            distance[je] = distance[j] + jw;
            mark[je] = true;
            if (i == n - 1) {
              return 1;
            }
          }
        }
      }
    }
  }
  return 0;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  std::cout << negative_cycle(adj, cost);
}
