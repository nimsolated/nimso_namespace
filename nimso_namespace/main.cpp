#include "Nimso.h"

int main()
{
	Nimso::DoublyLinkedList<int> myList;
	myList.emplace(3); myList.emplace(10); // [10, 3]
	myList.emplaceBack(15); myList.emplaceBack(27); // [10, 3, 15, 27]
	myList.pop(); // [3, 15, 27]
	myList.popBack(); // [3, 15]
	int num = 8;
	myList.push(num); // [8, 3, 15]

	std::cout << myList << std::endl << std::endl;

	std::cout << "found 3: " << myList.find(3) << std::endl
			  << "found 27: " << myList.find(27) << std::endl;

	std::cout << "15\'s position: " << myList.findPos(15) << std::endl
			  << "8\'s position: " << myList.findPos(8) << std::endl
			  << "27\'s position: " << myList.findPos(27) << std::endl;

	std::cout << "deleted 3: " << myList.findDelete(3) << std::endl; // [8, 15]
	std::cout << "deleted 99: " << myList.findDelete(99) << std::endl;
	std::cout << "inserted 19 after 8: "
			  << myList.findInsert(8, 19, Nimso::INSERT_AFTER) << std::endl; // [8, 19, 15]
	std::cout << "inserted 42 before 15: "
			  << myList.findInsert(15, 42, Nimso::INSERT_BEFORE) << std::endl; // [8, 19, 42, 15]
	std::cout << "inserted 1 before 42: "
			  << myList.findInsert(42, 1, Nimso::INSERT_BEFORE) << std::endl; // [8, 19, 1, 42, 15]

	std::cout << "replaced 42 with 6: " << myList.findReplace(42, 6) << std::endl; // [8, 19, 1, 6, 15]

	std::cout << std::endl << myList << std::endl;

	std::cout << "H: " << myList.head() << std::endl
			  << "T: " << myList.tail() << std::endl;
}
