#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>



using namespace std;



class ExceptionAbstractClass
{
    protected:
        const std::string _message;
    public:
        ExceptionAbstractClass (const std::string message) : _message(message) {}
        const std::string getMessage () const { return _message; }
};



class ZeroDivisionException : public ExceptionAbstractClass       { public: ZeroDivisionException (std::string message) : ExceptionAbstractClass (message)       {} };
class UnknownOperatorException : public ExceptionAbstractClass    { public: UnknownOperatorException (std::string message) : ExceptionAbstractClass (message)    {} };
class InvalidLogArgumentException : public ExceptionAbstractClass { public: InvalidLogArgumentException (std::string message) : ExceptionAbstractClass (message) {} };

void first_task (char, double, double, double &);
void second_task (double, double &);
