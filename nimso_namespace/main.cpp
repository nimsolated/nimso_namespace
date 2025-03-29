#include "nimso.h"
#include <string>

int main()
{
	nimso::Node<int>* h = new nimso::Node<int>(3, new nimso::Node<int>(6, new nimso::Node<int>(9)));
	nimso::SinglyLinkedList<int>* list = new nimso::SinglyLinkedList<int>(h);
	nimso::display(list->size());
	std::cout << *list;
}
