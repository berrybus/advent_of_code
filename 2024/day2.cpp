#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

bool is_safe(vector<int> row) {
  if (row.size() < 2) {
    return true;
  }

  vector<int> diffs;

  for (int i = 1; i < row.size(); i++) {
    diffs.push_back(row[i] - row[i - 1]);
  }

  bool is_increasing =
      all_of(diffs.begin(), diffs.end(), [](int x) { return x > 0; });
  bool is_decreasing =
      all_of(diffs.begin(), diffs.end(), [](int x) { return x < 0; });

  bool in_range = all_of(diffs.begin(), diffs.end(),
                         [](int x) { return abs(x) >= 1 && abs(x) <= 3; });

  return (is_increasing || is_decreasing) && in_range;
}

int main() {
  vector<vector<int>> lines;

  string line;

  while (getline(cin, line)) {
    stringstream lineStream(line);
    vector<int> row;
    int val;

    while (lineStream >> val) {
      row.push_back(val);
    }

    lines.push_back(row);
  }

  int safe = 0;
  for (const auto &line : lines) {
    safe += is_safe(line);
  }

  cout << "Part 1 safe: " << safe << endl;

  safe = 0;

  // brute force, couldn't figure out a clean way to logic it
  for (const auto &line : lines) {
    if (is_safe(line)) {
      safe += 1;
    } else {
      for (int i = 0; i < line.size(); i++) {
        vector<int> new_line = line;
        new_line.erase(new_line.begin() + i);
        if (is_safe(new_line)) {
          safe += 1;
          break;
        }
      }
    }
  }

  cout << "Part 2 safe: " << safe << endl;

  return 0;
}
