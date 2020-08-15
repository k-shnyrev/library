#include "Library.h"

namespace Library {
	void Library::add_book(const Book& b)
	{
		if (is_book(b)) {
			cerr << "already have that book\n";
			return;
		}
		books.push_back(b);
	}

	void Library::add_patron(const Patron& p)
	{
		if (is_patron(p)) {
			cerr << "already a patron'n";
			return;
		}
		patrons.push_back(p);
	}

	void Library::add_transaction(const Book& book, const Patron& patron, const Chrono::Date& date)
	{
		if (!is_patron(patron)) {
			cerr << "not a patron\n";
			return;
		}
		if (!(patron.has_paid())) {
			cerr << "the patron has not paid yet\n";
			return;
		}
		if (!is_book(book)) {
			cerr << "book doesn't exist\n";
			return;
		}
		if (is_absent(book)) {
			cerr << "book is already taken\n";
			return;
		}
		Transaction t{ book, patron, date };
		transactions.push_back(t);
	}

	bool Library::is_absent(const Book& b)
	{
		if (!is_book(b)) {
			cerr << "book doesn't exist\n";
			return true;
		}
		for (Transaction t : transactions)
			if (t.book == b)
				return true;
		return false;
	}

	bool Library::is_patron(const Patron& p) const
	{
		for (Patron tmp : patrons)
			if (tmp == p)
				return true;
		return false;
	}

	bool Library::is_book(const Book& b) const
	{
		for (Book tmp : books)
			if (tmp == b)
				return true;
		return false;
	}

	vector<Patron> Library::debtors() const
	{
		vector<Patron> res;
		for (Transaction t : transactions) {
			res.push_back(t.patron);
		}
		return res;
	}
}