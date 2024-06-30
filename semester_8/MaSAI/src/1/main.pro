:- dynamic product/3.

product(planks, 'StroySberLesnichestvo', 26).
product(planks, 'ForceOfForest', 28).
product(nails, 'Iron Factory Ltd.', 5).

print_fact(Title, Company, Price) :-
    write('Наименование="'), write(Title),
    write('", Компания="'), write(Company),
    write('", Стоимость="'), write(Price),
    write('"'), nl.

delete_fact_by_title(Title) :-
    retract(product(Title, _, _)).

write_term(Term) :-
    Term,
    display(Term), write('.'), nl,
    fail;
    true.

export_to(Filepath) :-
    tell(Filepath),
    write_term(product(_, _, _)).
    told.

import_from(Filepath) :-
    see(Filepath),
    read(X),
    assertz(X),
    seen.

% 1. добавление записи в базу данных
interactive_append_fact :-
    write('Наименование товара: '),
    read(Title),
    write('Производитель: '),
    read(Company),
    write('Стоимость: '),
    read(Price),
    print_fact(Title, Company, Price),
    assertz(product(Title, Company, Price)),
    write('Добавлено.'),
    nl.

% 2. удаление записи из базы данных
interactive_delete_fact :-
    write('Наименование товара для удаления: '),
    read(Title),
    delete_fact_by_title(Title),
    write('Удалено.'),
    nl.

% 3. просмотр базы данных
interactive_display_facts :-
    product(Title, Company, Price),
    print_fact(Title, Company, Price).

% 4. сохранение базы данных в файле
interactive_export :-
    write('Сохранить как: '),
    read(Filepath),
    export_to(Filepath),
    write('Экспортировано.'),
    nl.

% 5. сохранение базы данных в файле
interactive_import :-
    write('Загрзить из: '),
    read(Filepath),
    retractall(product(_, _, _)),
    import_from(Filepath),
    write('Импортировано.'),
    nl.

% 6. корректировка данных в базе по названию товара
interactive_update_product :-
    write('Наименование товара: '),
    read(Title),
    write('Новый поставщик: '),
    read(NewCompany),
    write('Новая цена: '),
    read(NewPrice),
    retract(product(Title, _, _)),
    assertz(product(Title, NewCompany, NewPrice)),
    write('Готово.').

% 7. вывод на экран информации о товаре, название которого введено с клавиатуры
interactive_search_product :-
    write('Наименование товара: '),
    read(Title),
    product(Title, Company, Price),
    print_fact(Title, Company, Price);
    write('Нет товаров с таким именем.'),
    nl,
    fail.

rel1(1) :- product(nails, _, _), product(planks, _, _).
rel1(2) :- product(nails, _, _), product(table, _, _).
rel1(10) :- product(nails, _, _); product(planks, _, _).
rel1(11) :- product(table, _, _); product(planks, _, _).
rel1(20) :- product(table, _, _), not(product(planks, _, _)).
