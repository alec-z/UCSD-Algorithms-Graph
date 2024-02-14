#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;


// 1 based minQ
class IndexMinQ {
  int size = 0;
  vector<int> min_q_v;
  vector<int> v_min_q_index;
  vector<long long>& keys;
  int min_q_size;
  int v_nums;
  public:
  IndexMinQ(int v_nums, vector<long long>& dist): v_nums(v_nums), min_q_v(v_nums + 1),v_min_q_index(v_nums, 0), keys(dist), min_q_size(0) {

  }
  void swim(int v) {
    int index = v_min_q_index[v];
    while (index > 1) {
      int parent = index / 2;
      if (keys[min_q_v[index]] < keys[min_q_v[parent]]) {
        std::swap(min_q_v[index], min_q_v[parent]);
        std::swap(v_min_q_index[min_q_v[index]], v_min_q_index[min_q_v[parent]]);
        index = parent;
      } else {
        break;
      }
    }
  }

  bool empty() {
    return min_q_size == 0;
  }

  bool contains(int v) {
    return v_min_q_index[v] > 0;
  }

  void push(int v) {
    min_q_v[++min_q_size] = v;
    v_min_q_index[v] = min_q_size;
    swim(v);
  }

  int pop() {
    int res = min_q_v[1];
    std::swap(min_q_v[1], min_q_v[min_q_size--]);
    v_min_q_index[res] = 0;
    v_min_q_index[min_q_v[1]] = 1;    
    int i = 1, j = 2;
    while (j <= min_q_size) {
      if (j + 1 <= min_q_size && keys[min_q_v[j + 1]] < keys[min_q_v[j]]) j++;
      if (keys[min_q_v[i]] > keys[min_q_v[j]]) {
        std::swap(min_q_v[i], min_q_v[j]);
        std::swap(v_min_q_index[min_q_v[i]], v_min_q_index[min_q_v[j]]);
        i = j;
        j = 2 * i;
      } else {
        break;
      }
    }
    return res;
  }

};
#define MAX_INT std::numeric_limits<int>::max()
long long distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t) {
  //write your code her
  size_t n = adj.size();
  vector<long long> dist(n, MAX_INT);
  IndexMinQ min_q(n, dist);
  dist[s] = 0;
  min_q.push(s);
  while (!min_q.empty()) {
    int v = min_q.pop();
    for (int i = 0; i < adj[v].size(); i++) {
      int w = adj[v][i];
      int weight = cost[v][i];
      if (dist[v] + weight < dist[w]) {
        dist[w] = dist[v] + weight;
        if (min_q.contains(w)) {
          min_q.swim(w);
        } else {
          min_q.push(w);
        }
      }
    }
  }
  return dist[t] == MAX_INT? -1: dist[t];
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
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, cost, s, t);
}
