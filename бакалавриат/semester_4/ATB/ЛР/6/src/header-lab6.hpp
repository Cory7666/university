#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <unistd.h>

#ifndef HEADER_HPP
#define HEADER_HPP

namespace lab6
{
    class Timer
    {
        public:
            void start ();
            void stop ();
            timespec getDiff () const;
            explicit operator std::string() const;
        private:
            timespec t_start_, t_stop_;
    };

    class ElementaryOperationCounter
    {
        public:
            ElementaryOperationCounter();
            ElementaryOperationCounter& resetCounter();
            ElementaryOperationCounter& increaseCounter();
            ElementaryOperationCounter& increaseCounter(unsigned long value);
            unsigned long getCounterValue ();
        private:
            unsigned long counter_;
    };

    class Fraction
    {
        public:
            Fraction ();
            Fraction (int numerator, int denominator);
            bool operator>  (const Fraction& val);
            bool operator>= (const Fraction& val);
            bool operator<  (const Fraction& val);
            bool operator<= (const Fraction& val);
            operator std::string() const;
        private:
            int numerator_,
                denominator_;
            bool is_negative_;
    };

    template <typename T>
    void
    print_array (const T* arr, int arr_size)
    {
        std::cout << "arr[" << arr_size << "] = { ";
        for (int i = 0; i < arr_size; i++)
            std::cout << " " << i << " => " << std::string (arr[i]);
        std::cout << " }" << std::endl;
    }

    template <typename T>
    ElementaryOperationCounter
    insert_sort_desc (T* arr, int arr_size)
    {
        ElementaryOperationCounter e;
        int i, j;
        T tmp;

        e.increaseCounter (2);
        for(i = 1; i <= arr_size; i++)
        {
            e.increaseCounter (3);

            tmp = arr[i];
            e.increaseCounter (2);

            e.increaseCounter (2 + 4);
            for(j = i - 1; j > -1 && arr[j] < tmp; j--)
            {
                e.increaseCounter (4 + 2);

                arr[j + 1] = arr[j];
                e.increaseCounter(3);
            }

            arr[j + 1] = tmp;
            e.increaseCounter (3);
        }

        return e;
    }

    template <typename T>
    ElementaryOperationCounter
    bubble_sorting_desc (T* arr, int arr_size)
    {
        ElementaryOperationCounter e;

        for (int end = arr_size - 1; end > 0; end--)
        {
            e.increaseCounter (5);

            e.increaseCounter (2);
            for (int j = 0; j < end; j++)
            {
                e.increaseCounter (1 + 2);

                e.increaseCounter (4);
                if (arr[j] < arr[j + 1])
                {
                    std::swap (arr[j], arr[j + 1]);
                    e.increaseCounter (3);
                }
            }
        }

        return e;
    }

    template <typename T>
    ElementaryOperationCounter
    shell_sort_desc (T* arr, int arr_size)
    {
        ElementaryOperationCounter e;

        e.increaseCounter (2 + 1);
        for (int step = arr_size / 2; step > 0; step /= 2)
        {
            e.increaseCounter (1 + 2);

            e.increaseCounter (1 + 2);
            for (int i = 0; i < (arr_size - step); i++)
            {
                e.increaseCounter (2 + 2);

                e.increaseCounter (1 + 6);
                for (int j = i; j >= 0 && arr[j] < arr[j + step]; j--)
                {
                    e.increaseCounter (6 + 2);

                    e.increaseCounter (3);
                    std::swap (arr[j], arr[j + step]);
                }
            }
        }

        return e;
    }
}

#endif //! HEADER_HPP
