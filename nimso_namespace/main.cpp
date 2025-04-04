#include "nimso.h"

int main()
{
	nimso::DoublyLinkedList<int> list1;
	nimso::DoublyLinkedList<int> list2;

	list1.emplaceBack(3);
	list1.emplaceBack(6);
	list1.emplaceBack(9);
	list1.emplaceBack(12);
	list1.emplaceBack(15);

	std::cout << list1 << std::endl;
	std::cout << list2 << std::endl;
	list1.split(list2);
	std::cout << list1 << std::endl;
	std::cout << list2 << std::endl;

	nimso::DoublyLinkedList<int> list3;
	list1.split(list3);
	std::cout << list1 << std::endl;
	std::cout << list3 << std::endl;

	nimso::DoublyLinkedList<int> list4;
	if (list3.split(list4) == nimso::ERROR_FAIL) {
		nimso::display("Nonono!");
	}
}