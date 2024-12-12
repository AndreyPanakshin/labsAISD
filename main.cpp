#include "list.h"

#include <iostream>

#include <iostream>

int sum_of_squares(int n) {
	int sum = 0;
	while (n > 0) {
		int digit = n % 10;
		sum += digit * digit;
		n /= 10;
	}
	return sum;
}

template<typename T>
bool is_happy(T value) {
	int number = value;
	int slow = number, fast = number;

	do {
		slow = sum_of_squares(slow);
		fast = sum_of_squares(sum_of_squares(fast));
	} while (slow != fast && slow != 1 && fast != 1);

	return slow == 1; 
}

int main() {
	LinkedList<int> list;
	list.push_tail(1);
	list.push_tail(2);
	list.push_head(0);
	list.push_tail(3);

	std::cout << "List: " << list << std::endl;

	LinkedList<int> list1(3,10,50);
	std::cout << "Another List: " << list1 << std::endl;

	LinkedList<int> list2(4, 8, 20);
	std::cout << "Another List: " << list2 << std::endl;

	list.pop_head();
	list.pop_tail();
	std::cout << "After pops: " << list << std::endl;


	list.push_tail(list1);
	std::cout << "Merged List: " << list << std::endl;

	list.push_head(list2);
	std::cout << "Merged List: " << list << std::endl;

	list.delete_node(2);
	std::cout << "After deleting 2s: " << list << std::endl;


	std::cout << "---------------------------------------------";
	int N = 30;

	LinkedList<int> numbers;
	for (int i = 1; i <= N; ++i) {
		numbers.push_tail(i);
	}

	std::cout << "\nUnhappy numbers in range [1; " << N << "]: ";
	for (size_t i = 0; i < numbers.get_size(); ++i) {
		int number = numbers[i];
		if (!is_happy(number)) {
			std::cout << number << " ";
		}
	}
	
	std::cout << std::endl;
	std::cout << "---------------------------------------------\n";




}



