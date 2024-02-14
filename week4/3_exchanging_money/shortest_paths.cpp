#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using std::pair;
using std::priority_queue;
using std::queue;
using std::vector;

#define MAX_INT std::numeric_limits<long long>::max()
#define MIN_INT std::numeric_limits<long long>::min()

void shortest_paths(vector<vector<int> > &adj, vector<vector<int> > &cost,
                    int s, vector<long long> &distance, vector<int> &reachable,
                    vector<int> &shortest) {
  // write your code here
  int n = adj.size();
  for (int i = 0; i < n; i++) distance[i] = MAX_INT;
  distance[s] = 0;

  queue<int> q;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < adj[j].size(); k++) {
        int je = adj[j][k];
        int jw = cost[j][k];
        if (distance[j] < MAX_INT && distance[j] + jw < distance[je]) {
          distance[je] = distance[j] + jw;
          if (i == n - 1) {
            q.push(je);
            distance[je] = MIN_INT;
          }
        }
      }
    }
  }

  while (!q.empty()) {
    int v = q.front();
    q.pop();
    for (int w: adj[v]) {
      if (distance[w] != MIN_INT) {
        q.push(w);
        distance[w] = MIN_INT;
      }
    }
  }
  for (int i = 0; i < n; i++) {
    if (distance[i] != MAX_INT) {
      reachable[i] = 1;
    }
    if (distance[i] == MIN_INT || distance[i] == MAX_INT) {
      shortest[i] = 0;
    }
  }
}

int main() {
  int n, m, s;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  std::cin >> s;
  s--;
  vector<long long> distance(n, std::numeric_limits<long long>::max());
  vector<int> reachable(n, 0);
  vector<int> shortest(n, 1);
  shortest_paths(adj, cost, s, distance, reachable, shortest);
  for (int i = 0; i < n; i++) {
    if (!reachable[i]) {
      std::cout << "*\n";
    } else if (!shortest[i]) {
      std::cout << "-\n";
    } else {
      std::cout << distance[i] << "\n";
    }
  }
}
