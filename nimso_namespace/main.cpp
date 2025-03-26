#include "nimso.h"

int main()
{
	const size_t N = 5;
	int arr[N] = { 3, 5, 6, 8, 9 };
	nimso::display(nimso::binarySearchRecursive(arr, 0, N - 1, 5));
	nimso::display(nimso::binarySearch(arr, 0, N - 1, 6));
	nimso::display(nimso::binarySearchRecursive(arr, 0, N - 1, 3));
	nimso::display(nimso::binarySearch(arr, 0, N - 1, 9));
	nimso::display(nimso::binarySearchRecursive(arr, 0, N - 1, 12));
	nimso::display(nimso::seqSearch(arr, 9, N));
	nimso::display(nimso::seqSearch(arr, 6, N));
	nimso::display(nimso::seqSearch(arr, 3, N));
}
