#include "Nimso.h"

int main()
{
	Nimso::Stack<char> stk;

	std::cout << stk << std::endl;
	std::cout << "Stack is empty: " << stk.isEmpty() << std::endl;
	std::cout << "Stack's size: " << stk.size() << std::endl;

	char c = 'N';
	char exclamation = '!';
	stk.push(c); stk.emplace('i'); stk.emplace('m'); stk.push(exclamation);

	std::cout << stk << std::endl;
	std::cout << "Stack is empty: " << stk.isEmpty() << std::endl;
	std::cout << "Stack's size: " << stk.size() << std::endl;

	char* charray = new char[5];

	size_t pos = 0;
	while (!stk.isEmpty()) {
		charray[pos] = stk.pop();
		pos++;
	}
	charray[4] = '\0';

	std::cout << stk << std::endl;
	std::cout << "Stack is empty: " << stk.isEmpty() << std::endl;
	std::cout << "Stack's size: " << stk.size() << std::endl;

	std::string reversedNim(charray);
	std::cout << "Nim in reverse: " << reversedNim;
	std::cout << std::endl;

	Nimso::Stack<char> stk2;
	stk.emplace('y'); stk.emplace('e'); stk.emplace('s');
	stk2.emplace('n'); stk2.emplace('o');
	stk.swap(stk2);

	std::cout << stk << std::endl;
	std::cout << stk2 << std::endl;

	delete[] charray;
}
