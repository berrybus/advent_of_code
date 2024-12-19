#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  vector<int> l;
  vector<int> r;
  unordered_map<int, int> map;
  int left, right;
  while (cin >> left >> right) {
    l.push_back(left);
    r.push_back(right);
    map[right]++;
  }

  sort(l.begin(), l.end());
  sort(r.begin(), r.end());

  int total = 0;

  for (int i = 0; i < l.size(); i++) {
    total += abs(l[i] - r[i]);
  }

  cout << "distance: " << total << endl;

  total = 0;

  for (int num : l) {
    total += num * map[num];
  }

  cout << "similarity: " << total << endl;

  return 0;
}
