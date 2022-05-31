#include "header-lab6.hpp"

using namespace std;
using namespace lab6;

int main (void)
{
    /*
        FOR TESTS

    const int arr_len = 5;
    lab6::Fraction arr[arr_len] = {{1, 2}, {4, 2}, {1, 3}, {68, 85}, {52, 1000}};

    lab6::print_array (arr, arr_len);
    lab6::bubble_sorting_desc (arr, arr_len);
    lab6::print_array (arr, arr_len);
    */

   int rand_seed = 100;
    std::ofstream fileBubble{"bubble-graphic"},
                  fileInsert{"insert-graphic"},
                  fileShell {"shell-graphic"};
    Timer t;

    srand(rand_seed);
    for (long i = 3; i < 5; i++)
    {
        long arr_size = i * i * i;
        ElementaryOperationCounter e;
        Fraction arr[arr_size];

        t.start ();
        e = bubble_sorting_desc (arr, arr_size);
        t.stop ();
        cout << "Bubble sort [" << arr_size << "] = " << std::string(t) << "s. Counter: " << e.getCounterValue() << std::endl;

        fileBubble << arr_size << " " << e.getCounterValue() << "\n";
    }

    cout << setw(10) << setfill('=') << " " << endl;

    srand(rand_seed);
    for (long i = 3; i < 5; i++)
    {
        long arr_size = i * i * i;
        ElementaryOperationCounter e;
        Fraction arr[arr_size];

        t.start ();
        e = insert_sort_desc (arr, arr_size);
        t.stop ();
        cout << "Insert sort [" << arr_size << "] = " << std::string(t) << "s. Counter: " << e.getCounterValue() << std::endl;

        fileInsert << arr_size << " " << e.getCounterValue() << "\n";
    }

    cout << setw(10) << setfill('=') << " " << endl;

    srand(rand_seed);
    for (long i = 3; i < 5; i++)
    {
        long arr_size = i * i * i;
        ElementaryOperationCounter e;
        Fraction arr[arr_size];

        t.start ();
        e = shell_sort_desc (arr, arr_size);
        t.stop ();
        cout << "Shell sort [" << arr_size << "] = " << std::string(t) << "s. Counter: " << e.getCounterValue() << std::endl;

        fileShell << arr_size << " " << e.getCounterValue() << "\n";
    }

    return 0;
}
