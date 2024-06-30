student(1, 'Math', 200, 2, 5).
student(3, 'Physics', 172, 3, 4).
student(6, 'Native Language', 80, 1, 5).
student(2, 'Biology', 36, 4, 3).
student(1, 'Math', 200, 2, 3).
student(1, 'Math', 200, 2, 5).
student(5, 'German Language', 220, 2, 4).
student(10, 'Spain Language', 220, 2, 2).

has_in_range_72_and_180 :-
    student(_, _, Hours, _, _),
    (Hours >= 72),
    (Hours =< 180), !.

has_not_in_range_72_and_180 :-
    student(_, _, Hours, _, _),
    ((Hours =< 72); (Hours >= 180)),
    !.

has_discipline_with_equal_id_and_length :-
    student(Id, _, _, Length, _),
    Id =:= Length,
    !.

print_disciplines_with_mark(UserMark) :-
    student(_, Discipline, _, _, UserMark),
    display(Discipline).

print_disciplines_with_mark_interactive :-
    read(UserMark),
    print_disciplines_with_mark(UserMark).

has_disciplines_with_equal_length_and_hours :-
    student(_, Discipline1, Hours, Length, _),
    student(_, Discipline2, Hours, Length, _),
    Discipline1 \= Discipline2,
    display(Discipline1),
    display(Discipline2), !.