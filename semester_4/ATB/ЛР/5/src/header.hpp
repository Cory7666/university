#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <unistd.h>

#ifndef HEADER_HPP
#define HEADER_HPP

namespace l
{
    class Graph;

    /* Длина пути от одной вершины к другой. */
    using length = unsigned int;

    /* Длина пути между несвязанными узлами. */
    static constexpr length NO_WAY = (length) -1;
    /* Значение по умолчанию в new_names_for_nodes_. */
    static const int UNSET_NEW_NODE_NAME = -1;

    /* Граф */
    class Graph
    {
        public:
            Graph ();
            /* Заполнить граф данными, вводимыми пользователем. */
            Graph (int node_count);
            /* Заполнить граф на основе данных из файла. */
            Graph (const std::string& filename);
            Graph (const Graph&) = delete;
            ~Graph();
            /* Ручное занесение данных о вершинах. */
            Graph& fill();
            /* Занесение данных о вершинах из файла. */
            Graph& fill(const std::string& filename);
            /* Получить старое имя узла по новому. */
            int getOldNodeNameByNew (int node_name) const;
            /* Получить новое имя узла по старому. */
            int getNewNodeNameByOld (int node_name) const;
            /* Преобразование в строку. */
            operator std::string() const;
            /* Получение длины пути из from в to. */
            length operator() (int from, int to) const;
            /* Получение длины пути из from в to (Алгоритм Дейкстры) */
            length getShortestWayByDijkstraAlgorithm (int from, int to);
        private:
            /* Провести топологическую сортировку узлов. */
            Graph& sortTopologically ();
            /* Является ли указанный узел тупиковым. Проверка
            проводится на основе данных из массива новых имён для
            узлов. */
            bool isDeadEnd (int node_num);
            /* Таблица путей в ориентированном графе. */
            l::length **table_;
            /* Таблица новых имён для точек после топологической сортировки. */
            int *node_names_;
            /* Количество узлов в графе. */
            int node_count_;
            /* Можно ли искать методом динамического программирования. */
            bool b_;
    };
};

#endif //! HEADER_HPP file
