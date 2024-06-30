#include <iostream>
#include <set>
#include <iterator>
#include <algorithm>


enum MENU_ITEMS {
    ITEM_ADD_ELEMENT = 1,
    ITEM_DELETE_ELEMENT,
    ITEM_SHOW_ELEMENTS,
    ITEM_SEARCH_TITLE,
    ITEM_SEARCH_BY_AUTHOR,
    ITEM_EXIT
};

/* Абстрактный класс исключений */
class AllExceptions
{
    private:
        const std::string _block;
        const std::string _message;
    public:
        AllExceptions (std::string block, std::string message)
            : _block (block), _message (message)
        {}

        std::string getBlock   () const { return _block;   }
        std::string getMessage () const { return _message; }
};
/* Исключение отсутствия элементов в контейнере */
class NoElementException : public AllExceptions
    { public: NoElementException (std::string block, std::string message) : AllExceptions (block, message) {} };
/* Исключение: элемент не найден */
class NotFoundException : public AllExceptions
    { public: NotFoundException  (std::string block, std::string message) : AllExceptions (block, message) {} };
/* Исключение: неверный код пункта меню */
class UnknownKeyException : public AllExceptions 
    { public: UnknownKeyException (std::string block, std::string message) : AllExceptions (block, message) {} };


/* Структура с доп информацией о книге */
struct data_t
{
    std::string title;
    int div_num, stand_num, shelf_num;

    friend bool operator< (const data_t & d1, const data_t & d2);
};

typedef std::pair<std::string, data_t> pair_t;   // Тип данных пары
typedef std::multiset<pair_t> db_t;              // Тип данных контейнера

/* Сравнение структур с доп информацией */
bool
operator< (const data_t & d1, const data_t & d2)
{ return d1.title < d2.title; }



/* Добавить элемент в контейнер */
void add_element (db_t & db)
{
    std::string FIO;
    data_t d;

    std::cout << "[MESSAGE] Добавление нового элемента." << std::endl;
    std::cout << "Введите ФИО автора:     "; std::cin >> FIO;
    std::cout << "Введите название книги: "; std::cin >> d.title;
    std::cout << "Введите № отдела:       "; std::cin >> d.div_num;
    std::cout << "Введите № стенда:       "; std::cin >> d.stand_num;
    std::cout << "Введите № полки:        "; std::cin >> d.shelf_num;
    // Добавление 
    db.insert (std::make_pair(FIO, d));
    std::cout << "[MESSAGE] Добавлено." << std::endl << std::endl;

    return;
}

/* Удалить элемент в контейнере */
void delete_element (db_t & db)
{
    if (1 > db.size ())
        throw NoElementException ("Удаление_Элемента", "Данные отсутствуют.");

    std::string FIO, title;

    std::cout << "Введите ФИО автора:     "; std::cin >> FIO;
    std::cout << "Введите название книги: "; std::cin >> title;

    for (db_t::iterator iter = db.begin (); iter != db.end (); iter++)
    {
        if (iter->first == FIO && iter->second.title == title)
        {
            db.erase (iter);
            return;
        }
    }

    throw NotFoundException ("Удаление_Элемента", "Книги <" + FIO + "> - <" + title + "> не существует.");

    return;
}

/* Отобразхить книги, имеющие данное название */
void search_element (const db_t & db)
{
    if (1 > db.size ())
        throw NoElementException ("Поиск_Книги", "Нельзя осуществить поиск среди несуществующих данных.");

    std::string title;
    bool f = false;

    std::cout << "Введите название книги: "; std::cin >> title;

    for (auto elem : db)
    {
        if (title == elem.second.title)
        {
            std::cout << "Найден элемент:" << std::endl;
            std::cout << "  ▶ ФИО: " << elem.first << std::endl
                      << "  ▶ № отдела/стенда/полки: " << elem.second.div_num << "/"
                                                       << elem.second.stand_num << "/"
                                                       << elem.second.shelf_num << std::endl << std::endl;
            f = true;
        }
    }

    if (!f)
        throw NotFoundException ("Поиск_Книги", "Книги с названием <" + title + "> не существует.");
}

/* Отобразхить книги, имеющие данного автора */
void search_elements_by_author (const db_t & db)
{
    if (1 > db.size ())
        throw NoElementException ("Поиск_Книг_По_Автору", "Нельзя осуществить поиск среди несуществующих данных.");

    std::string writter;
    bool f = false;

    std::cout << "Введите ФИО автора: "; std::cin >> writter;

    for (auto elem : db)
    {
        if (writter == elem.first)
        {
            std::cout << "Найден элемент:" << std::endl;
            std::cout << "  ▶ " << elem.first << " \"" << elem.second.title << "\"" << std::endl
                      << "  ▶ № отдела/стенда/полки: " << elem.second.div_num << "/"
                                                       << elem.second.stand_num << "/"
                                                       << elem.second.shelf_num << std::endl << std::endl;
            f = true;
        }
    }

    if (!f)
        throw NotFoundException ("Поиск_Книг_По_Автору", "Не удалось найти ни одну книгу с автором <" + writter + ">.");
}

/* Печать элементов на экран */
void print_elements (const db_t & db)
{
    if (1 > db.size ())
        throw NoElementException ("Печать_Элементов", "Нельзя напечатать несуществующие данные.");

    std::cout << "Вывод элементов." << std::endl;

    auto iter = db.begin();
    auto i = 1U;
    
    for (; iter != db.end(); iter++, i++)
    {
        std::cout << "Книга [" << i << "]" << std::endl;
        std::cout << "  ▶ Автор: " << iter->first << std::endl
                  << "  ▶ Название книги: " << iter->second.title << std::endl
                  << "  ▶ № отдела: " << iter->second.div_num << std::endl
                  << "  ▶ № стенда: " << iter->second.stand_num << std::endl
                  << "  ▶ № полки: " << iter->second.shelf_num << std::endl << std::endl;
    }

    std::cout << "Вывод завершён." << std::endl;
}


/* Печать меню */
void print_menu (void)
{
    std::cout << "Меню программы" << std::endl
              << "  ▶ " << ITEM_ADD_ELEMENT      << " - Добавить элемент в контейнер."      << std::endl
              << "  ▶ " << ITEM_DELETE_ELEMENT   << " - Удалить элемент."                   << std::endl
              << "  ▶ " << ITEM_SHOW_ELEMENTS    << " - Печать всех книг."                  << std::endl
              << "  ▶ " << ITEM_SEARCH_TITLE     << " - Найти книгу."                       << std::endl
              << "  ▶ " << ITEM_SEARCH_BY_AUTHOR << " - Найти все книги указанного автора." << std::endl
              << "  ▶ " << ITEM_EXIT             << " - Выйти из программы."                << std::endl;
}



int main (int argc, char **argv)
{
    db_t db;
    int menuItemNum = (-1);

    {
        int elem_count = 0;
        std::cout << "Введите количество элементов для добавления: "; std::cin >> elem_count;
        while (elem_count > 0)
        {
            add_element (db);
            elem_count--;
        }
    }

    while (menuItemNum != ITEM_EXIT)
    {
        print_menu ();

        std::cout << "$ "; std::cin >> menuItemNum;

        try
        {
            switch (menuItemNum)
            {
                case ITEM_ADD_ELEMENT:
                    add_element (db);
                    break;
                case ITEM_DELETE_ELEMENT:
                    delete_element (db);
                    break;
                case ITEM_SEARCH_BY_AUTHOR:
                    search_elements_by_author (db);
                    break;
                case ITEM_SEARCH_TITLE:
                    search_element (db);
                    break;
                case ITEM_SHOW_ELEMENTS:
                    print_elements (db);
                    break;
                case ITEM_EXIT:
                    break;
                default:
                    throw UnknownKeyException ("Главное_Меню", "Неизвестный код пункта меню.");
                    break;
            }
        }
        catch (AllExceptions & e)
        {
            std::cout << "ВНИМАНИЕ, ИСКЛЮЧЕНИЕ" << std::endl
                      << "  ▶ Блок: " << e.getBlock () << std::endl
                      << "  ▶ Причина исключения: " << e.getMessage () << std::endl
                      << std::endl;
        }
        catch (...)
        {
            std::cout << "ВНИМАНИЕ, ПОЛУЧЕНО НЕИЗВЕСТНОЕ ИСКЛЮЧЕНИЕ." << std::endl
                      << std::endl;
        }
    }

    return 0;
}
