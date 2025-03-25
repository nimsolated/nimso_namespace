#include "nimso.h"

template <typename Variant>
void display(Variant& item) {
	try {
		std::cout << item << std::endl;
	}
	catch (...) {
		std::cout << "Unknown error in display(item) function. Does the item parameter have an operator<< overload?" << std::endl;
		return;
	}
}

int main()
{
	nimso::DoublyLinkedList<int> list;
	list.emplace(3); // [3]
	display(list);
	list.push(17); // [17, 3]
	display(list);
	list.emplaceBack(2); // [17, 3, 2]
	display(list);
	list.pushBack(4); // [17, 3, 2, 4]
	display(list);
	list.pop(); // [3, 2, 4]
	display(list);
	list.popBack(); // [3, 2]
	display(list);
	list.emplace(9); // [9, 3, 2]
	display(list);
	list.findInsert(3, 15, nimso::INSERT_AFTER); // [9, 3, 15, 2]
	display(list);
	list.findInsert(15, 42, nimso::INSERT_BEFORE); // [9, 3, 42, 15, 2]
	display(list);
	list.swapEnds(); // [2, 3, 42, 15, 9]
	display(list);
	list.popBack(); // [2, 3, 42, 15]
	display(list);
	list.popBack(); // [2, 3, 42]
	display(list);
	list.popBack(); // [2, 3]
	display(list);
	list.swapEnds(); // [3, 2]
	display(list);
}
