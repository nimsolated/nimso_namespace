#include "Nimso.h"

int main()
{
	Nimso::LinkedList<int> myList;
	myList.emplace(3); myList.emplace(10); // [10, 3]
	myList.emplaceBack(15); myList.emplaceBack(27); // [10, 3, 15, 27]
	myList.pop(); // [3, 15, 27]
	myList.popBack(); // [3, 15]
	int num = 8;
	myList.push(num);

	std::cout << myList << std::endl;
	std::cout << "H: " << myList.head() << std::endl
			  << "T: " << myList.tail() << std::endl;
}
