#include<stdlib.h>
#include<iostream>
#include <vector>
#include<stack>
#include"linklist.h"
#include"tree.h"
int main() {
	auto vec1 = { 1,2,5 };
	std::vector<int> vec2 = {5,2,1};
	LinkList ll1(vec1);
	LinkList ll2(vec2);
	auto op = LinkList::greaterNext(&ll2);
	ll2.traverse_and_print();
	for (auto e : op) {
		std::cout << "Element " << e << std::endl;
	}
	return 0;
}