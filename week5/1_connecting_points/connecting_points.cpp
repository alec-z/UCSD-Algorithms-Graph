#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <queue>
#include <functional>

using std::vector;
using std::priority_queue;

struct Edge {
  int be;
  int en;
  double weight;
};

class UnionFind {
  vector<int> set;
  public:
    UnionFind(size_t size): set(size, 0) {
      for (int i = 0; i < set.size(); i++) set[i] = i;
    }
    int find(int x) {
      int p = x;
      while (p != set[p]) {
        set[p] = set[set[p]];
        p = set[p];
      }
      return p;
    }

    int merge(int x, int y) {
      int sx = find(x);
      int sy = find(y);
      set[sx] = sy;
      return sy;
    }
};

double minimum_distance(vector<int> x, vector<int> y) {
  double result = 0.;
  //write your code here
  int n = x.size();
  UnionFind uf(n);
  priority_queue<Edge, vector<Edge>, std::function<bool(const Edge &, const Edge &)> > q([](const Edge & a, const Edge &b) {
    return a.weight > b.weight;
  });

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      q.push(Edge{i, j, std::sqrt(((double)x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]) )});
    }
  }

  int e_size = 0;
  while (e_size < n - 1) {
    Edge e = q.top();
    q.pop();
    if (uf.find(e.be) != uf.find(e.en)) {
      e_size++;
      uf.merge(e.be, e.en);
      result += e.weight;
    }
  }
  return result;
}



int main() {
  size_t n;
  std::cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cout << std::setprecision(10) << minimum_distance(x, y) << std::endl;
}
