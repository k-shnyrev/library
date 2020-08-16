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
	cout << d << '\n';
	cout << Chrono::day_of_week(d) << '\n';
	cout << "week " << week_of_year(d) << '\n';
	d.add_day(1);
	cout << "++d: " << d << '\n';
	d.add_month(1);
	cout << "++m: " << d << '\n';
	d.add_year(1);
	cout << "++y: " << d << '\n';
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