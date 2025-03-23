#include "Nimso.h"

int main()
{
	Nimso::TowerOfHanoi toh;
	std::cout << toh.getNumMoves() << std::endl;
	toh.start(4, 'A', 'C', 'B');
	std::cout << toh.getNumMoves() << std::endl;
	Nimso::TowerOfHanoi toh2(toh);
	std::cout << toh2.getNumMoves() << std::endl;
	toh.resetNumMoves();
	std::cout << toh.getNumMoves() << std::endl;
	std::cout << toh2.getNumMoves() << std::endl;

	Nimso::Stack<char> stk1;
	Nimso::Stack<char> stk2;
	std::cout << "stk1 size: " << stk1.size() << std::endl;
	std::cout << "stk2 size: " << stk2.size() << std::endl;
	if (stk1.swap(stk2) == Nimso::ERROR_PASS) {
		std::cout << "Good swap.\n";
	}
	else {
		std::cout << "Bad swap.\n";
	}
	stk1.emplace('A'); stk1.emplace('B');
	stk2.emplace('C'); stk2.emplace('D'); stk2.emplace('E');
	std::cout << "stk1 size: " << stk1.size() << std::endl;
	std::cout << "stk2 size: " << stk2.size() << std::endl;
	if (stk1.swap(stk2) == Nimso::ERROR_PASS) {
		std::cout << "Good swap.\n";
	}
	else {
		std::cout << "Bad swap.\n";
	}
	if (stk1.swap(stk1) == Nimso::ERROR_FAIL) {
		std::cout << "Bad swap. (self-reference)\n";
	}
}
