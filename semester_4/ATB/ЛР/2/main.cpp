#include <iostream>
#include <cmath>
#include <random>
#include <fstream>

class LabArray;
std::ostream& operator<< (std::ostream& out, const LabArray& obj);

inline double
harmonic (size_t N)
{
    double ret = 0;
    for (size_t i = 1; i <= N; i++)
        ret += 1 / static_cast<double>(i);
    return ret;
}

class LabArray
{
    public:
        const int __size__,
                  __max_rand_value__;
        size_t __counter__;
        int * __array__;

    
        LabArray (int size, int max_value)
            : __size__(size), __max_rand_value__(max_value), __counter__(0)
        { __array__ = new int[__size__]; }

        ~LabArray ()
        { delete[] __array__; }

        LabArray& fillArray (void)
        {
            std::mt19937 generator((std::random_device())());
            std::uniform_int_distribution<int> distribution(0, __max_rand_value__);

            for (int i = 0; i < __size__; i++)
                __array__[i] = distribution(generator);

            return *this;
        }

        int getMinimalValue (void)
        {
            int ret = __array__[0]; __counter__ = 0;

            for (int i = 1; i < __size__; i++)
                if (ret > __array__[i])
                {
                    ret = __array__[i];
                    __counter__++;
                }

            return ret;
        }

        inline size_t getCounter(void) { return __counter__; }
        inline int getSize (void) { return __size__; }
        inline int getMaxRandVal (void) { return __max_rand_value__; }

        friend std::ostream& operator<< (std::ostream&, const LabArray&);
};

std::ostream&
operator<< (std::ostream& out, const LabArray& obj)
{
    out << "arr[" << obj.__size__ << "] = {";
    for (int i = 0; i < std::min<int>(15, obj.__size__); i++)
        out << obj.__array__[i] << (i + 1 == obj.__size__ ? "" : " ");
    out << (obj.__size__ >= 15 ? "... }" : "}");

    return out;
}



int main (void)
{
    std::ofstream f{"coords.out", std::ios::out};
    double n;

    static LabArray A[3] = {
        {300,  100},
        {900,  100},
        {3000, 100}
    };

    std::cout << "Гармонические числа: "
              << harmonic(A[0].getSize()) << "/" << harmonic(A[1].getSize()) << "/" << harmonic(A[2].getSize())
              << " (для N = " << A[0].getSize() << "/" << A[1].getSize() << "/" << A[2].getSize() << ")" << std::endl;
    f         << "Гармонические числа: "
              << harmonic(A[0].getSize()) << "/" << harmonic(A[1].getSize()) << "/" << harmonic(A[2].getSize())
              << " (для N = " << A[0].getSize() << "/" << A[1].getSize() << "/" << A[2].getSize() << ")" << std::endl;

    for (int i = 0; i < 3; i++, n = 0.0)
    {
        for (int j = 0; j < 1000000; j++)
        {
            A[i].fillArray().getMinimalValue();
            n += A[i].getCounter();
        }

        std::cout << n / 1000000 << "\t" << A[i].getSize() << std::endl;
        f << n / 1000000 << "\t" << A[i].getSize() << std::endl;
    }

    return 0;
}
