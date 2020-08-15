/*
Library base

Exercises from chapter 9 "Programming Principles and Practice Using C++" by B. Stroustrup.
*/

#include "std_lib_facilities.h" 
#include "Library.h"

int main()
try {
	Chrono::Date d;
	cin >> d;
	cout << d << '\n' << Chrono::day_of_week(d) << '\n';
	d.add_day(365);
	cout << d << '\n';
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