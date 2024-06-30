#include "lab-8.hpp"

using namespace std;

int main (void)
{
    lab8::Graph g{"./table-1.dat"};
    cout << "Ответ: " << lab8::ask_God_for_answer(g, 0) << endl;

    return 0;
}
