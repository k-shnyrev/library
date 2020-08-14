#include "Patron.h"

namespace Library {

	Patron::Patron(string nm, int no, double p)
		: name{ nm }, number{ no }, payment{ p }
	{
	};

	void Patron::set_payment(double p)
	{
		payment = p;
	}

	string Patron::get_name() const
	{
		return name;
	}

	int Patron::get_number() const
	{
		return number;
	}

	double Patron::get_payment() const
	{
		return payment;
	}

	bool Patron::has_paid() const
	{
		return (payment == 0);
	}
}