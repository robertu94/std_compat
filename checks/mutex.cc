#include <mutex>

int main() {
  std::mutex m;
  std::unique_lock<std::mutex> ul;
  std::lock_guard<std::mutex> lg(m);
}
