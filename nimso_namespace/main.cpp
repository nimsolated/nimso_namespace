#include "Nimso.h"

int main()
{
	const char* infix1 = "A-(B+V)*D+E/F";
	Nimso::PostfixExpression PE1(infix1);
	const char* infix2 = "Z+R/(U-T)*K^P";
	Nimso::PostfixExpression PE2(infix2);
	std::cout << PE1 << std::endl;
	std::cout << PE2 << std::endl;
}
