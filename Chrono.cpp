#include "Chrono.h"

namespace Chrono {
    // member function definitions:

    Month operator++(Month& m)
    {
        m = (m == Month::dec) ? Month::jan : Month(int(m) + 1);
        return m;
    }

    Month operator--(Month& m)
    {
        m = (m == Month::jan) ? Month::dec : Month(int(m) - 1);
        return m;
    }

    Date::Date(int yy, Month mm, int dd)
        : y{ yy }, m{ mm }, d{ dd }
    {
        if (!is_date(yy, mm, dd)) throw Invalid{};
    }

    const Date& default_date()
    {
        static Date dd{ 2001,Month::jan,1 };   // start of 21st century
        return dd;
    }

    Date::Date()
        :y{ default_date().year() }, m{ default_date().month() }, d{ default_date().day() }
    {
    }

    void Date::add_day(int n)
    {
        while (n > 0) {
            if (d + n <= days_in_month(m, y)) {
                d += n;
                n = 0;
            }
            else {
                n -= days_in_month(m, y) - d + 1;
                d = 1;
                if (m < Month::dec)
                    ++m;
                else {
                    m = Month::jan;
                    ++y;
                }
            }
        }
        while (n < 0) {
            if (d + n > 0) {
                d += n;
                n = 0;
            }
            else {
                n += d;
                if (m > Month::jan)
                    --m;
                else {
                    m = Month::dec;
                    --y;
                }
                d = days_in_month(m, y);
            }
        }
    }

    void Date::add_month(int n)
    {
        // ...
    }

    void Date::add_year(int n)
    {
        if (m == Month::feb && d == 29 && !leapyear(y + n)) {             // beware of leap years!
            m = Month::mar;                                        // use March 1 instead of February 29
            d = 1;
        }
        y += n;
    }
    // helper functions:

    bool is_date(int y, Month m, int d)
    {
        // assume that y is valid

        if (d <= 0) return false;                        // d must be positive
        if (m < Month::jan || Month::dec < m) return false;

        if (days_in_month(m, y) < d) return false;

        return true;
    }

    bool leapyear(int y)
    {
        if (y % 400 == 0)
            return true;
        if (y % 100 == 0)
            return false;
        if (y % 4 == 0)
            return true;
        return false;
    }

    bool operator==(const Date& a, const Date& b)
    {
        return a.year() == b.year()
            && a.month() == b.month()
            && a.day() == b.day();
    }

    bool operator!=(const Date& a, const Date& b)
    {
        return !(a == b);
    }

    ostream& operator<<(ostream& os, const Date& d)
    {
        return os << '(' << d.year()
            << ',' << d.month()
            << ',' << d.day() << ')';
    }

    ostream& operator<<(ostream& os, const Month& m)
    {
        return os << int(m);
    }

    ostream& operator<<(ostream& os, const Day& d)
    {
        return os << days[int(d)];
    }

    istream& operator>>(istream& is, Date& dd)
    {
        int y, m, d;
        char ch1, ch2, ch3, ch4;
        is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;
        if (!is) return is;
        if (ch1 != '(' || ch2 != ',' || ch3 != ',' || ch4 != ')') {       // oops: format error
            is.clear(ios_base::failbit);                            // set the fail bit
            return is;
        }

        dd = Date(y, Month(m), d);                                   // update dd

        return is;
    }

    Day day_of_week(const Date& d)
    {
        int day = d.day();
        int m = int(d.month());
        int y = d.year();
        if (m < 3) {
            m += 10;
            y -= 1;
        }
        else
            m -= 2;
        int c = y / 100;
        return Day((day + 31 * m / 12 + y + y / 4 - y / 100 + y / 400) % 7);
    }

    Date next_Sunday(const Date& d)
    {
        Date r = d;
        r.add_day(7 - int(day_of_week(d)));
        return r;
    }

    Date next_weekday(const Date& d)
    {
        Date r = d;
        switch (day_of_week(d)) {
        case Day::friday:
            r.add_day(3);
            break;
        case Day::saturday:
            r.add_day(2);
            break;
        default:
            r.add_day(1);
        }
        return r;
    }

    int days_in_month(const Month& m, int y)
    {
        int days = 31;                  // most months have 31 days

        switch (m) {
        case Month::feb:                              // the length of February varies
            days = (leapyear(y)) ? 29 : 28;
            break;
        case Month::apr: case Month::jun: case Month::sep: case Month::nov:
            days = 30;               // the rest have 30 days
            break;
        }
        return days;
    }

    int week_of_year(const Date& d)
    {
        int days{ d.day() };
        int w{ 0 };
        if (d.month() > Month::jan)
            for (Month i = Month::jan; i < d.month(); ++i)
                days += days_in_month(i, d.year());
        Date start = Date(d.year(), Month::jan, 1);
        days -= (next_Sunday(start).day() - 7);
        return days / 7 + 1;
    }
}