#include <iostream>

#include "Compositions.hpp"

int main (int argc, char **argv)
{
    Composition *myCollection[6] = {
        new Art("Ван Гог", "Звёздная Ночь", 5555555, "Постимпрессионизм", 6300),
        new Art("Шишкин И.И.", "Утро в сосновом бору", 666666, "Релизм", 29607),
        new Book("Эрин Хантер", "Коты-Воители", 78198, "Фэнтези"),
        new Book("Зузак М.", "Я - посланник", 484575, "Реализм"),
        nullptr,
        nullptr
    };

    cout << "Вывод содержимого \"Моя коллекция произведений\":" << endl;
    for (int i = 0; myCollection[i]; myCollection[i]->print(), i++);

    cout << endl << "Добавить новую книгу в колекцию." << endl
         << "Добавление жанра к добавленной книге." << endl
         << "Повторный вывод информации о данной книге: " << endl << endl;

    Book *pBook = (Book *) (myCollection[2]);
    const string genre_old = pBook->getGenre();

    pBook->setGenre(genre_old + "; Приключения").print();

    return 0;
}