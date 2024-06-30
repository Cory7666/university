#include "Class.hpp"

std::istream & operator>> (std::istream & stream, DMatr & obj)
{
    for (size_t i = 0; i < obj._lines; i++)
        for (size_t j = 0; j < obj._cols; j++)
            stream >> obj._m[i][j];

    return stream;
}

DMatr::DMatr (size_t lines, size_t cols, elem_t * array, size_t array_size)
    : _lines (lines), _cols (cols)
{
    _m = new elem_t*[_lines];
    for (size_t i = 0; i < _lines; i++)
    {
        _m[i] = new elem_t[_cols];
        memset (_m[i], 0 , _cols * sizeof(elem_t));
    }
    
    for (size_t i = 0; i < _lines; i++)
        for (size_t j = 0; j < _cols; j++)
            _m[i][j] = (i * _cols + j < array_size) ? array[i * _cols + j] : 0;
}

DMatr::DMatr (const DMatr & a)
    : _lines (a._lines), _cols (a._cols)
{
    _m = new elem_t*[_lines];

    for (size_t i = 0; i < _lines; i++)
    {
        _m[i] = new elem_t[_cols];
        memcpy (_m[i], a._m[i], sizeof(elem_t) * _cols);
    }
}

DMatr::~DMatr ()
{
    for (size_t i = 0; i < _cols; i++)
        delete [] _m[i];
    delete [] _m;
}

bool DMatr::operator! ()
{
    for (size_t i = 0; i < _lines; i++)
        for (size_t j = 0; j < _cols; j++)
            if (!_m[i][j])
                return true;
    return false;
}

elem_t operator+  (const DMatr & obj)
{
    elem_t sum = 0.0;
    for (size_t i = 0; i < obj._lines; i++)
        for (size_t j = 0; j < obj._cols; j++)
            sum += obj._m[i][j];
    return sum;
}

elem_t DMatr::operator* (const DMatr & obj)
{
    if ( (this->_cols != obj._cols) || (this->_lines != obj._lines) ) return -6.666;

    elem_t sum = 0.0;
    
    for (size_t i = 0; i < this->_lines; i++)
        for (size_t j = 0; j < this->_cols; j++)
            sum += this->_m[i][j] + obj._m[i][j];
    
    return sum;
}

bool operator== (const DMatr & obj_1, const DMatr & obj_2)
{
    if ( (obj_1._cols != obj_2._cols) || (obj_1._lines != obj_2._lines) ) return false;

    for (size_t i = 0; i < obj_1._lines; i++)
        for (size_t j = 0; j < obj_1._cols; j++)
            if (obj_1._m[i][j] != obj_2._m[i][j])
                return false;
    
    return true;
}