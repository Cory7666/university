#include <iostream>
#include <stdlib.h>

#define ARR_LEN(arr) (sizeof(arr) / sizeof((arr)[0]))

using std::cout;
using std::cin;
using std::endl;
using std::string;

class Integer;
class IntVector;

size_t f(const Integer & obj_1, const IntVector & obj_2);

class Integer
{
    private:
        long long int _integer;
    
    public:
        Integer ()                            : Integer (0)             { }
        Integer (const long long int integer) : _integer (integer)      { }
        Integer (const Integer & obj)         : _integer (obj._integer) { }

        long long int getValue () const                  { return _integer; }
        Integer & setValue (const long long int integer) { _integer = integer; return *this; }

        friend size_t f(const Integer & obj_1, const IntVector & obj_2);
};

class IntVector
{
    private:
        long long int * _integers;
        size_t          _vector_size;
    
    public:
        IntVector () : IntVector(nullptr, 0) { }
        IntVector (const long long int *data, const size_t data_size);
        IntVector (const IntVector & obj) : IntVector (obj._integers, obj._vector_size) { }
        ~IntVector ();

        long long int getVectorSize () const { return _vector_size; }
        const long long int * getVectorData () const { return const_cast<const long long int *>(_integers); }
        IntVector & push (long long int integer);
        IntVector & pop ();

        explicit operator std::string () const;

        friend size_t f(const Integer & obj_1, const IntVector & obj_2);
};