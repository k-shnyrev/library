#pragma once

#include "std_lib_facilities.h"
#include "Chrono.h"

namespace Library {
	enum class Genre {
		fiction, prose, periodic, biography, children
	};

	const vector<string> genres_list{ "fiction", "prose", "periodic", "biography", "children" };

	class Book {
	public:
		class Invalid { }; // to throw as exception

		Book(string i, string t, string a, Chrono::Date rd, bool ab, Genre g); // check valid isbn and initialize

		string get_isbn() const;
		string get_title() const;
		string get_author() const;
		Chrono::Date get_reg_date() const;
		bool is_absent() const;
		Genre get_genre() const;
	private:
		string isbn;
		string title;
		string author;
		Chrono::Date reg_date;
		bool absent;
		Genre genre;
	};

	bool correct_isbn(const string& isbn);

	bool operator==(const Book& a, const Book& b);

	bool operator!=(const Book& a, const Book& b);

	ostream& operator<<(ostream& os, const Book& b);
	ostream& operator<<(ostream& os, const Genre& g);

	Book add_book();
}