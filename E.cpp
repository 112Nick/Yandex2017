#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

class SegmentTree {
public:
  SegmentTree(int n) {
    this->n = n;
    a = std::vector<std::pair<long long, long long>>(4 * n, {1, 0});
  }

  long long getMax(int l, int r) { return getMax(1, 0, n - 1, l, r, 0); }

  void setValue(int l, int r, long long value) {
    setValue(1, 0, n - 1, l, r, value);
  }

private:
  int n;
  std::vector<std::pair<long long, long long>> a;

  long long getMax(int v, int tl, int tr, int l, int r, long long value) {
    if (l > r) {
      return 0;
    }
    a[v].first = max(value, a[v].first);
    value = max(value, a[v].second);
    if (l == tl && r == tr) {
      a[v].second = value;
      return a[v].first;
    }
    int tm = (tl + tr) / 2;
    return max(getMax(v * 2, tl, tm, l, min(r, tm), value),
               getMax(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, value));
  }

  void setValue(int v, int tl, int tr, int l, int r, long long value) {
    if (l > r) {
      return;
    }
    a[v].first = max(value, a[v].first);
    value = max(value, a[v].second);
    if (l == tl && r == tr) {
      a[v].second = value;
      return;
    }
    int tm = (tl + tr) / 2;
    setValue(v * 2, tl, tm, l, min(r, tm), value);
    setValue(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, value);
  }
};

int main() {
  int n, m;
  std::cin >> n >> m;
  SegmentTree tree(n);
  for (int i = 0; i < m; ++i) {
    long long s, d;
    int l, r;
    std::cin >> s >> l >> r >> d;
    --l, --r;
    long long cur = tree.getMax(l, r);
    if (cur <= s) {
      tree.setValue(l, r, s + d);
      std::cout << "Yes" << std::endl;
    } else {
      std::cout << "No" << std::endl;
    }
  }
  return 0;
}