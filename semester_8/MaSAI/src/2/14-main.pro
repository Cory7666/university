% Оценки братьев
grade(aleksey, [4, 5]).
grade(leonid, [3, 2]).
grade(aleksandr, [2, 4]).

kuv().

% Возвращает во втором параметре последние два элемента списка в
% первом параметре.
last_two_elements(List, Result) :-
    append(_, [X, Y], List),
    Result = [X, Y].

% Указывает, что третьим параметром является список, переданный вторым
% параметром, в котором отсутствует элемент, переданный первым.
del(X,[X|T],T).
del(X,[Н|T],[Н|T1]) :- del(X, T, T1).

% Добавляет элемент, переданный первым, в список, переданый вторым, а
% результат записывает в третий параметр.
insert(X, L1, L) :- del(X, L, L1).

% Перемещает элементы из одного списка в другой.
swap([],[]).
swap([X|L],P):-swap(L,L1), insert(X, L1, P).

% Определяет максимальное из двух чисел.
max(X, Y, Max) :-
    (X >= Y -> Max = X ; Max = Y).

% Найти решение для переданного списка оценок.
find_next(G) :-
    check(X,G),
    generate(X).

generate(X) :-
    swap([2,3,4,5], X).

print_final_grade(FinalGrade) :-
    write('Итоговая оценка: '),
    write(FinalGrade),
    nl.

print_grades(Grades) :-
    write('Оценки: '),
    write(Grades),
    nl.

check(X,G):- % проверка решения
    [F|_] = X, 
    last_two_elements(G,Result),
    [A,B] = Result,
    
    ((A=5,B=5, F=2);
    (A=4,B=4,F=3);
    (A=3,B=3,F=3);
    (A\=B, max(A,B,Max), F=Max)),
    
    append(G, [F], Gn),
    length(Gn,Len),
    ((Len =< 30,
        find_next(Gn));
    (
        Len = 30,
        average(Gn, Avg),
        round_integer(Avg, FinalGrade),
        print_final_grade(FinalGrade),
        print_grades(Gn)
    )).
    
% Определяет среднее арифметическое по всему списку.
average(List, Avg) :-
    sum_list(List, Sum),
    length(List, Len),
    Avg is Sum / Len.

% Округляет до ближайшего целого.
round_integer(X, Y) :-
    Y is round(X).

% Вычисляет итоговую оценку.
final_grade(Name) :-
    grade(Name, Grades),
    find_next(Grades).

main:-
    writeln("Aleksey"),final_grade(aleksey),nl,
    writeln("Leonid"),final_grade(leonid),nl,
    writeln("Aleksandr"),final_grade(aleksandr).

% Выполняет правило Goal N раз.
repeat(Goal,1):-Goal.
repeat(Goal,N):-
    not(not(Goal)), %стирание предыдущих подстановок
    M is N-1,repeat(Goal,M).
