///////////////////////////////////
// Блок препроцессорных директив //
///////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tables.h"
#include "files.h"

#define MENU_EXIT      0 
#define MENU_LOAD_DATA 1 
#define MENU_SAVE_DATA 2 
#define MENU_ORG       3 
#define MENU_ADD_ONE   4 
#define MENU_DEL       5 
#define MENU_PRINT_TBL 6 
#define MENU_SORT_LIST 7 
#define MENU_SADD_ONE  8

#define DEFAULT_FILENAME ".7.database"

///////////////////////////////////
//       Прототипы функций       //
///////////////////////////////////

void menu_Print     ();
t_row *menu_OrgTable();
void menu_DelElem   (t_row **head);
void menu_AddOne    (t_row **head);
void menu_SAddOne   (t_row **head);
void menu_SaveTable (const t_row *head, const char *name);
void menu_LoadTable (t_row **head, const char *name);


///////////////////////////////////
//       Основная функция        //
///////////////////////////////////

int main ()
{
    // Начальный этап

    t_row *head = NULL;
    int u_answ = -1;

    // Основной алгоритм
    
    while (u_answ != MENU_EXIT)
    {
        menu_Print();

        do {
            printf("$: ");
            fseek(stdin, 0, SEEK_END);
            u_answ = getc(stdin);
        } while (u_answ == '\n');

        switch (u_answ -= (int) '0')
        {
            case MENU_SAVE_DATA:
                menu_SaveTable (head, DEFAULT_FILENAME);
                break;

            case MENU_LOAD_DATA:
                menu_LoadTable(&head, DEFAULT_FILENAME);
                break;

            case MENU_ORG:
                printf("Начато удаление старой таблицы...");
                row_del_rec(head); head = 0;
                printf("УДАЧА\n");

                printf("Организация новой таблицы...\n\n");
                head = menu_OrgTable();
                break;

            case MENU_PRINT_TBL:
                printf("Начата печать данных в табличном виде.\n\n");
                t_print(head);
                break;

            case MENU_DEL:
                printf("Запущена процедура удаления элемента таблицы...\n\n");
                menu_DelElem(&head);
                break;
            
            case MENU_ADD_ONE:
                printf("Запуск функции добавления одного элемента в конец таблицы...\n\n");
                menu_AddOne(&head);
                break;
            
            case MENU_SORT_LIST:
                printf("Попытка отсортировать таблицу...");
                table_sort(head);
                printf("УДАЧА\n");
                break;
            
            case MENU_SADD_ONE:
                printf("Запуск функции добавления одного элемента...\n\n");
                menu_SAddOne(&head);
                break;

            case MENU_EXIT:
                printf("Выход из программы...\n");
                break;

            default:
                printf("\033[41;1;37mOШИБКА\033[0m: Действие \"%d\" неизвестно программе. Повторите ввод.\n", u_answ);
                break;
        }
    }

    // Завершительный этап

    row_del_rec(head);
    head = NULL;

    return 0;
}

///////////////////////////////////
//     Определение функций       //
///////////////////////////////////

void menu_Print ()
{
    printf("( %d ) Выйти из программы.\n"                         , MENU_EXIT     );
    printf("( %d ) Загрузить данные из файла (по умолчанию %s).\n", MENU_LOAD_DATA, DEFAULT_FILENAME);
    printf("( %d ) Сохранить данные в файл (по умолчанию %s).\n",   MENU_SAVE_DATA, DEFAULT_FILENAME);
    printf("( %d ) Удалить старую и Организовать новую таблицу.\n", MENU_ORG      );
    printf("( %d ) Добавить один элемент в конец таблицы.\n"      , MENU_ADD_ONE  );
    printf("( %d ) Удалить элемент.\n"                            , MENU_DEL      );
    printf("( %d ) Вывести таблицу.\n"                            , MENU_PRINT_TBL);
    printf("( %d ) Отсортировать данные в таблице (по ФИО).\n"    , MENU_SORT_LIST);
    printf("( %d ) *my* Вставить элемент.\n"                      , MENU_SADD_ONE );
    printf("\n");
}

t_row *menu_OrgTable ()
{
    unsigned long int counter = 1;
    unsigned int answer = 0;
    t_row *head = 0, *curr_row = 0;
    t_data d;

    printf("Создадим первый элемент!\n");
    printf("Введите ФИО человека:                "); fseek(stdin, 0, SEEK_END); scanf("%s", d.FIO);
    printf("Введите год рождения человека:       "); scanf("%ld", &d.year);
    printf("Введите пол человека:                "); scanf("%s", d.gender);
    printf("Введите семейное положение человека: "); scanf("%s", d.status);
    printf("Введите количество детей в семье:    "); scanf("%lu", &d.chcnt);
    printf("Введите оклад:                       "); scanf("%lu", &d.salary);

    head = curr_row = row_create(d);

    printf("Продолжить ввод? [Y/n] "); getchar(); answer = getchar();

    while (answer != 'n' && answer != 'N' && answer != 'н' && answer != 'Н')
    {
        printf("\n\n<===================>\n\n");
        printf("Создадим %lu элемент таблицы!\n", ++counter);
        printf("Введите ФИО человека:                "); fseek(stdin, 0, SEEK_END); scanf("%s", d.FIO);
        printf("Введите год рождения человека:       "); scanf("%ld", &d.year);
        printf("Введите пол человека:                "); scanf("%s", d.gender);
        printf("Введите семейное положение человека: "); scanf("%s", d.status);
        printf("Введите количество детей в семье:    "); scanf("%lu", &d.chcnt);
        printf("Введите оклад:                       "); scanf("%lu", &d.salary);

        curr_row->next = row_create(d);
        curr_row->next->prev = curr_row;
        curr_row = curr_row->next;

        printf("Продолжить ввод? [Y/n] "); getchar(); answer = getchar();

    }

    printf("Ввод завершён. Добавлено %lu элемент(-a,-ов). Возврат в меню.\n", counter);

    return head;
}


/**
 * @brief Запуск из меню функции удаления элемента.
 * 
 * @param head Указатель на начало списка.
 */
void menu_DelElem (t_row **head)
{
    char FIO[FIO_LENGHT_ * MAX_CHAR_SIZE_];
    printf("Введите ФИО удаляемого человека:\n");
    printf("$: "); scanf("%s", FIO);
    
    t_row *row = searchRowByFIO(*head, FIO);

    if (row)
    {
        printf("Найдено поле:\n");
        if (row->prev)
        {
            if (row->prev->prev)
                printf("...\n");
            print_row(0, row->prev->data);
        }
        print_row(0, row->data);
        if (row->next)
        {
            print_row(0, row->next->data);
            if (row->next->next)
                printf("...\n");
        }

        unsigned int answer;
        printf("Вы действительно хотите удалить дайнный элемент? [y/N] "); getchar(); answer = getchar();
        printf("Удаление элемента...");

        if (answer == 'Y' || answer == 'y')
        {   
            if (*head == row)
            {
                *head = row->next;
            }
            row_del(row);

            printf("УДАЧА\n");
        }
        else
            printf("ОТКЛОНЕНО\n");
    }
    else
    {
        printf("Указанный элемент не найден.\n");
    }
}


/**
 * @brief Запуск из меню функции добавления одного элемента в список.
 * 
 * @param head Указатель на начало списка.
 */
void menu_AddOne (t_row **head)
{
    t_data d;

    printf("Введите ФИО человека:                "); fseek(stdin, 0, SEEK_END); scanf("%s", d.FIO);
    printf("Введите год рождения человека:       "); scanf("%ld", &d.year);
    printf("Введите пол человека:                "); scanf("%s", d.gender);
    printf("Введите семейное положение человека: "); scanf("%s", d.status);
    printf("Введите количество детей в семье:    "); scanf("%lu", &d.chcnt);
    printf("Введите оклад:                       "); scanf("%lu", &d.salary);

    printf("Попытка добавления в конец файла...");
    if (!*head)
    {
        printf("\nТаблица пуста. Попытка добавить первую запись...");
        *head = row_create(d);
    }
    else
    {
        t_row *tmp1 = *head, *tmp2 = row_create(d);

        while (tmp1->next)
            tmp1 = tmp1->next;
        
        tmp1->next = tmp2;
        tmp2->prev = tmp1;
    }

    printf("УДАЧА\n");
}

void menu_SAddOne (t_row **head)
{
    t_data d;

    printf("Введите ФИО человека:                "); fseek(stdin, 0, SEEK_END); scanf("%s", d.FIO);
    printf("Введите год рождения человека:       "); scanf("%ld", &d.year);
    printf("Введите пол человека:                "); scanf("%s", d.gender);
    printf("Введите семейное положение человека: "); scanf("%s", d.status);
    printf("Введите количество детей в семье:    "); scanf("%lu", &d.chcnt);
    printf("Введите оклад:                       "); scanf("%lu", &d.salary);

    printf("Попытка добавления в таблицу...");

    SaddRowToTable(head, &d);

    printf("УДАЧА\n");
}



void menu_SaveTable(const t_row *head, const char *name)
{
    if (!head)
    {
        printf("Ошибка: таблицы не существует.\n");
        return;
    }

    FILE *f = fopen(DEFAULT_FILENAME, "w");
    if (!f)
    {
        printf("Ошибка: файла сохранений не существует.\n");
        return;
    }

    while (head)
    {
        file_saveData(f, &(head->data));
        head = head->next;
    }

    fclose(f);
    return;
}



void menu_LoadTable (t_row **head, const char *name)
{
    row_del_rec(*head);
    *head = NULL;

    FILE *f = fopen(name, "r");
    if (!f)
    {
        printf("Ошибка: файла сохранений не существует.\n");
        return;
    }


    t_data  tmp_d;
    t_row  *tmp_l;

    while (file_getData(f, &tmp_d))
    {
        if (!*head)
        {
            *head = row_create(tmp_d);
            tmp_l = *head;
        }
        else
        {
            tmp_l->next = row_create(tmp_d);
            tmp_l->next->prev = tmp_l;
            tmp_l = tmp_l->next;
        }
    }


    fclose(f);
    return;
}