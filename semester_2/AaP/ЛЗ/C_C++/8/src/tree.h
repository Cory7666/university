#ifndef TREE_H

#define TREE_H 1

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

typedef struct T_LEAF {
    unsigned long int id;
    t_data data;
    struct T_LEAF *left;
    struct T_LEAF *right;
} t_leaf;

size_t  file_saveData(FILE *f, t_data *d);
int     file_getData (FILE *f, t_data *d);

/**
 * @brief Создаёт лист дерева.
 * 
 * @param d 
 * @return t_leaf* 
 */

t_leaf *create_leaf (t_data *d)
{
    t_leaf *t = (t_leaf *) malloc(sizeof(t_leaf));
    t->right = t->left = NULL;
    t->data = *d;
    
    return t;
}

/**
 * @brief Удаляет ветку.
 * 
 * @param p 
 */

void del_branch (t_leaf **p)
{
    if (!(*p)) return;

    del_branch(&((*p)->left));
    del_branch(&((*p)->right));

    free(*p); *p = NULL;
}

/**
 * @brief Печать ветки на экран.
 * 
 * @param p 
 * @param margin_left 
 */

void print_branch (t_leaf *p, unsigned long int level)
{
    if (!p) return;
    int i;

    print_branch(p->left, level + 1);

    for (i = 1; i++ < level; printf("    ")); printf("УРОВЕНЬ %lu <u_id %lu>\n",   level, p->id);
    for (i = 1; i++ < level; printf("    ")); printf("ФИО:                %-16s\n", p->data.FIO);
    for (i = 1; i++ < level; printf("    ")); printf("Год рождения:       %lu\n" , p->data.year);
    for (i = 1; i++ < level; printf("    ")); printf("Пол:                %s\n",   p->data.gender);
    for (i = 1; i++ < level; printf("    ")); printf("Семейное положение: %-16s\n", p->data.status);
    for (i = 1; i++ < level; printf("    ")); printf("Количество детей:   %lu\n",  p->data.chcnt);
    for (i = 1; i++ < level; printf("    ")); printf("Оклад:              %lu\n",  p->data.salary);

    print_branch(p->right, level + 1);
}


void add_leaf (t_leaf **branch, t_leaf *leaf)
{
    if (!(*branch)) { *branch = leaf; return; }

    if ( strcmp( (*branch)->data.FIO, leaf->data.FIO ) < 0 )
        add_leaf ( &((*branch)->left),  leaf );
    else
        add_leaf ( &((*branch)->right), leaf );
}

void save_branch (t_leaf *elem, FILE *f)
{
    if (!elem) return;

    file_saveData(f, &(elem->data));
    save_branch(elem->left, f);
    save_branch(elem->right, f);
}

#endif

