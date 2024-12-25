#include <cmath>
#include <iostream>

class Vec3 {
private:
  double m_x{};
  double m_y{};
  double m_z{};

public:
  Vec3(double x = 0, double y = 0, double z = 0) {
    m_x = x;
    m_y = y;
    m_z = z;
  }

  // Copy constructor, assignment operator, and destructor defaults
  // should be sufficient?
  Vec3(const Vec3 &other) = default;

  Vec3 &operator=(const Vec3 &other) = default;

  ~Vec3() = default;

  friend std::ostream &operator<<(std::ostream &out, const Vec3 &vec3);

  double magnitude() { return std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z); }

  Vec3 operator+(const Vec3 &other) {
    // Why is accessing other.m_x valid, isn't it private??
    return Vec3(m_x + other.m_x, m_y + other.m_y, m_z + other.m_z);
  }
};

// Is this a good place to add the << override or should you stuff all the cout
// overrides in a single file?
std::ostream &operator<<(std::ostream &out, const Vec3 &vec3) {
  out << "(" << vec3.m_x << ", " << vec3.m_y << ", " << vec3.m_z << ")";
  return out;
}

int main() {
  Vec3 my_vec = Vec3(5, 2, 3);
  std::cout << my_vec << std::endl;
  std::cout << "magnitude: " << my_vec.magnitude() << std::endl;

  Vec3 another_vec = Vec3(-4, 2, 900);
  std::cout << "added: " << my_vec + another_vec << std::endl;

  return 0;
}
