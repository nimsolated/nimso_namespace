#include "nimso.h"

int main()
{
	nimso::Array<int> myArray(5);
	for (size_t i = 0; i < myArray.size(); i++) {
		myArray[i] = (int)((i + 1) * 2);
	}
	std::cout << myArray.size() << std::endl;
	std::cout << myArray << std::endl;
	myArray.resize(8);
	std::cout << myArray.size() << std::endl;
	std::cout << myArray << std::endl;
	myArray.resize(5);
	std::cout << myArray.size() << std::endl;
	std::cout << myArray << std::endl;
	std::cout << myArray[2] << std::endl;
	myArray[2] = myArray[0] * myArray.at(myArray.size() - 1);
	std::cout << myArray << std::endl;
	std::cout << myArray.at(2) << std::endl;

	myArray.swapElements(0, myArray.size() - 1);

	std::cout << myArray.size() << std::endl;
	std::cout << "myArray: " << myArray << std::endl;

	nimso::Array<int> mySecondArray(2);
	mySecondArray[0] = 30;
	mySecondArray[1] = 90;

	std::cout << myArray.size() << std::endl;
	std::cout << "myArray: " << myArray << std::endl;
	std::cout << mySecondArray.size() << std::endl;
	std::cout << "mySecondArray: " << mySecondArray << std::endl;
	myArray.swap(mySecondArray);
	std::cout << myArray.size() << std::endl;
	std::cout << "myArray: " << myArray << std::endl;
	std::cout << mySecondArray.size() << std::endl;
	std::cout << "mySecondArray: " << mySecondArray << std::endl;

	nimso::Array<int> copyOfMyArray(myArray);
	std::cout << copyOfMyArray.size() << std::endl;
	std::cout << "Copy of myArray: " << copyOfMyArray << std::endl;

	nimso::Array<int> anotherCopyOfMyArray = copyOfMyArray;
	std::cout << anotherCopyOfMyArray.size() << std::endl;
	std::cout << "Another copy of myArray: " << anotherCopyOfMyArray << std::endl;
}