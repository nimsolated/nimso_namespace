#include "nimso.h"

int main()
{
	srand((unsigned int)time(0));

	nimso::Array<int> arr(5);
	for (size_t i = 0; i < arr.size(); i++) {
		arr[i] = (int)((i + 1) * 2);
	}
	nimso::Dish<int> dish(arr);
	std::cout << dish << std::endl;
	std::cout << dish.eat() << std::endl;
	std::cout << dish << std::endl;
	std::cout << dish.eat() << std::endl;
	std::cout << dish << std::endl;
	dish.serve(arr);
	std::cout << dish << std::endl;
	std::cout << dish.eat() << std::endl;
	std::cout << dish << std::endl;
	std::cout << dish.eat() << std::endl;
	std::cout << dish << std::endl;
	dish.serve(arr);
	std::cout << dish << std::endl;
	std::cout << dish.eat() << std::endl;
	std::cout << dish.eat() << std::endl;
	std::cout << dish.eat() << std::endl;
	std::cout << dish.eat() << std::endl;
	std::cout << dish << std::endl;
	std::cout << dish.eat() << std::endl;
	std::cout << dish << std::endl;
	nimso::Array<int> arr2(10);
	for (size_t i = 0; i < arr2.size(); i++) {
		arr2[i] = (int)(i + 1);
	}
	dish.serve(arr2);
	std::cout << dish << std::endl;

	nimso::Bowl<int> bowl(arr2);
	nimso::Bowl<int> bowl2 = bowl;
	std::cout << bowl << std::endl;
	bowl.mix();
	std::cout << bowl << std::endl;

	std::cout << bowl2 << std::endl;
	bowl2.mix();
	std::cout << bowl2 << std::endl;
}