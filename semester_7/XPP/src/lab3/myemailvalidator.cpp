#include "myemailvalidator.h"

MyEmailValidator::MyEmailValidator() : _emailRegex(_emailPattern)
{}

QValidator::State MyEmailValidator::validate(QString &data, int &pos) const
{
    return this->_emailRegex.match(data).hasMatch() ? QValidator::Acceptable : QValidator::Intermediate;
}
