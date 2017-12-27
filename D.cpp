
#include <algorithm>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <vector>

struct Point {
  int x;
  int y;

  Point() : x(0), y(0) {}

  Point(const int &x, const int &y) : x(x), y(y) {}

  bool operator<(const Point &point) const {
    if (this->x == point.x)
      return this->y < point.y;
    return this->x < point.x;
  }

  bool operator==(const Point &point) const {
    return this->x == point.x && this->y == point.y;
  }
};

int rotate(const Point &a, const Point &b, const Point &c) {
  return (b.x - a.x) * (c.y - b.y) - (b.y - a.y) * (c.x - b.x);
}

std::vector<int> convexHull(std::vector<Point> A) {
  int n = A.size();
  int *P = new int[n];
  for (int i = 0; i < n; i++) {
    P[i] = i;
  }
  for (int i = 1; i < n; i++) {
    if (A[P[i]].x < A[P[i]].x) {
      std::swap(P[i], P[0]);
    }
  }
  for (int i = 2; i < n; i++) {
    int j = i;
    while (j > 1 && rotate(A[P[0]], A[P[j - 1]], A[P[j]]) < 0) {
      std::swap(P[j], P[j - 1]);
      j--;
    }
  }
  std::vector<int> S;
  S.push_back(P[0]);
  S.push_back(P[1]);
  for (int i = 2; i < n; i++) {
    while (rotate(A[S[S.size() - 2]], A[S[S.size() - 1]], A[P[i]]) < 0) {
      S.pop_back();
    }
    S.push_back(P[i]);
  }
  return S;
}

int area(Point a, Point b, Point c) {
  return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool intersects(int a, int b, int c, int d) {
  if (a > b)
    std::swap(a, b);
  if (c > d)
    std::swap(c, d);
  return std::max(a, c) <= std::min(b, d);
}

bool intersects(Point a, Point b, Point c, Point d) {
  return intersects(a.x, b.x, c.x, d.x) && intersects(a.y, b.y, c.y, d.y) &&
         area(a, b, c) * area(a, b, d) <= 0 &&
         area(c, d, a) * area(c, d, b) <= 0;
}

int main() {
  srand(time(NULL));
  std::vector<Point> A;
  std::vector<Point> B;
  std::vector<Point> C;
  int n, x, y, t;
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    Point point;
    std::cin >> x >> y >> t;
    point.x = x;
    point.y = y;
    if (t == 1) {
      A.push_back(point);
    } else if (t == 2) {
      B.push_back(point);
    }
    C.push_back(point);
  }
  std::vector<int> hullA = convexHull(A);
  std::vector<int> hullB = convexHull(B);
  std::vector<int> hullC = convexHull(C);

  if (A.size() == 0 || B.size() == 0) {
    std::cout << "Yes" << std::endl;
    return 0;
  }
  if (A.size() == 1 && B.size() == 1) {
    if (A[0] == B[0]) {
      std::cout << "No" << std::endl;
    } else {
      std::cout << "Yes" << std::endl;
    }
    return 0;
  }
  if (A.size() > 1 && B.size() > 1) {
    for (int i = 0; i < hullA.size(); ++i) {
      for (int j = 0; j < hullB.size(); ++j) {
        Point a1, a2, b1, b2;
        if (i == hullA.size() - 1) {
          a2 = A[hullA[0]];
        } else {
          a2 = A[hullA[i + 1]];
        }
        if (j == hullB.size() - 1) {
          b2 = B[hullB[0]];
        } else {
          b2 = B[hullB[j + 1]];
        }
        a1 = A[hullA[i]];
        b1 = B[hullB[j]];
        if (intersects(a1, a2, b1, b2)) {
          std::cout << "No" << std::endl;
          return 0;
        }
      }
    }
  }
  if (hullC == hullA || hullC == hullB) {
    std::cout << "No" << std::endl;
    return 0;
  }
  if (A.size() == 1 || B.size() == 1) {
    std::cout << "No" << std::endl;
    
    return 0;
  }
  if (A.size() == 0 || B.size() == 0) {
    std::cout << "Yes" << std::endl;
    
    return 0;
  }
  std::cout << "Yes" << std::endl;
  return 0;
}