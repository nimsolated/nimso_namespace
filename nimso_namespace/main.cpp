#include "Nimso.h"

int main()
{
	Nimso::Queue<int> q1;
	int count = 0;
	while (++count <= 10) {
		q1.emplace(count);
	}

	std::cout << q1 << std::endl;
}
