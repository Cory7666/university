info:-
    nl,
    write('***************************************'),nl,
    write('* Экспертная система по теме           *'),nl,
    write('* Компьютерные игры.                   *'),nl,
    write('*------------------------------------- *'),nl,
    write('* Ожидаемый ввод: да, нет, почему      *'),nl,
    write('* Для объяснения решения введите цель. *'),nl,
    write('****************************************'), nl ,
    write('Тыкните на любую кнопку'),
    nl,
    get0(_).

% тестовая база продукционных правил
rule1 :: if monster(near) and have(place_to_hide) then hide(in_closet).
rule2 :: if monster(near) and no(place_to_hide) then run(away).
rule3 :: if monster(near) and have(ammo) then shoot(the_monster).
rule4 :: if low(hp) and have(place_to_loot) then find(medecine).
rule5 :: if door(locked) and have(key) then unlock(the_door).
rule6 :: if door(locked) and have_not(key) then find(key).
rule7 :: if your_name(daniel)
    and place(castle_brenenburg)
    and have(amnesia)
    then you_must(destroy_spehere).

% гипотезы (цели)
h1 :: hypothesis(run(away)).
h2 :: hypothesis(hide(in_closet)).
h3 :: hypothesis(shoot(the_monster)).
h4 :: hypothesis(find(medecine)).
h5 :: hypothesis(unlock(the_door)).
h6 :: hypothesis(find(key)).
h7 :: hypothesis(you_must(destroy_spehere)).

% признаки, истинность которых можно выяснить у пользователя
q1 :: sign(monster(near)).
q2 :: sign(door(locked)).
q3 :: sign(have(key)).
q4 :: sign(have(place_to_hide)).
q5 :: sign(have(ammo)).
q6 :: sign(low(hp)).
q7 :: sign(have(place_to_loot)).
q8 :: sign(no(place_to_hide)).
q9 :: sign(your_name(daniel)).
q10 :: sign(place(castle_brenenburg)).
q11 :: sign(have_not(key)).
q12 :: sign(have(amnesia)).
