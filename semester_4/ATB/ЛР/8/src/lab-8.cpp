#include "lab-8.hpp"

using namespace std;
using namespace lab8;

Graph::Graph (int node_count)
    : table_ (nullptr), node_count_ (node_count)
{
    /* Создание пустой таблицы для графа. */
    table_ = new length*[node_count_];
    for (int row = 0; row < node_count_; row++)
        table_[row] = new length[node_count_];

    /* Ручное заполнение данных о графе. */
    for (int row = 0; row < node_count_; row++)
        for (int col = 0; col < node_count_; col++)
        {
            std::cout << "Введите длину пути из " << (row + 1)
                      << " в " << (col + 1) << ": ";
            std::cin >> table_[row][col];
        }
    
    return;
}
Graph::Graph (const std::string& filename)
    : table_ (nullptr), node_count_ (0)
{
    std::ifstream file{filename};

    /* Попытка прочитать данные из файла. */
    node_count_ = -1;
    file >> node_count_;
    if (node_count_ == -1)
    {
        std::cerr << "[ОШИБКА] Не удалось считать данные из файла. Файл повреждён." << std::endl;
        return;
    }

    /* Создание таблица с точками графа. */
    if (table_ == nullptr)
    {
        table_ = new length*[node_count_];
        for (int row = 0; row < node_count_; row++)
            table_[row] = new length[node_count_];
    }

    /* Заполнение таблицы из файла. */
    for (int row = 0; row < node_count_; row++)
        for (int col = 0; col < node_count_; col++)
            if (!file.eof())
            {
                file >> table_[row][col];
                if (table_[row][col] == 0)
                    table_[row][col] = NO_WAY;
            }
            else
                table_[row][col] = NO_WAY;
    
    return;
}
Graph::~Graph ()
{
    for (int row = 0; row < node_count_; row++)
        delete []table_[row];
    delete []table_;
}

Graph::operator string () const
{
    int col, row;
    stringstream out;
    
    out << "   ";
    for (col = 0; col < node_count_; col++)
        out << setw (3) << (col + 1) << " ";
    out << "\n";
    
    for (row = 0; row < node_count_; row++)
    {
        out << setw (2) << (row + 1) << " ";
        for (col = 0; col < node_count_; col++)
            out << setw (3) << (table_[row][col] != NO_WAY ? table_[row][col] : 0) << " ";
        out << "\n";
    }

    return out.str();
}

length lab8::ask_God_for_answer(const Graph& graph, int start_node)
{
    length out = 0;
    int node_from, node_to;
    bool is_node_marked[graph.node_count_];

    /* Присвоение начальных значений. */
    for (int i = 0; i < graph.node_count_; i++)
        is_node_marked[i] = false;
    is_node_marked[start_node] = true;

    for (int i = 0; i < graph.node_count_ - 1; i++)
    {
        node_from = node_to = -1;
        for (int j = 0; j < graph.node_count_; j++)
            if (is_node_marked[j])
                for (int k = 0; k < graph.node_count_; k++)
                    if ( !is_node_marked[k]
                        && graph.table_[j][k] != NO_WAY
                        && (node_to == -1 ||
                            graph.table_[node_from][node_to] > graph.table_[j][k]) )
                    {
                        node_from = j;
                        node_to = k;
                    }
        
        if (node_from == -1)
        {
            cout << "[ОШИБКА] Не удалось соединить все точки." << endl;
            return NO_WAY;
        }

        out += graph.table_[node_from][node_to];
        is_node_marked[node_to] = true;
    }

    return out;
}
