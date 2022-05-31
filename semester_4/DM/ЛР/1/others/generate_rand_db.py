#!/bin/python 

from random import randint

randgen = {
    "names": {
        "females": [
            "Авдотья",
            "Александра",
            "Анастасия",
            "Афродита",
            "Валерия",
            "Дарья",
            "Мария",
            "Юлия",
            "Яна"
        ],
        "males": [
            "Александр",
            "Виктор",
            "Грегорий",
            "Дмитрий",
            "Иннокентий",
            "Лев",
            "Михаил",
            "Павел",
            "Родион"
        ]
    },
    "surnames": {
        "females": [
            "Расторгуева",
            "Мармеладова",
            "Севастьянова",
            "Ануфрейчук",
            "Сухарева",
            "Деркач",
            "Вулпе",
            "Ануфриева",
            "Макеенкова",
            "Карташова",
            "Иващенко",
            "Дараева",
            
            "Бойко",
            "Неторжко",
            "Пынко",
            "Цалко"
        ],
        "males": [
            "Расторгуев",
            "Мармеладов",
            "Деркач",
            "Данченко",
            "Вахромеев",
            "Куртев",
            "Лысенко",
            "Усс",
            "Горох",
            "Косолапов",
            "Калинский",

            "Бойко",
            "Пынко",
            "Неторжко",
            "Цалко"
        ]
    },
    "patronymics_base": [
            "Александров",
            "Алексеев",
            "Анатольев",
            "Валерьев",
            "Викторов",
            "Витальев",
            "Владимиров",
            "Вячеславов",
            "Дмитриев",
            "Евгеньев",
            "Игорев",
            "Иоаннов",
            "Михайлов",
            "Николаев",
            "Романов",
            "Сергеев",
            "Тарасов"
    ],

    "drug_names": [
        "Ринофлуимуцил",
        "Остара Лакова",
        "Сульддибромид Форте",
        "Эвалар Плюс",
        "Сульддибромид",
        "Эвалар",
        "Атероклефит",
        "Тенотен",
        "Линк",
        "Эфонази",
        "Аналгон",
        "Димедролит",
        "Оралсепт",
        "Септолете Тотал",
        "Лизобакт",
        "Доритрицин",
        "Стрепсилс",
        "Фарингосепт",
        "Фурацилин",
        "Граммидин Нео",
        "Каметон",
        "Аква-Риносоль",
        "Пропосол"
    ],
    "drug_side-effects": [
        "Рвота",
        "Помутнение рассудка",
        "Раздражительность",
        "Аппатия",
        "Сонливость",
        "Диарея",
        "Кожная сыпь",
        "Ринит",
        "Конъюктивит",
        "Запор",
        "Отёчность конечностей",
        "Синдром отмены",
        "Судороги",
        "Гипотония",
        "Головные боли",
        "Сухость во рту",
        "Тахикардия",
        "Повышение АД",
        "Понижение АД",
        "Одышка",
        "Изменения вкуса",
        "Изменения аппетита",
        "Аритмия сердца",
        "Ощущение сердцебиения",
        "Повышение потоотделения",
        "Снижение массы тела",
        "Бессонница"
    ],

    "procedure_names": [
        "Погружной остеосинтез",
        "Внутрикостный остеосинтез",
        "Накостный остеосинтез",
        "Чрескостный остеосинтез",
        "Лазерная шлифовка лица",
        "Вскрытие и санация гематомы 1",
        "Вскрытие и санация гематомы 2",
        "Плазмолифтинг",
        "Прокол ушей",
        "Послеоперационная перевязка",
        "Пластика паховой грыжи",
        "Пластика пупочной грыжи",
        "ПХО"
    ],
    "procedure_equipments": [
        "АРГО 3400",
        "АРГО 3402",
        "ФАРГУС 3000 Эксклюзив",
        "ФАРГУС 3025",
        "FANGO MRP452-A",
        "FANGO MRP453-N",
        "SKP 59-NM Seraphim",
        "АРГО 95У",
        "АРГО 1593УК",
        "FANGO MSP9010-AT"
    ],

    "addresses": [
        "ул. 60-летия Октябрьской Революции",
        "ул. Административная",
        "ул. Арабатская",
        "ул. Генерала Острякова",
        "ул. Дубовая",
        "ул. Красная",
        "ул. Крымской Весны",
        "ул. Широкая",
        "ул. Яблочная",
        "ул. Ясельная",
        "ул. Ясная",
        "пр. Победы",
        "ул. Руднева",
        "ул. Шабалина",
        "Промышленная ул.",
        "ул. Генерала Мельника",
        "Айвовая ул.",
        "ул. Генерала Коломийца",
        "ул. Вакуленчука",
        "Июльская ул.",
        "Камышовое ш.",
        "ул. Правды",
        "Мартовская ул.",
        "Террасная ул.",
        "Гранатная ул.",
        "ул. Георгиевская Балка",
        "Ангарская ул.",
        "ул. Чехова",
        "ул. Симонок"
    ]
}



def get_random (a: list):
    return a[randint(1, len(a) - 1)]

def generate_rand_FIO () -> str:
    gender = ["males", "females"][randint(1, 2) - 1]
    return ("%s %s %s" % (
        get_random(randgen["surnames"][gender]),
        get_random(randgen["names"][gender]),
        get_random(randgen["patronymics_base"]) + ("на" if (gender == "females") else "ич")
    ))

def generate_address () -> str:
    return get_random(randgen["addresses"]) + ", " + str(randint (1, 99)) + (["", "", "А", "Б"])[randint(1, 4) - 1]

def generate_rand_side_effects () -> str:
    out_str = ""
    curr_num = -1
    
    while curr_num < (len (randgen["drug_side-effects"]) - randint (1, 5)):
        curr_num = randint (curr_num + 1, len(randgen["drug_side-effects"]) - 1)
        out_str += randgen["drug_side-effects"][curr_num] + ";"
    
    if out_str[-1] == ";":
        out_str = out_str[0:len(out_str) - 1]
    
    return out_str



def fill_first_table (n: int) -> list:
    stack = []
    uniq_id = 0

    for i in range (n):
        stack.append ({
            "id": uniq_id,
            "FIO": generate_rand_FIO(),
            "address": generate_address(),
            "birth_date": ("%04d-%02d-%02d" % (randint(1960, 2016), randint (1, 12), randint (1, 28)))
        })

        uniq_id -=- 1
    
    return stack

def fill_second_table (n: int) -> list:
    stack = []
    uniq_num = 1000

    for i in range (n):
        stack.append ({
            "id": uniq_num,
            "FIO": generate_rand_FIO ()
        })
        uniq_num -=- 1

    return stack

def fill_third_table () -> list:
    stack = []

    for drug_name in randgen["drug_names"]:
        stack.append ({
            "name": drug_name,
            "side_effect": generate_rand_side_effects()
        })

    return stack

def fill_fourth_table () -> list:
    stack = []

    for procedure in randgen["procedure_names"]:
        stack.append ({
            "procedure_title": procedure,
            "equipment": get_random(randgen["procedure_equipments"])
        })

    return stack

def create_sql_query (table_name: str, column_names: list, values: list) -> str:
    return ("INSERT INTO %s (%s) VALUES (%s);\n" % (
        table_name,
        ", ".join([f"{column_names[i]}" for i in range(len(column_names))]),
        ", ".join([(("'%s'" if type(values[i]) == str else "%s") % (str(values[i]))) for i in range(len(values))])
    ))

f_sql = open ("sql_queries.out", "w")

for patient in fill_first_table(23):
#    print ("%3d %s %s %s" % (
#        patient["id"],
#        patient["FIO"],
#        patient["address"],
#        patient["birth_date"]
#    ))
    query = create_sql_query("patient", ["id", "FIO", "address", "birth_date"], [patient["id"], patient["FIO"], patient["address"], patient["birth_date"]])
    #print(query)
    f_sql.write(query)


for surgeon in fill_second_table(15):
#    print ("%d %s" % (
#        surgeon["id"],
#        surgeon["FIO"]
#    ))
    query = create_sql_query("surgeon", ["id", "FIO"], [surgeon["id"], surgeon["FIO"]])
    #print(query)
    f_sql.write(query)

for drug in fill_third_table():
#    print ("%s %s" % (
#        drug["name"],
#        drug["side_effect"]
#    ))
    query = create_sql_query("drug", ["name", "side_effect"], [drug["name"], drug["side_effect"]])
    print(query)
    f_sql.write(query)

for proc in fill_fourth_table():
#    print ("%s %s" % (
#        proc["procedure_title"],
#        proc["equipment"]
#    ))
    query = create_sql_query("procedures", ["procedure_title", "equipment"], [proc["procedure_title"], proc["equipment"]])
    print(query)
    f_sql.write(query)
