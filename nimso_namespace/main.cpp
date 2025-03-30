#include "nimso.h"

int main()
{
	nimso::FreeRoam FR;
	FR.run();
	std::cout << FR.getPos() << std::endl << FR.getBorder() << std::endl;
}