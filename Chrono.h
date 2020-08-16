#pragma once

#include "std_lib_facilities.h"

namespace Chrono {

    enum class Month {
        jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
    };

    Month operator++(Month& m);
    Month operator--(Month& m);

    enum class Day {
        sunday, monday, tuesday, wednesday, thursday, friday, saturday
    };

    const vector<string> days{ "sunday", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday" };

    class Date {
    public:
        class Invalid { };                               // to throw as exception

        Date(int y, Month m, int d);         // check for valid date and initialize
        Date();                                              // default constructor
        // the default copy operations are fine

        // nonmodifying operations:
        int day() const;
        Month month() const;
        int year() const;
        void current_date(int& cd, Month& cm, int& cy) const;
        int date() const;

        // modifying operations:
        void add_day(int n);
        void add_month(int n);
        void add_year(int n);
    private:
        long int d;
    };

    bool is_date(int y, Month m, int d);  // true for valid date
    bool leapyear(int y);           // true if y is a leap year

    bool operator==(const Date& a, const Date& b);
    bool operator!=(const Date& a, const Date& b);

    ostream& operator<<(ostream& os, const Date& d);
    ostream& operator<<(ostream& os, const Month& m);
    ostream& operator<<(ostream& os, const Day& d);

    istream& operator>>(istream& is, Date& dd);

    Day day_of_week(const Date& d);
    Date next_Sunday(const Date& d);
    Date next_weekday(const Date& d);
    int days_in_month(const Month& m, int y);
    int week_of_year(const Date& d);
    int days_in_year(const int& y);
}