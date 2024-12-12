#include "list.h"

void solve_hanoi(int n, LinkedList<int>& source, LinkedList<int>& target, LinkedList<int>& auxiliary, const std::string& source_name, const std::string& target_name, const std::string& auxiliary_name) {
	if (n == 1) {
		int disk = source[source.get_size() - 1];
		source.pop_tail();
		target.push_tail(disk);
		std::cout <<"Moved disk " << disk << " from " << source_name << " to " << target_name<<"\t"<<" source->" << source << "\t" << " target->" << target << "\t" << " aux->" << auxiliary << "\n";
		return;
	}
	solve_hanoi(n - 1, source, auxiliary, target, source_name, auxiliary_name, target_name);
	int disk = source[source.get_size() - 1];
	source.pop_tail();
	target.push_tail(disk);
	std::cout << "Moved disk " << disk << " from " << source_name << " to " << target_name << "\t" << " source->" << source << "\t" << " target->" << target << "\t" << " aux->" << auxiliary << "\n";

	solve_hanoi(n - 1, auxiliary, target, source, auxiliary_name, target_name, source_name);
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

	std::cout << std::endl;
	LinkedList<int> tower1, tower2, tower3;
	for (int i = 3; i > 0; --i) {
		tower1.push_tail(i);
	}
	solve_hanoi(3, tower1, tower2, tower3, "source","target","auxiliary");
	
	std::cout << std::endl;
	std::cout << "---------------------------------------------\n";
}




