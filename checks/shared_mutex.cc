#include <shared_mutex>


int main()
{
  std::shared_mutex mtx;
  std::shared_lock<std::shared_mutex> lock(mtx);
  
}
