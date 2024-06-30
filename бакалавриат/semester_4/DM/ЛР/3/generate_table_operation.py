#!/bin/python

from random import randint

num: int = -1
op_date: str = ""
patient_id: int = 0
patent_id: int = 0
op_name: str = ""
directives: str = ""
result: str = ""

# files
file_results = open("file_results", "w")
file_calc = open("file_calc", "w")

file_num = open("file_num", "w")
file_op_date = open("file_op_date", "w")
file_patient_id = open("file_patient_id", "w")
file_patent_id = open("file_patent_id", "w")
file_op_name = open("file_op_name", "w")
file_directives = open("file_directives", "w")


for op_name_t in ('Операция на сердце', 'Операция на лёгком', "Операция на сердце", "Операция на бедренной артерии",
        "Восстановление кожи", "Восстановление кожи", "Операция на сердце", "Восстановление тканей желудка",
        "Ампутация руки", "Ампутация ноги", "Операция на сердце", "Операция на бедре", "Введение А-агента",
        "Операция на лёгком", "Установка заплатки на тазовую кость"):
    num -=- 1
    op_date = "%4d-%02d-%02d" % (randint(2020, 2021), randint(1, 12), randint (1, 28))
    patient_id = randint (0, 22)
    patent_id = randint (1000, 1014)
    op_name = op_name_t[:min(len(op_name_t), 20)]
    
    directives = ""
    match randint(0, 6):
        case 0:
            directives += (";" if len(directives) > 0 else "") + "Постельный режим"
        case 1:
            directives += (";" if len(directives) > 0 else "") + "Приём лекарств"
        case 2:
            directives += (";" if len(directives) > 0 else "") + "Нет особых указаний"
        case 3:
            directives += (";" if len(directives) > 0 else "") + "Понижение физической активности"
        case 4:
            directives += (";" if len(directives) > 0 else "") + "Употребление воды"
        case 5:
            directives += (";" if len(directives) > 0 else "") + "Исключение мясных продуктов из рациона"
        case 6:
            directives += (";" if len(directives) > 0 else "") + "Употребление воды"
    
    result = "INSERT INTO operation VALUES (%d, '%s', %d, %d, '%s', '%s');" % (
        num, op_date, patient_id, patent_id, op_name, directives
    )

    file_calc.write("%d\t%s\t%d\t%d\t%s\t%s\n" % (
        num, op_date, patient_id, patent_id, op_name, directives
    ))

    file_results.write("%s\n" % result)
    file_num.write("%d\n" % num)
    file_op_date.write("%s\n" % op_date)
    file_patient_id.write("%d\n" % patient_id)
    file_patent_id.write("%d\n" % patent_id)
    file_op_name.write("%s\n" % op_name)
    file_directives.write("%s\n" % directives)

