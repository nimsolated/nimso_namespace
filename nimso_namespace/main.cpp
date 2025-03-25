#include "nimso.h"

int main()
{
	nimso::SinglyLinkedList<int> list;
	list.emplace(3); // [3]
	std::cout << list << std::endl;
	list.push(17); // [17, 3]
	std::cout << list << std::endl;
	list.emplaceBack(2); // [17, 3, 2]
	std::cout << list << std::endl;
	list.pushBack(4); // [17, 3, 2, 4]
	std::cout << list << std::endl;
	list.pop(); // [3, 2, 4]
	std::cout << list << std::endl;
	list.popBack(); // [3, 2]
	std::cout << list << std::endl;
	list.emplace(9); // [9, 3, 2]
	std::cout << list << std::endl;
	list.findInsert(3, 15, nimso::INSERT_AFTER); // [9, 3, 15, 2]
	std::cout << list << std::endl;
	list.findInsert(15, 42, nimso::INSERT_BEFORE); // [9, 3, 42, 15, 2]
	std::cout << list << std::endl;
	list.findDelete(2); // [9, 3, 42, 15]
	std::cout << list << std::endl;
	list.findDelete(9); // [3, 42, 15]
	std::cout << list << std::endl;
	list.findDelete(42); // [3, 15]
	std::cout << list << std::endl;
	list.popBack(); // [3]
	std::cout << list << std::endl;
	list.popBack(); // []
	std::cout << list << std::endl;
}
