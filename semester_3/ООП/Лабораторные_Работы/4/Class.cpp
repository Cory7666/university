#include "Class.hpp"

IntVector::IntVector (const long long int *data, const size_t data_size)
{
    _integers = (long long int *) calloc(sizeof(long long int), data_size);
    _vector_size = data_size;
    for (size_t i = 0; i < data_size; i++)
        _integers[i] = data[i];
}

IntVector::~IntVector ()
{
    free(_integers);
}

IntVector & IntVector::push (long long int integer)
{
    _integers = (long long int *) realloc(_integers, ++_vector_size * sizeof(long long int));
    _integers[_vector_size - 1] = integer;
    return *this;
}

IntVector & IntVector::pop ()
{
    if (_vector_size)
        _integers = (long long int *) realloc(_integers, --_vector_size * sizeof(long long int));
    return *this;
}

IntVector::operator std::string () const
{
    string s = "vector = [";
    for (size_t i = 0; i < _vector_size; i++)
        s += std::to_string(_integers[i]) + ((i + 1 != _vector_size) ? (", ") : (""));
    s += "]";
    return s;
}

size_t f(const Integer & obj_1, const IntVector & obj_2)
{
    size_t answer = 0;
    for (size_t i = 0; i < obj_2._vector_size; i++)
        if (obj_2._integers[i] > obj_1._integer)
            answer++;
    return answer;
}