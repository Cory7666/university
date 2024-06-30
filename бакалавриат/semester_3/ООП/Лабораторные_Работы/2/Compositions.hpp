#include <iostream>



using std::string;
using std::cout;
using std::endl;



class Composition;
class Book;
class Art;



class Composition
{
    protected:
        const string author;           // Автор произведения.
        const string name;             // Название произведения.
        const long   num;              // Регистрационный номер.

    public:
        Composition (const string a, const string na, const long nu);    // Обычный конструктор класса.
        Composition (const Composition &c);            // Конструктор копирования.
        
        virtual void print () = 0;     // Печать данных.
        const string getAuthor ();     // Получить автора.
        const string getName   ();     // Получить название.
        const long   getRegNum ();     // Получить регистрационный номер.
};

class Book : public Composition
{
    protected:
        string genre;                  // Жанр произведения.
    public:
        Book (const string a, const string na, const long nu,    // Обычный конструктор класса.
              const string g);
        Book (const Book &c);          // Конструктор копирования.
        
        void print ();
        
        const string getGenre ();      // Получить жанр книги.
        Book & setGenre (const string g);    // Изменить жанр книги.
};

class Art : public Composition
{
    protected:
        string      style;             // Стиль.
        const long  size;              // Размер.
    public:
        Art (const string a, const string na, const long nu,   // Обычный конструктор класса.
             string st, const long si);
        Art (const Art &c);            // Конструктор копирования.
        
        void print ();
        
        const string getStyle ();      // Получить стиль картины.
        Art & setStyle        (const string st);    // Установить стиль картины.

        const long getSize    ();      // Получить размер картины.
};