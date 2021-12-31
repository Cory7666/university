#include "header.hpp"

int main (void)
{
    double
        first = 0.0,
        second = 0.0,
        result = 0.0;
    char
        op = 0;
    char
        fileName[] = "result";

    try {
        /*
        cout << "Введите первое число, оператор, второе число: ";
        cin >> first >> op >> second;
        first_task (op, first, second, result);
        cout << "Ответ: " << setfill ('^') << setw (15) << setprecision (5) << result << endl << " *  Результат выведен в файл " << fileName << "." << endl;

        ofstream file (fileName, ios::app);
        file << "Результат: " << setfill ('^') << setw (15) << setprecision (5) << result << endl;
        */

        
        cout << "Введите число: ";
        cin >> first;
        second_task (first, result);
        cout << "Ответ: " << result << endl;
        
    }
    catch (ZeroDivisionException & e)
    {
        std::cerr << "ОШИБКА: Деление на 0." << std::endl
                 << " *  Получено в блоке: «" << e.getMessage() << "»." << std::endl;
    }
    catch (UnknownOperatorException & e)
    {
        std::cerr << "ОШИБКА: Неверный оператор." << std::endl;
    }
    catch (...)
    {
        std::cerr << "Поймано необрабатываемое исключение." << std::endl;
    }

    return 0;
}

void first_task (char op, double f, double s, double & result)
{
    switch (op)
    {
        case '+':
            result = f + s;
            break;
        case '-':
            result = f - s;
            break;
        case '*':
            result = f * s;
            break;
        case '/':
            if (s)
                result = f / s;
            else
                throw ZeroDivisionException ("Калькулятор & Вычисление Результата");
            break;
        default:
            throw UnknownOperatorException ("Калькулятор & Вычисление результата");
            break;
    }

    return;
}

void second_task (double x, double & result)
{
    if (!x) throw ZeroDivisionException("Выражение & Значение Аргумента Косинуса");

    double tmp = cos (1 / x);
    if (tmp <= 0) throw InvalidLogArgumentException ("Выражение & Значение Логарифма");

    result = log (tmp);

    return;
}
