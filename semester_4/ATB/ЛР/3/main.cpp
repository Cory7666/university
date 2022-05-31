#include <cmath>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <random>

typedef uint64_t flag_t;

size_t op_couter = 0;

/* Выполнить задание. */
template <typename T>
flag_t taskSum (uint8_t array_size, T array[], T sum);
/* Заполнить массив случайными значениями. */
template <typename T>
void fill_random (uint8_t array_size, T array[], T min_value, T max_value);
/* Заполнить массив вручную. */
template <typename T>
void fill_manually (uint8_t& array_size, T array[]);
/* Печать ответа на задание. */
template <typename T>
void printAnswer (uint8_t array_size, T array[], flag_t flags);

/* Сбросить счётчик элементарных операций. */
inline void reset_oc (void) { op_couter = 0; }
/* Увеличить счётчик элементарных операций. */
inline size_t increase_oc (size_t n) { return op_couter += n; }



int main (void)
{
    const uint8_t
        size = 12;
    static int
        V = 20,
        min_rand_value = 0,
        max_rand_value = 20,
        array[size],
        sum = 0.0;

    for (int i = 0; i < 20; i += 1)
    {
        fill_random (size, array, min_rand_value, max_rand_value);
        printAnswer(size, array, taskSum(size, array, V));

        sum += op_couter;
    }

    std::cout << "Счётчик элементарных операций: " << op_couter << std::endl;

    std::cout << "Количество операций в теории: " << (1 + (std::pow(2, size) - 1) * ( 3 + 1 + 1 + size * ( 3 + 2 + 3 * 0.5 ) + 1 )) << std::endl;

    std::cout << "Среднее количество операций: " << (sum / 20.0) << std::endl;
}

template <typename T>
void fill_random (uint8_t array_size, T array[], T min_value, T max_value)
{
    std::mt19937 engine{(std::random_device())()};
    std::uniform_int_distribution<T> dist{min_value, max_value};

    for (uint8_t i = 0; i < array_size; i++)
        array[i] = dist(engine);
}

template <typename T>
void fill_manually (uint8_t array_size, T array[])
{
    for (uint8_t i = 0; i < array_size; i++)
    {
        std::cout << "Введите " << i + 1 << " элемент:\t";
        std::cin >> array[i];
    }
}

template <typename T>
flag_t taskSum (uint8_t array_size, T array[], T V)
{
    reset_oc();

    //memset (array, 0, array_size * sizeof (T));
    //array[0] = V;

    static flag_t
        flags,
        Nmax = std::pow(2, array_size) - 1;
    T sum = 0;
    
    increase_oc (1);
    for (flags = 0x1; flags <= Nmax; flags += 0x1)  // 1 + Nmax * ( 3 +
    {
        increase_oc (1);

        sum = 0;                                    // 1
        increase_oc (1);

        increase_oc (1);
        for (uint8_t i = 0; i < array_size; i++)    // 1 + array_size * ( 3 + 
        {
            increase_oc (1);

            increase_oc (2);
            if ((flags >> i) & 0x1)                 // 2
            {
                increase_oc (3);
                sum = sum + array[i];               // 3 Вероятность: 0.5
            }

            increase_oc (2);
        }                                           // )

        increase_oc (1);
        if (sum == V)                               // 1
            return flags;
        
        increase_oc (2);
    }                                               // )

    return 0;
}

template <typename T>
void
printAnswer (uint8_t array_size, T array[], flag_t flags)
{
    std::cout << "Ответ:" << std::endl;
    if (!flags)
    {
        std::cout << "\tПодходящие элементы массива не найдены." << std::endl;
        return;
    }

    for (auto i = 0; i < array_size; i++)
        std::cout << " " << (((flags >> i) & 0x1) ? "+" : " ") << "  ";
    
    std::cout << std::endl;

    for (auto i = 0; i < array_size; i++)
        std::cout << std::setw(3) << std::setfill('_') << array[i] << " ";
    
    std::cout << std::endl;
}
