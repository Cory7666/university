#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./tree.h"
#include "./files.h"

static unsigned long int LAST_ID = 0;

void menu_create_tree (t_leaf **root);
int menu_create_from_file (char *fname, t_leaf **root);
int menu_save_to_file (char *fname, t_leaf **root);
void menu_search_elem (t_leaf *root);
void menu_add_one (t_leaf **root);

int main ()
{
    t_leaf *root = NULL;
    int answer = -1;

    do
    {
        printf("\n\n\n");

        printf("Действия: \n");
        printf("  (0) Выйти из программы.\n");
        printf("  (1) Загрузить из файла \".database.8\".\n");
        printf("  (2) Сохранить в файл \".database.8\".\n");
        printf("  (3) Создать новое дерево.\n");
        printf("  (4) Добавить один элемент.\n");
        printf("  (5) Печать дерева.\n");
        printf("  (6) *my* Найти элемент в дереве.\n\n");
        printf("$: "); scanf("%d", &answer);

        printf("\n\n\n");

        switch (answer)
        {
            case 0:
                goto A;
                break;
            
            case 1:
                if (!menu_create_from_file(".database.8", &root))
                    printf("Может быть загружено!\n");
                else
                    printf("Не загружено!\n");
                break;

            case 2:
                if (!menu_save_to_file(".database.8", &root))
                    printf("Может быть сохранено!\n");
                else
                    printf("Не сохранено!\n");
                break;
            
            case 3:
                menu_create_tree(&root);
                break;
            
            case 4:
                menu_add_one(&root);
                break;
            
            case 5:
                if (root)
                    print_branch(root, 1);
                else
                    printf("Дерево не существует!\n");
                break;
            
            case 6:
                menu_search_elem(root);
                break;
            
            default:
                printf("Неверное действие.\n");
                break;
        }

    } while (1);

    A:
    

    return 0;
}

void menu_create_tree (t_leaf **root)
{
    del_branch(root); LAST_ID = 0;

    t_leaf *new_leaf = NULL;
    char answer[MAX_CHAR_SIZE_ + 1];

    do
    {
        new_leaf = (t_leaf *) malloc( sizeof(t_leaf) );

        printf("Введите ФИО:                "); scanf("%s",  new_leaf->data.FIO);       fseek(stdin, 0, SEEK_END);
        printf("Введите Год рождения:       "); scanf("%ld", &(new_leaf->data.year));   fseek(stdin, 0, SEEK_END);
        printf("Введите Пол:                "); scanf("%s",  new_leaf->data.gender);    fseek(stdin, 0, SEEK_END);
        printf("Введите Семейное положение: "); scanf("%s",  new_leaf->data.status);    fseek(stdin, 0, SEEK_END);
        printf("Введите Количество детей:   "); scanf("%lu", &(new_leaf->data.chcnt));  fseek(stdin, 0, SEEK_END);
        printf("Введите Оклад:              "); scanf("%lu", &(new_leaf->data.salary)); fseek(stdin, 0, SEEK_END);

        new_leaf->id = LAST_ID++;
        add_leaf(root, new_leaf);

        printf("Новый элемент добавлен. Его U_ID: %lu. Продолжить ввод [Y/n] ?: ", new_leaf->id); scanf("%s", answer);

    } while (*answer != 'n' && *answer != 'N' && *answer != 'н');
}

int menu_create_from_file (char *fname, t_leaf **root)
{
    FILE *f;
    if (!(f = fopen(fname, "r"))) return 1;

    del_branch(root); LAST_ID = 0;
    t_data data;

    while (file_getData(f, &data))
    {
        t_leaf *new_leaf = create_leaf(&data);
        new_leaf->id = LAST_ID++;
        add_leaf(root, new_leaf);
    }

    fclose(f);

    return 0;
}

int menu_save_to_file (char *fname, t_leaf **root)
{
    FILE *f;
    if (!(f = fopen(fname, "w"))) return 1;

    save_branch(*root, f);

    fclose(f);
    return 0;
}

void menu_search_elem (t_leaf *root)
{
    if (!root) {printf("Дерево пустое!\n"); return; }

    char FIO[FIO_LENGHT_ * MAX_CHAR_SIZE_ + 1];
    printf("Введите ФИО: "); scanf("%s", FIO); fseek(stdin, 0, SEEK_END);

    t_leaf *tmp = root; int result = 0, level = 0;
    while (tmp)
    {
        level++;
        result = strcmp(tmp->data.FIO, FIO);

        if (!result)
        {
            printf("Элемент найден. Его u_id: %lu. Длина: %d.\n", tmp->id, level - 1);
            return;
        }
        else
            if (result >= 0)
                tmp = tmp->right;
            else
                tmp = tmp->left;
    }
    printf("Элемент не найден!\n");
}

void menu_add_one (t_leaf **root)
{
    t_leaf *new_leaf = (t_leaf *) malloc( sizeof(t_leaf) );

    printf("Введите ФИО:                "); scanf("%s",  new_leaf->data.FIO);       fseek(stdin, 0, SEEK_END);
    printf("Введите Год рождения:       "); scanf("%ld", &(new_leaf->data.year));   fseek(stdin, 0, SEEK_END);
    printf("Введите Пол:                "); scanf("%s",  new_leaf->data.gender);    fseek(stdin, 0, SEEK_END);
    printf("Введите Семейное положение: "); scanf("%s",  new_leaf->data.status);    fseek(stdin, 0, SEEK_END);
    printf("Введите Количество детей:   "); scanf("%lu", &(new_leaf->data.chcnt));  fseek(stdin, 0, SEEK_END);
    printf("Введите Оклад:              "); scanf("%lu", &(new_leaf->data.salary)); fseek(stdin, 0, SEEK_END);

    new_leaf->id = LAST_ID++;
    add_leaf(root, new_leaf);

    printf("Новый элемент добавлен. Его U_ID: %lu.\n", LAST_ID);
}