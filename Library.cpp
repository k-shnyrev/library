#include "Library.h"

namespace Library {
	void Library::add_book(const Book& b)
	{
		books.push_back(b);
	}

	void Library::add_patron(const Patron& p)
	{
		patrons.push_back(p);
	}

	void Library::add_transaction(const Transaction& t)
	{
		transctions.push_back(t);
	}

	bool Library::is_absent(const Book& b)
	{
		/* ... */
	}
}