#include "Compositions.hpp"



Composition::Composition (const string a, const string na, const long nu) : 
    author(a), name (na), num (nu) {}
Composition::Composition (const Composition & c) : 
    author (c.author), name (c.name), num (c.num) {}

const string Composition::getAuthor () { return this->author; }
const string Composition::getName   () { return name;   }
const long   Composition::getRegNum () { return num;    }



Book::Book (const string a, const string na, const long nu, const string g) : 
    Composition (a, na, nu), genre (g) {}
Book::Book (const Book & c) :
    Composition (c.author, c.name, c.num), genre (c.genre) {}

void Book::print ()
{
    cout << author << " \"" << name << "\"." << endl
         << "Регистрационный номер: " << num << endl
         << "Жанры: " << genre << endl;
}

const string Book::getGenre ()               { return genre; }
Book &       Book::setGenre (const string g) { genre = g; return *this; }



Art::Art (const string a, const string na, const long nu,
          string st, const long si) :
    Composition (a, na, nu), style (st), size (si) {}
Art::Art (const Art & c) :
    Composition (c.author, c.name, c.num), style (c.style), size (c.size) {}

void Art::print ()
{
    cout << author << " \"" << name << "\"." << endl
         << "Регистрационный номер: " << num << endl
         << "Стили: " << style << endl;
}

const string Art::getStyle ()                { return style; }
Art &        Art::setStyle (const string st) { style = st; return *this; }

const long   Art::getSize  ()                { return size; }