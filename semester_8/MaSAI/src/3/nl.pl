info:-
nl,
write('*******************************'),nl,
write('* Expert system *'),nl,
write('* for troubleshooting *'),nl,
write('*---------------------------- *'),nl,
write('* Answer questions: *'),nl,
write('* yes, no, why *'),nl,
write('* To explain the solution *'),nl,
write('* enter a goal *'),nl,
write('*******************************'), nl ,
write('Write any key'),nl, %Ожидание ввода литеры
get0(_).
% тестовая база продукционных правил для диагностики электрической плиты
rule1 :: if display(blink) and gpu(mined)
then gpu(otval).
rule2 :: if speaker(not_beep) and display(off) and cpu(cold)
then bp(off).
rule3 :: if cpu(hot)
then cpu_fan(off).
rule4 :: if time(resets)
then cmos_battery(discharged).
rule5 :: if display(none) and speaker(beep_often) and ram(on)
then ram(broken).
rule6 :: if display(none) and speaker(beep_often)
then ram(off).
rule7 :: if display(none) and cpu_fan(on) and speaker(beep)
then display(broken).
% гипотезы неисправности (цели)
h1 :: hypothesis(ram(off)).
h2 :: hypothesis(cpu_fan(off)).
h3 :: hypothesis(bp(off)).
h4 :: hypothesis(cmos_battery(discharged)).
h5 :: hypothesis(ram(broken)).
h6 :: hypothesis(gpu(otval)).
h7 :: hypothesis(display(broken)).
% признаки, истинность которых можно выяснить у пользователя
q1 :: sign(cpu_fan(on)).
q2 :: sign(cpu(cold)).
q3 :: sign(bp(on)).
q4 :: sign(cpu(hot)).
q5 :: sign(display(blink)).
q6 :: sign(speaker(beep)).
q7 :: sign(speaker(not_beep)).
q8 :: sign(ram(on)).
q9 :: sign(speaker(beep_often)).
q10 :: sign(display(off)).
q11 :: sign(time(resets)).
q12 :: sign(gpu(mined)).