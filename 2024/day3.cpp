#include <iostream>
#include <regex>
#include <sys/_types/_u_int64_t.h>
#include <utility>

int main() {
  std::string line;
  std::string input;
  while (std::getline(std::cin, line)) {
    if (!input.empty()) {
      input += "\n";
    }
    input += line;
  }

  std::regex mult(R"(mul\(\d+,\d+\))");
  std::smatch match;
  std::vector<std::pair<int, int>> matches;

  std::string::const_iterator search_start(input.begin());
  while (std::regex_search(search_start, input.cend(), match, mult)) {
    std::string inner = match.str().substr(4, match.str().size() - 5);
    size_t comma_pos = inner.find(",");
    int num1 = std::stoi(inner.substr(0, comma_pos));
    int num2 = std::stoi(inner.substr(comma_pos + 1));
    matches.emplace_back(num1, num2);
    search_start = match.suffix().first;
  }

  u_int64_t tot = 0;

  for (auto &str : matches) {
    tot += str.first * str.second;
  }

  std::cout << "total: " << tot << std::endl;

  return 0;
}
