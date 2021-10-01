#include <vector>
#include <iterator>
#include <iostream>
int main()
{
  std::vector<int> v;
  v.push_back(1);

  for(std::vector<int>::const_iterator it = std::cbegin(v); it != std::cend(v); ++it) {
    std::cout << *it << std::endl;
  }
}
