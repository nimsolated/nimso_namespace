#include "nimso.h"

int main()
{
	const char* infix1 = "A-(B+V)*D+E/F";
	nimso::PostfixExpression PE1(infix1);
	const char* infix2 = "Z+R/(U-T)*K^P";
	nimso::PostfixExpression PE2(infix2);
	std::cout << PE1 << std::endl;
	std::cout << PE2 << std::endl;
}
