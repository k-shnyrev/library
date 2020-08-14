/*
Library base

Exercises from chapter 9 "Programming Principles and Practice Using C++" by B. Stroustrup.
*/

#include "Book.h"

int main()
try {
	cout << "bk1:\n";
	Books::Book bk1 = Books::add_book();
	cout << "bk2:\n";
	Books::Book bk2 = Books::add_book();
	cout << "bk1\n" << bk1 << "\nbk2\n" << bk2;
	cout << "bk1 == bk2: " << (bk1 == bk2) << '\n';
	return 0;
}
catch (runtime_error& e) {
	cerr << "Runtime error: " << e.what() << '\n';
	return 1;
}
catch (...) {
	cerr << "Unknown runtime error\n";
	return 2;
}