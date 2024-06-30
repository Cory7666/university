#include "header.hpp"

using namespace l;

Graph::Graph ()
    : table_ (nullptr), node_names_ (nullptr), node_count_ (0)
{ }
Graph::Graph (int node_count)
    : table_ (nullptr), node_names_ (nullptr), node_count_ (node_count)
{
    /* Создание массива с новыми именами для узлов */
    node_names_ = new int[node_count_];
    
    /* Создание пустой таблицы для графа */
    table_ = new length*[node_count_];
    for (int row = 0; row < node_count_; row++)
        table_[row] = new length[node_count_];

    fill ();
}
Graph::Graph (const std::string& filename)
    : Graph ()
{
    fill (filename);
}
Graph::~Graph ()
{
    delete []node_names_;
    for (int row = 0; row < node_count_; row++)
        delete []table_[row];
    delete []table_;
}



Graph& Graph::fill ()
{
    if (table_ == nullptr || node_count_ < 1)
    {
        std::cerr << "[ОШИБКА] Неверное количество узлов в графе." << std::endl;
        return *this;
    }

    for (int row = 0; row < node_count_; row++)
        for (int col = 0; col < node_count_; col++)
        {
            std::cout << "Введите длину пути из " << (row + 1)
                      << " в " << (col + 1) << ": ";
            std::cin >> table_[row][col];
        }
    
    sortTopologically();

    return *this;
}
Graph& Graph::fill (const std::string& filename)
{
    std::ifstream file{filename};

    node_count_ = -1;
    file >> node_count_;
    if (node_count_ == -1)
    {
        std::cerr << "[ОШИБКА] Не удалось считать данные из файла. Файл повреждён." << std::endl;
        return *this;
    }

    if (table_ == nullptr)
    {
        table_ = new length*[node_count_];
        for (int row = 0; row < node_count_; row++)
            table_[row] = new length[node_count_];
    }
    if (node_names_ == nullptr)
        node_names_ = new int[node_count_];

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
    
    file.close();

    sortTopologically();

    return *this;
}



Graph::operator std::string () const
{
    int col, row;
    std::stringstream out;
    
    out << "   ";
    for (col = 0; col < node_count_; col++)
        out << std::setw (3) << (col + 1) << " ";
    out << "\n";
    
    for (row = 0; row < node_count_; row++)
    {
        out << std::setw (2) << (row + 1) << " ";
        for (col = 0; col < node_count_; col++)
            out << std::setw (3) << (table_[row][col] != NO_WAY ? table_[row][col] : 0) << " ";
        out << "\n";
    }

    return out.str();
}

length Graph::operator() (int from, int to) const
{
    if (node_names_[from] > node_names_[to])
        return NO_WAY;
    if (from == to)
        return 0;
    if (!b_)
    {
        std::cout << "Ошибка: действие к данному графу неприменимо." << std::endl;
        return NO_WAY;
    }
    
    length ways[node_count_];
    for (int i = 0; i < node_count_; i++)
        ways[i] = NO_WAY;
    ways[from] = 0;

    for (int node = node_names_[from]; node < node_names_[to]; node++)
        for (int next_node = 0; next_node < node_count_; next_node++)
            if (table_[getOldNodeNameByNew(node)][next_node] != NO_WAY)
                ways[next_node] = std::min (ways[next_node], ways[getOldNodeNameByNew(node)] + table_[getOldNodeNameByNew(node)][next_node]);
    
    return ways[to];
}

Graph& Graph::sortTopologically ()
{
    int new_name = node_count_ - 1;
    bool flag;

    /* Установка значений по умолчению. */
    for (int i = 0; i < node_count_; i++)
        node_names_[i] = UNSET_NEW_NODE_NAME;

    while (new_name != -1)
    {
        flag = true;
        for (int i = 0; i < node_count_; i++)
        {
            if (node_names_[i] == UNSET_NEW_NODE_NAME && isDeadEnd(i))
            {
                flag = false;
                node_names_[i] = new_name--;
                break;
            }
        }

        if (flag)
        {
            std::cerr << "[ОШИБКА] Обнаружен цикл. Невозможно произвести топологическую сортировку узлов." << std::endl;
            b_ = false;
            return *this;
        }
    }

    b_ = true;
    return *this;
}

bool Graph::isDeadEnd (int node_num)
{
    for (int node_to = 0; node_to < node_count_; node_to++)
    {
        if ((node_names_[node_to] == UNSET_NEW_NODE_NAME) && (table_[node_num][node_to] != NO_WAY))
            return false;
    }
    return true;
}

int Graph::getNewNodeNameByOld (int node_name) const
{
    return node_names_[node_name];
}
int Graph::getOldNodeNameByNew (int node_name) const
{
    for (int node = 0; node < node_count_; node++)
        if (node_names_[node] == node_name)
            return node;
    return -1;
}

length Graph::getShortestWayByDijkstraAlgorithm (int from, int to)
{
    int i, j, k, min_node;
    bool is_used[node_count_];
    length ways[node_count_];

    for (i = 0; i < node_count_; i++)
    {
        is_used[i] = false;
        ways[i] = NO_WAY;
    }

    ways[from] = 0;
    
    for(i = 0; i < node_count_; i++)
    {
        min_node = UNSET_NEW_NODE_NAME;
        
        for(j = 0; j < node_count_; j++)
            if (!is_used[j] && (min_node == UNSET_NEW_NODE_NAME || ways[j] < ways[min_node]))
                min_node = j;
        
        if (min_node == UNSET_NEW_NODE_NAME)
            return NO_WAY;

        is_used[min_node] = true;
        for(k = 0; k < node_count_; k++)
            if(table_[min_node][k] != NO_WAY)
                ways[k] = std::min (ways[k], (ways[min_node] != NO_WAY ? ways[min_node] : 0) + table_[min_node][k]);
    }

    return ways[to];
}
