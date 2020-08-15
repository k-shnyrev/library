#pragma once

#include "std_lib_facilities.h"
#include "Book.h"
#include "Patron.h"

namespace Library {
	struct Transaction {
		Book book;
		Patron patron;
		Chrono::Date date;
	};
	
	class Library {
	public:
		void add_book(const Book& b);
		void add_patron(const Patron& p);
		void add_transaction(const Book& book, const Patron& patron, const Chrono::Date& date);
		bool is_absent(const Book& b);
		bool is_patron(const Patron& p) const;
		bool is_book(const Book& b) const;
		vector<Patron> debtors() const;
	private:
		vector<Book> books;
		vector<Patron> patrons;
		vector<Transaction> transactions;
	};
}