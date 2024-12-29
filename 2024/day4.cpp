#include <iostream>
#include <sys/_types/_u_int64_t.h>
#include <vector>

std::string xmas = "XMAS";

bool check_direction(int r, int c, int dr, int dc,
                     std::vector<std::string> grid, int idx) {
  if (!(r >= 0 && r < grid.size() && c >= 0 && c < grid.at(0).size())) {
    return false;
  }

  if (grid[r][c] != xmas[idx]) {
    return false;
  }

  if (idx >= xmas.size() - 1) {
    return true;
  }

  return check_direction(r + dr, c + dc, dr, dc, grid, idx + 1);
}

void part_one(std::vector<std::string> grid) {
  u_int64_t cnt = 0;

  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid.at(0).size(); j++) {
      std::pair<int, int> dirs[8] = {{0, 1}, {0, -1}, {1, 1},  {-1, -1},
                                     {1, 0}, {-1, 0}, {-1, 1}, {1, -1}};

      for (auto &dir : dirs) {
        if (check_direction(i, j, dir.first, dir.second, grid, 0)) {
          cnt++;
        }
      }
    }
  }

  std::cout << "total: " << cnt << std::endl;
}

bool check_rest(std::vector<std::string> grid, int r1, int c1, int r2, int c2) {
  if (r1 >= 0 && r1 < grid.size() && r2 >= 0 && r2 < grid.size() && c1 >= 0 &&
      c1 < grid.at(0).size() && c2 >= 0 && c2 < grid.at(0).size()) {
    return (grid[r1][c1] == 'M' && grid[r2][c2] == 'S') ||
           (grid[r1][c1] == 'S' && grid[r2][c2] == 'M');
  } else {
    return false;
  }
}

void part_two(std::vector<std::string> grid) {
  u_int64_t cnt = 0;
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid.at(0).size(); j++) {
      if (grid[i][j] == 'A') {
        bool has_left = check_rest(grid, i - 1, j - 1, i + 1, j + 1);
        bool has_right = check_rest(grid, i - 1, j + 1, i + 1, j - 1);
        if (has_left && has_right) {
          cnt++;
        }
      }
    }
  }

  std::cout << "total: " << cnt << std::endl;
}

int main() {
  std::vector<std::string> grid;
  std::string line;
  while (std::getline(std::cin, line)) {
    grid.push_back(line);
  }

  part_two(grid);

  return 0;
}
