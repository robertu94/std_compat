#include <bit>

int main() {
  return std::endian::big != std::endian::little;
}
