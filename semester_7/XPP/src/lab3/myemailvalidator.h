#ifndef MYEMAILVALIDATOR_H
#define MYEMAILVALIDATOR_H

#include <QString>
#include <QValidator>
#include <QRegularExpression>

class MyEmailValidator : public QRegularExpressionValidator
{
    Q_OBJECT
public:
    MyEmailValidator();
protected:
    const char* _emailPattern = "\\w+@\\w+\\.\\w\\w+";
    QRegularExpression _emailRegex;
public:
    State validate(QString &data, int &pos) const override;
};

#endif // MYEMAILVALIDATOR_H
