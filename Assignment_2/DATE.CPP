#include "DATE.H"

/// overloading < operator
inline bool Date::operator <(const Date& other)const
{
    if(year < other.GetYear())
    {
        return true;
    }
    else if(year <= other.year && month < other.month)
    {
        return true;
    }
    else if(year <= other.year && month <= other.month && day < other.day)
    {
        return true;
    }
    return false;
}

/// overloading == operator
inline bool Date::operator ==(const Date& other)const
{
    if (year == other.year && month == other.month && day == other.day)
    {
        return true;
    }
    return false;
}

/// Initialization
Date::Date(const int& d, const int& m, const int& y):day(d), month(m), year(y) {}

/// Setter
void Date::SetDay(const int& d)
{
    if(d <=1 || d >=31)
        std::cout << "Invalid day entered.";
    else
        day = d;
}

/// Setter
void Date::SetMonth(const int& m)
{
    if(m <= 1 || m >= 12)
        std::cout << "Invalid month entered.";
    else
        month = m;
}

/// Setter
void Date::SetYear(const int& y)
{
    if(y <=1974 || y >=2022)
        std::cout << "Invalid year entered.";
    else
        year = y;
}

/// Getter
int Date::GetDay() const
{
    return day;
}

/// Getter
int Date::GetMonth() const
{
    return month;
}

/// Getter
int Date::GetYear() const
{
    return year;
}
