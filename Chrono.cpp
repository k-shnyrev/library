#include <limits>
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

    void Date::current_date(int& cd, Month& cm, int& cy) const
    {
        int i = d;
        cd = 1;
        cm = Month::jan;
        cy = 1970;
        while (i > 0) {
            if (i >= days_in_year(cy)) {
                i -= days_in_year(cy);
                ++cy;
            }
            else if (i >= days_in_month(cm, cy)) {
                i -= days_in_month(cm, cy);
                if (cm == Month::dec)
                    ++cy;
                ++cm;
            }
            else {
                cd += i;
                i -= i;
            }
        }
    }

    int Date::day() const
    {
        int cd;
        Month cm;
        int cy;
        current_date(cd, cm, cy);
        return cd;
    }

    Month Date::month() const
    {
        int cd;
        Month cm;
        int cy;
        current_date(cd, cm, cy);
        return cm;
    }

    int Date::year() const
    {
        int cd;
        Month cm;
        int cy;
        current_date(cd, cm, cy);
        return cy;
    }

    int Date::date() const
    {
        return d;
    }

    Date::Date(int yy, Month mm, int dd) {
        if (!is_date(yy, mm, dd)) throw Invalid{};
        int r = 0;
        int rd = 1;
        Month rm = Month::jan;
        int ry = 1970;
        while (ry < yy) {
            r += days_in_year(ry);
            ++ry;
        }
        while (rm < mm) {
            r += days_in_month(rm, ry);
            ++rm;
        }
        r += dd - rd;
        rd = dd;
        d = r;
    }

    Date::Date()
        :d{ 0 }
    {
    }

    void Date::add_day(int n)
    {
        d += n;
    }

    void Date::add_month(int n)
    {
        Month cm = month();
        int cy = year();
        for (int i = 0; i < n; ++i) {
            d += days_in_month(cm, cy);
            if (cm == Month::dec)
                ++cy;
            ++cm;
        }
    }

    void Date::add_year(int n)
    {
        add_month(12 * n);
    }
    // helper functions:

    bool is_date(int y, Month m, int d)
    {
        // assume that y is valid

        if (d <= 0) return false;                        // d must be positive
        if (m < Month::jan || Month::dec < m) return false;
        if (y < 1970 || y > INT64_MAX / 366) return false;
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
        return Day((d.date() + 4) % 7);
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

    int days_in_year(const int& y)
    {
        if (leapyear(y))
            return 366;
        return 365;
    }
}