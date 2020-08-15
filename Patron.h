#pragma once

#include "std_lib_facilities.h"

namespace Library {
	class Patron {
	public:
		Patron(string nm, int no, double p);
		void set_payment(double p);
		string get_name() const;
		int get_number() const;
		double get_payment() const;
		bool has_paid() const;
	private:
		string name;
		int number;
		double payment;
	};

	bool operator==(const Patron& a, const Patron& b);
	bool operator!=(const Patron& a, const Patron& b);
}