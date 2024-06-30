:- dynamic transaction/3.

transaction(9999, 8888, 900).
transaction(9999, 7777, 800).
transaction(9999, 5555, 500).
transaction(5555, 9999, 900).
transaction(5555, 1111, 100).
transaction(1111, 2222, 200).

update_transaction :-
    read(MyNum),
    retract(transaction(MyNum, _, _)),
    read(NewOtherNum),
    read(NewValue),
    asserta(transaction(MyNum, NewOtherNum, NewValue));
    write('No transaction with this my nums.'),
    nl, fail.

print_schet :-
    read(MyNum),
    transaction(MyNum, OtherNum, Value),
    display(MyNum), write(' | '),
    display(OtherNum), write(' | '),
    display(Value), nl;
    write('Empty.'),
    nl, fail.

print_all :-
    listing.