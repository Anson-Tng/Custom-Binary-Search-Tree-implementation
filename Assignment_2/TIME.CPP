#include "TIME.H"


/// overloading < operator
inline bool Time::operator <(const Time& other)const
{
    if(hour < other.getHours())
    {
        return true;
    }
    else if(hour <= other.getHours() && minute < other.getMinutes())
    {
        return true;
    }
    else
    {
        return false;
    }
}

/// overloading == operator
inline bool Time::operator ==(const Time& other)const
{
    if (hour == other.getMinutes() && minute == other.getMinutes())
    {
        return true;
    }
    return false;
}

/// Constructor with parameters
Time::Time(const int& hours, const int& minutes):hour(hours), minute(minutes) {}

/// Setter
void Time::setHours(const int& hrs)
{
    if(hrs >= 24 || hrs <= 1)
    {
        std::cout << "invalid hours";
    }
    else
    {
        hour = hrs;
    }
}

/// Setter
void Time::setMinutes(const int& mins)
{
    if(mins >= 59 || mins <= 0)
    {
        std::cout << "invalid minutes";
    }
    else
    {
        minute = mins;
    }
}

/// Getter
int Time::getHours() const
{
    return hour;
}

/// Getter
int Time::getMinutes() const
{
    return minute;
}


