function out = fregp (m)
    t = 0;
    out = zeros(1, length(m));
    for i = 1:length(m)
        t = t + m(i);
        out(i) = t / i;
    end;
    