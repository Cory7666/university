#include "header-lab6.hpp"

using namespace std;
using namespace lab6;

Fraction::Fraction ()
    : numerator_ (rand() % 61), denominator_ (rand() % 60 + 1), is_negative_ (false)
{ }
Fraction::Fraction (int numerator, int denominator)
    : numerator_ (abs(numerator)), denominator_ (abs(denominator))
{
    if ( (numerator < 0 && denominator > 0)
      || (numerator > 0 && denominator < 0) )
        is_negative_ = true;
    else
        is_negative_ = false;
}
bool Fraction::operator> (const Fraction& val)
{
    int num1 = val.denominator_ * this->numerator_ * (this->is_negative_ ^ val.is_negative_ ? -1 : 1),
        num2 = val.numerator_ * this->denominator_ * (this->is_negative_ ^ val.is_negative_ ? -1 : 1);
    return num1 > num2;
}
bool Fraction::operator>= (const Fraction& val)
{
    int num1 = val.denominator_ * this->numerator_ * (this->is_negative_ ^ val.is_negative_ ? -1 : 1),
        num2 = val.numerator_ * this->denominator_ * (this->is_negative_ ^ val.is_negative_ ? -1 : 1);
    return num1 >= num2;
}
bool Fraction::operator< (const Fraction& val)
{
    int num1 = val.denominator_ * this->numerator_ * (this->is_negative_ ^ val.is_negative_ ? -1 : 1),
        num2 = val.numerator_ * this->denominator_ * (this->is_negative_ ^ val.is_negative_ ? -1 : 1);
    return num1 < num2;
}
bool Fraction::operator<= (const Fraction& val)
{
    int num1 = val.denominator_ * this->numerator_ * (this->is_negative_ ^ val.is_negative_ ? -1 : 1),
        num2 = val.numerator_ * this->denominator_ * (this->is_negative_ ^ val.is_negative_ ? -1 : 1);
    return num1 <= num2;
}
Fraction::operator std::string() const
{
    std::string out{};
    out = "(" + to_string(numerator_) + "/" + to_string(denominator_) + ")";
    return out;
}

void Timer::start()
{
    clock_gettime (CLOCK_REALTIME, &t_start_);
}
void Timer::stop()
{
    clock_gettime (CLOCK_REALTIME, &t_stop_);
}
timespec Timer::getDiff() const
{
    timespec tmp;
    tmp.tv_nsec = t_stop_.tv_nsec - t_start_.tv_nsec;
    tmp.tv_sec = t_stop_.tv_sec - t_start_.tv_sec;
    if (tmp.tv_nsec < 0)
    {
        tmp.tv_nsec += 1000000000;
        tmp.tv_sec--;
    }

    return tmp;
}
Timer::operator std::string() const
{
    std::stringstream ss;
    timespec t = getDiff();
    ss << t.tv_sec << "." << t.tv_nsec;
    return ss.str();
}

ElementaryOperationCounter::ElementaryOperationCounter ()
    : counter_ (0)
{ }
ElementaryOperationCounter& ElementaryOperationCounter::resetCounter()
{ counter_ = 0; return *this; }
ElementaryOperationCounter& ElementaryOperationCounter::increaseCounter()
{ counter_++; return *this; }
ElementaryOperationCounter& ElementaryOperationCounter::increaseCounter(unsigned long value)
{ counter_ += value; return *this; }
unsigned long ElementaryOperationCounter::getCounterValue()
{ return counter_; }
