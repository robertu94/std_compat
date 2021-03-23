#include <algorithm>

int main() {
	std::array<int, 4> a{1,2,3,4};
	std::array<int, 4> b{1,2,3,4};
	
	return std::equal(
		a.begin(), a.end(),
		b.begin(), b.end());
}
