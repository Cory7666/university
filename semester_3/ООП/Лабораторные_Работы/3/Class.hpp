#include <iostream>



using std::endl;
using std::string;
using std::cout;

class Aircraft;
class Transport;
class Shuttle;



class Aircraft               // Класс "Летательный аппарат".
{
    private:
        const string type;   // Тип Летательного аппарата.
        double fuel_cons;    // Расход топлива. л/ч.
        double fuel_level;   // Вместимость топливного бака. л.
        long speed;          // Скорость Летательного аппарата. км/ч.
    public:
        Aircraft ();                             // Обычный конструктор 1.
        Aircraft (const long s, const double fl, const double fc);                    // Обычный конструктор 2.
        Aircraft (const string t, const long s, const double fl, const double fc);    // Обычный конструктор 3.

              string getType  ();                // Получить Тип.
        const long   getSpeed ();                // Получить Скорость.
        const double getFLevel();                // Получить уровень топлива.
        const double getFConsumption ();         // Получить Расход топлива.

        Aircraft & setType  (string t);          // Установить значение Тип.
        Aircraft & setSpeed (long s);            // Установить значение Скорость.
        Aircraft & setFLevel(double fl);         // Установить уровень топлива.
        Aircraft & setFConsumption (double fc);  // Установить Расход топлива.

        const double getEstimatedRange ();       // Получить расчётную дальность хода Летательного аппарата.
};



class Transport              // Класс "Транспорт".
{
    private:
        const long tonnage;        // Тоннаж.
    public:
        Transport ();                            // Обычный конструктор 1.
        Transport (const long t);                // Обычный конструктор 2.

        string     getTonnage  ();               // Получить Тоннаж.

        Aircraft & setTonnage  (string t);       // Установить значение Тоннаж.
};



class Shuttle : public Aircraft, public Transport    // Класс "Шаттл".
{

};