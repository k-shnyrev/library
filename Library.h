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
		void add_transaction(const Transaction& t);
		bool is_absent(const Book& b);
	private:
		vector<Book> books;
		vector<Patron> patrons;
		vector<Transaction> transctions;
	};
}