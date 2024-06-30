#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>

#ifndef LAB8_HPP
#define LAB8_HPP

namespace lab8
{
    class Graph;

    /* Тип: длина пути от одной вершины к другой. */
    using length = unsigned int;

    /* Длина пути между несвязанными узлами. */
    constexpr length NO_WAY = (length) -1;
    /* Значение по умолчанию в new_names_for_nodes_. */
    constexpr int UNSET_NEW_NODE_NAME = -1;

    /* Получить суммарную длину кратчайшего остового дерева. */
    length ask_God_for_answer(const Graph& graph, int start_node);

    /* Граф */
    class Graph
    {
        friend length ask_God_for_answer(const Graph& graph, int start_node);
        
        public:
            /* Заполнить граф данными, вводимыми пользователем. */
            Graph (int node_count);
            /* Заполнить граф на основе данных из файла. */
            Graph (const std::string& filename);
            /* Преобразование в строку. */
            operator std::string() const;

            Graph () = delete;
            Graph (const Graph&) = delete;
            ~Graph();
        private:
            /* Таблица точек. */
            length **table_;
            /* Количество точек в графе. */
            int node_count_;
    };

}

#endif //! LAB8_HPP
