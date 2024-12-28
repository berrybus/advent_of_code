#include <iostream>
#include <regex>
#include <string>
#include <sys/_types/_u_int64_t.h>
#include <utility>

bool isNumber(const std::string &str) {
  return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
}

int main() {
  std::string line;
  std::string input;
  while (std::getline(std::cin, line)) {
    if (!input.empty()) {
      input += "\n";
    }
    input += line;
  }

  std::vector<std::pair<int, int>> matches;

  size_t start = 0;

  bool shouldAdd = true;
  while (start < input.size() - 5) {
    if (shouldAdd && input.substr(start, 4) == "mul(") {
      size_t close = input.find_first_of(")", start + 4);
      std::string inner = input.substr(start + 4, close - start - 4);
      size_t comma_pos = inner.find(",");
      std::string num1_str = inner.substr(0, comma_pos);
      std::string num2_str = inner.substr(comma_pos + 1);
      if (comma_pos < inner.size() && isNumber(num1_str) &&
          isNumber(num2_str)) {
        int num1 = std::stoi(num1_str);
        int num2 = std::stoi(num2_str);
        matches.emplace_back(num1, num2);
        start = close + 1;
      } else {
        start++;
      }
      // comment the below out if doing part t 1
    } else if (input.substr(start, 4) == "do()") {
      shouldAdd = true;
      start += 4;
    } else if (input.substr(start, 7) == "don't()") {
      shouldAdd = false;
      start += 7;
    } else {
      start++;
    }
  }

  u_int64_t tot = 0;

  for (auto &str : matches) {
    tot += str.first * str.second;
  }

  std::cout << "total: " << tot << std::endl;

  return 0;
}
