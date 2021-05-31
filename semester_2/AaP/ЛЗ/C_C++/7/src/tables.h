#ifndef TABLES_H_
#define TABLES_H_ 1

#ifndef MAX_CHAR_SIZE_
    #define MAX_CHAR_SIZE_ 6
#endif

#define FIO_LENGHT_ 1024
#define STATUS_LENGHT_ 512

typedef struct T_DATA {
    char FIO[FIO_LENGHT_ * MAX_CHAR_SIZE_ + 1];       // ФИО
    long int year;                                    // Год рождения
    char gender[MAX_CHAR_SIZE_ + 1];                  // Пол
    char status[STATUS_LENGHT_ * MAX_CHAR_SIZE_ + 1]; // Семейное положение
    unsigned long int chcnt;                          // Количество детей
    unsigned long int salary;                         // Оклад
} t_data;

typedef struct T_ROW {
    t_data data;
    struct T_ROW *next;
    struct T_ROW *prev;
} t_row;

///////////////////////
// Прототипы функций //
///////////////////////

t_row *row_create (t_data data);
void row_del (t_row *row);
void print_row (const unsigned long int c, const t_data data);
void table_del (t_row *row);


/////////////
// Функции // 
/////////////

/*******************************************************************
 * @brief Инициализирует строку в таблице.
 * 
 * @param data Данные, которые необходимо записать в новую строчку.
 */
t_row *row_create (t_data data)
{
    t_row *nrow = (t_row *) malloc(sizeof(t_row));
    
    nrow->next = nrow->prev = NULL;
    nrow->data = data;

    return nrow;
}


/*******************************************************************
 * @brief Удаляет строку. Автоматически пересвязывает элементы.
 * 
 * @param row Строчка таблицы для удаления.
 */
void row_del (t_row *row)
{
    if (row->prev)
        row->prev->next = row->next;
    
    if (row->next)
        row->next->prev = row->prev;
    
    free(row);
}


/*******************************************************************
 * @brief Печать строчки.
 * 
 * @param c Порядковый номер.
 * @param data Данные для печати.
 */
void print_row (const unsigned long int c, const t_data data)
{
    printf("|%3lu| %20s | %4ld | %3s | %18s | %6lu | %8lu |\n",
        c,
        data.FIO,
        data.year,
        data.gender,
        data.status,
        data.chcnt,
        data.salary
    );
}


/**
 * @brief Удаление текущего элемента и всех последующих.
 * 
 * @param row Указатель на элемент, с которого необходимо удалять.
 */
void row_del_rec (t_row *row)
{
    if (!row) return;
    row_del_rec(row->next);
    free(row);
}


/**
 * @brief Печать полноценной таблицы. Если таблица не содержит элементы, выводится ошибка.
 * 
 * @param head Указатель на начало списка.
 */
void t_print (t_row *head)
{
    printf("+---+----------------------+------+-----+--------------------+--------+----------+\n");
    printf("| № |         ФИО          | ГРож | Пол | Семейное Положение | КолДет |  Оклад   |\n");
    printf("+---+----------------------+------+-----+--------------------+--------+----------+\n");

    if (!head)
    {
        printf("+                                 Данные отсутствуют                             +\n");
    }
    else
    {
        t_row *curr_row = head;
        unsigned long int counter = 0;
        while (curr_row)
        {
            print_row(++counter, curr_row->data);
            curr_row = curr_row->next;
        }
    }

    printf("+---+----------------------+------+-----+--------------------+--------+----------+\n");
    printf("\n\n");
}


/**
 * @brief Функция поиска элемента в списке по значению поля "FIO"
 * 
 * @param head Указатель на начало списка.
 * @param FIO Значение FIO.
 * @return t_row* Указатель на найденный элемент. NULL, если элемент не был найден.
 */
t_row *searchRowByFIO (t_row *head, char *FIO)
{
    t_row *curr_row = head;

    while (curr_row)
    {
        if (!strcmp(curr_row->data.FIO, FIO))
            break;
        curr_row = curr_row->next;
    }

    return curr_row;
}


/**
 * @brief Получить элемент по его id.
 * 
 * @param head Указатель на голову списка.
 * @param id ID элемента.
 * @return *t_row Указатель на этот элемент. Если id недостижимЮ, возвращщает NULL.
 */
t_row *getRowById (t_row *head, unsigned long int id)
{
    for (unsigned long int curr_id = 0; head && curr_id < id; head = head->next, curr_id++);
    return head;
}


/**
 * @brief Функция сортировки элементов в списке.
 * 
 * @param head Указатель на начало списка.
 */
void table_sort (t_row *head)
{
    t_row *tmp = 0; t_data d;
    unsigned long int elem_count = 0;

    for (tmp = head; tmp; elem_count++, tmp = tmp->next);

    for (int i = elem_count - 1; i > 0; i--)
    {
        tmp = head;
        for (int j = 0; j < i; j++)
        {
            if (strcmp(tmp->data.FIO, tmp->next->data.FIO) > 0)
            {
                d = tmp->data;
                tmp->data = tmp->next->data;
                tmp->next->data = d;
            }
            tmp = tmp->next;
        }
    }
}


/**
 * @brief Вставка элемента row в список с головой head. Вставка происходит с учётом сортировки.
 * 
 * @param head Указатель на начало списка.
 * @param row Указатель на элемент, который необходимо добавить.
 */
void SaddRowToTable (t_row **head, t_data *d)
{ 
	if (!(*head))
    { // Если головы не существует
        *head = row_create(*d);
        return;
    }

    if (strcmp((*head)->data.FIO, d->FIO) >= 0)
    { // Если элемент нужно вставить перед головой
        t_row *tmp = *head;
        *head = row_create(*d);
        (*head)->next = tmp;
        if ((*head)->next) (*head)->next->prev = *head;
        return;
    }

    t_row *tmp1;
    for (tmp1 = *head; tmp1->next && strcmp(tmp1->next->data.FIO, d->FIO) < 0; tmp1 = tmp1->next);

    t_row *tmp2 = row_create(*d);
    
    tmp2->next = tmp1->next;
    tmp2->prev = tmp1;

    tmp1->next = tmp2;
    if (tmp2->next) tmp2->next->prev = tmp2;

    return;
}


#endif
