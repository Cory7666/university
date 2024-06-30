a = 0;
b = 1.5;
h = 0.15;

x = [a:h:b];
f = (2 .* exp(-x)) / (2 * pi + x.^3);

plot (x, f);