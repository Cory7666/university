#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

///////////////////////////////////
// Блок препроцессорных директив //
///////////////////////////////////

#define DEFAULT_FILE_NAME ".database"

#define NAME_SIZE 1024
#define MARKET_SIZE 1024
#define CHAR_SIZE 6

#define MENU_CLEAR_FILE 1
#define MENU_ADD_STRUCTS 2
#define MENU_PRINT_STRUCTS 3
#define MENU_SEARCH_STRUCT 4
#define MENU_EXIT 5

//////////////////////////////////////
// Блок объявления типов и структур //
//////////////////////////////////////

struct PRICE {
	char name  [NAME_SIZE   * CHAR_SIZE];
	char market[MARKET_SIZE * CHAR_SIZE];
    unsigned long int price;
};

////////////////////////////////
// Блок объявления прототипов //
////////////////////////////////

unsigned long int fsize             (char *name);
void              file_clear        (char *name);
void              file_PrintStructs (char *name);
void              file_AddStructs   (char *name);
void			  file_SortStructs  (char *name);
int               struct_GetFromFile(FILE *f, struct PRICE *s);
void              struct_AddToFile  (FILE *f, struct PRICE s);
void              file_PrintStruct  (char *name);

/////////////////////////////////////////
//          Основная функция           //
/////////////////////////////////////////

int main ()
{
    // Подготовительный этап //

	unsigned short int answer = 0;
    FILE *f;                                                         // Файловая переменная
    if (!fsize(DEFAULT_FILE_NAME)) { f = fopen(DEFAULT_FILE_NAME, "w"); fclose(f); } // Создать файл, если он не существует


    // Выполнение основной части программы //

	while (answer != MENU_EXIT)
	{
		printf("Меню программы:\n");
		printf(" (%d) Очистить файл.\n",             MENU_CLEAR_FILE   );
		printf(" (%d) Добавить структуры в файл.\n", MENU_ADD_STRUCTS  );
		printf(" (%d) Вывести содержимое файла.\n",  MENU_PRINT_STRUCTS);
		printf(" (%d) Найти элемент.\n",             MENU_SEARCH_STRUCT);
		printf(" (%d) Выйти из программы.\n",        MENU_EXIT         );
		printf("\n");
		printf("$ "); scanf("%hd", &answer);

		switch (answer)
		{
			case MENU_EXIT:
				printf("Осуществляется выход из программы...\n");
				break;
			
			case MENU_CLEAR_FILE:
				printf("Очистка файла от старых данных...");
				file_clear(DEFAULT_FILE_NAME);
				printf("УДАЧА\n");
				break;
			
			case MENU_PRINT_STRUCTS:
				printf("Запуск функции печати структур из файла.\n");
				file_PrintStructs(DEFAULT_FILE_NAME);
				break;

			case MENU_ADD_STRUCTS:
				printf("Запущена функция добавления структур в файл.\n");
				file_AddStructs(DEFAULT_FILE_NAME);
				break;
			
			case MENU_SEARCH_STRUCT:
				printf("Запущена функция поиска структуры в файле.\n");
				file_PrintStruct(DEFAULT_FILE_NAME);
				break;
		}

		printf("Нажмите на \"%s\" для продолжения...\n", "h");
		while ( 'h' != getchar());
	}

    // Завершающий этап //

	return 0;
}

/////////////////////////////////////////
//     Блок инициализации функций      //
/////////////////////////////////////////

/********************************************************************************************************************
 * @brief Определяет размер файла в байтах. Возращает 0, если размер файла равен нулю или если файл невозможно открыть для чтения
 * 
 * @param name Путь к файлу
 * @return unsigned long int Размер файла в байтах
 */

unsigned long int fsize (char *name)
{
	FILE *f = fopen(name, "r"); if (!f) return 0;
	
	fseek(f, 0, SEEK_END);
	unsigned long int l = ftell(f);
	
	fclose(f);
	return l;
}


/********************************************************************************************************************
 * @brief Функция очистки файла.
 * 
 * @param name Путь к файлу.
 */

void file_clear (char *name)
{
	fclose(fopen(name, "w"));
	return;
}


/********************************************************************************************************************
 * @brief Сохраняет структуру в данный файл.
 * 
 * @param f Данный файл.
 * @param s Структура для записи.
 */

void struct_AddToFile (FILE *f, struct PRICE s)
{
	fwrite(s.name,   sizeof(char),    CHAR_SIZE * NAME_SIZE,   f);
	fwrite(s.market, sizeof(char),    CHAR_SIZE * MARKET_SIZE, f);
	fwrite(&s.price, sizeof(s.price), 1,                       f);
	return;
}


/********************************************************************************************************************
 * @brief Получение структуры из файла.
 * 
 * @param f Данный файл.
 * @param s Структура, куда записать данные.
 */

int struct_GetFromFile (FILE *f, struct PRICE *s)
{
	fread(s->name,    sizeof(char),    CHAR_SIZE * NAME_SIZE,    f);
	fread(s->market,  sizeof(char),    CHAR_SIZE * MARKET_SIZE,  f);
	return fread(&(s->price), sizeof(s->price), 1,                      f);
}


/********************************************************************************************************************
 * @brief Функция печати всех структур из файла.
 * 
 * @param name Имя данного файла.
 */

void file_PrintStructs (char *name)
{
	printf("Проверка файла на существование данных...");
	if (fsize(name) < 1)
	{
		printf("ПОТРАЧЕНО: файл пуст или недоступен для чтения.\n");
		return;
	}
	printf("УДАЧА\n");

	printf("Осуществляется проверка валидности сохранённых данных...");
	if ( fsize(name) % sizeof(struct PRICE) )
	{
		printf("ПОТРАЧЕНО: данные в файле не соответствуют стандартам.\n");
		return;
	}
	printf("УДАЧА\n");

	FILE *f = fopen(name, "r");
	struct PRICE s; unsigned long int counter = 1;

	while (struct_GetFromFile(f, &s))
	{
		printf("Товар №%lu\n", counter++);
		printf(" * Наименование: \"%s\".\n",  s.name  );
		printf(" * Поставщик:    \"%s\".\n",  s.market);
		printf(" * Стоимость товара: %lu.\n", s.price );
		printf("\n");
	}

	fclose(f);
}

/********************************************************************************************************************
 * @brief Функция добавления структур в файл.
 * 
 * @param name Имя данного файла.
 */

void file_AddStructs (char *name)
{
	FILE *f;

	printf("Попытка открыть файл...");
	if (!(f = fopen(DEFAULT_FILE_NAME, "a")))
	{
		printf("ПОТРАЧЕНО: файл недоступен для записи.\n");
		return;
	}
	printf("УДАЧА\n");

	struct PRICE s;
	char answer = 'y';
	size_t nl = NAME_SIZE, ml = MARKET_SIZE;

	printf("Перед началом ввода нажмите на \"%s\" для продолжения...\n", "h"); while ( 'h' != getchar());

	while (tolower(answer) != 'n')
	{

		printf("А теперь введите цену товара:\n");
		printf("$ "); scanf("%lu", &s.price);

		getchar();

		printf("Введите Наименование товара:\n");
		printf("$ "); fseek(stdin, 0, SEEK_END); scanf("%s", s.name);

		printf("Введите Название организации:\n");
		printf("$ "); fseek(stdin, 0, SEEK_END); scanf("%s", s.market);

		struct_AddToFile(f, s);

		printf("Отлично! Новый продукт добавлен в файл.\n");
		
		answer = '\n';
		while (answer == '\n') 
		{
			printf("Продолжить ввод? [Y/n] ");
			scanf("%c", &answer);
			printf("\n");
		}
	}

	fclose(f);

	file_SortStructs(name);

	return;
}

/********************************************************************************************************************
 * @brief Функция, которая сортирует структуры в данном файле.
 * 
 * @param name Имя данного файла.
 */

void file_SortStructs (char *name)
{
	FILE *f;
	if (!(f = fopen(name, "r+b"))) return;

	struct PRICE s1, s2;
	int c = fsize(DEFAULT_FILE_NAME) / sizeof(struct PRICE);

	for (int j = c - 1; j > 0; j--)
	{
		for (int i = 0; i < j; i++)
		{
			fseek(f, i * sizeof(struct PRICE), SEEK_SET);

			struct_GetFromFile(f, &s1);
			struct_GetFromFile(f, &s2);

			if (strcmp(s1.name, s2.name) > 0)
			{
				fseek(f, i * sizeof(struct PRICE), SEEK_SET);

				struct_AddToFile(f, s2);
				struct_AddToFile(f, s1);
			}
		}
	}

	fclose(f);
	return;
}

/**
 * @brief Функция поиска структуры в файле. Найденная структура выводится на экран.
 * 
 * @param name Имя данного файла.
 */

void file_PrintStruct(char *name)
{
	FILE *f;
	if (!(f = fopen(name, "r+b"))) return;

		struct PRICE s_user, s_file;
		int isFound = 0;

		printf("Введите наименование товара: "); fseek(stdin, 0, SEEK_END); scanf("%s", s_user.name);

		while (!feof(f))
		{
			struct_GetFromFile(f, &s_file);
			
			if (!strcmp(s_user.name, s_file.name))
			{
				isFound = 1;
				break;
			}
		}

		if (isFound)
		{
			printf("Элемент найден:\n");
			printf(" * Наименование: \"%s\".\n", s_file.name);
			printf(" * Поставщик:    \"%s\".\n", s_file.market);
			printf(" * Стоимость:    %lu.\n\n", s_file.price);
		} else {
			printf("Элемент не найден.\n\n");
		}
	
	fclose(f);
	return;
}