#include "Book.h"

namespace Books {
	Book::Book(string i, string t, string a, Chrono::Date rd, bool ab, Genre g)
		:isbn{ i }, title{ t }, author{ a }, reg_date{ rd }, absent{ ab }, genre{ g }
	{
		if (!correct_isbn(i))
			throw Invalid{};
	}

	bool correct_isbn(const string& isbn) {
		int k = 0;
		int p = 0;
		for (int i = 0; i < isbn.size() && (k < 3); ++i) {
			if (!isdigit(isbn[i]))
				if (isbn[i] == '-') {
					++k;
					p = i;
				}
				else {
					return false;
				}
		}
		return (k == 3) && (p == isbn.size() - 2) && isalnum(isbn[isbn.size() - 1]);
	}

	bool operator==(const Book& a, const Book& b)
	{
		return a.get_isbn() == b.get_isbn();
	}

	bool operator!=(const Book& a, const Book& b)
	{
		return !(a == b);
	}

	ostream& operator<<(ostream& os, const Book& b)
	{
		return os << "title: " << b.get_title() << '\n'
			<< "author: " << b.get_author() << '\n'
			<< "isbn: " << b.get_isbn() << '\n'
			<< "genre: " << b.get_genre() << '\n';
	}

	ostream& operator<<(ostream& os, const Genre& g)
	{
		return os << genres_list[int(g)];
	}

	Book add_book()
		try {
		cout << "isbn: ";
		string isbn;
		cin >> isbn;
		if (!correct_isbn(isbn))
			throw Book::Invalid{};
		cout << "title: ";
		string title;
		cin >> title;
		cout << "author: ";
		string author;
		cin >> author;
		cout << "registration date:\n";
		cout << "year: ";
		int year;
		if (!(cin >> year))
			error("expected year");
		cout << "month (int from 1 to 12): ";
		int m;
		if (!(cin >> m))
			error("expected month");
		cout << "day: ";
		int day;
		if (!(cin >> day))
			error("expected day");
		Chrono::Date reg_date{ year, Chrono::Month(m), day };
		cout << "is book absent? (y or N): ";
		char ab;
		cin >> ab;
		bool absent = (ab == 'y' || ab == 'Y');
		cout << "Choose genre:\n"
			<< "0 - fiction (default)\n"
			<< "1 - prose\n"
			<< "2 - periodic\n"
			<< "3 - biography\n"
			<< "4 - children\n";
		int g;
		cin >> g;
		Genre genre = Genre::fiction;
		switch (g) {
		case 1: case 2: case 3: case 4:
			genre = Genre(g);
			break;
		default:
			genre = Genre(0);
		}
		return Book{ isbn, title, author, reg_date, absent, genre };
	}
	catch (Book::Invalid) {
		error("incorrect book data");
	}
}