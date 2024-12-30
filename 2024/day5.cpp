#include <algorithm>
#include <iostream>
#include <set>
#include <sstream>
#include <sys/_types/_u_int64_t.h>

int main() {
  std::string line;
  std::set<std::string> rules;
  std::vector<std::vector<int>> updates;
  while (std::getline(std::cin, line)) {
    if (line.empty()) {
      break;
    }
    rules.insert(line);
  }

  while (std::getline(std::cin, line)) {
    std::stringstream ss(line);
    std::string num;
    std::vector<int> update;
    while (std::getline(ss, num, ',')) {
      update.push_back(std::stoi(num));
    }
    updates.push_back(update);
  }

  std::vector<int> mids;
  auto cmp = [rules](int a, int b) {
    std::string less = std::to_string(a) + "|" + std::to_string(b);
    return rules.find(less) != rules.end();
  };
  for (auto &update : updates) {
    bool is_sorted = std::is_sorted(update.begin(), update.end(), cmp);

    // this is part 2, but part 1 is just this but is_sorted and don't sort
    if (!is_sorted) {
      std::sort(update.begin(), update.end(), cmp);
      mids.push_back(update[update.size() / 2]);
    }
  }

  u_int64_t sum = 0;
  for (int num : mids) {
    sum += num;
  }

  std::cout << sum << std::endl;

  return 0;
}
