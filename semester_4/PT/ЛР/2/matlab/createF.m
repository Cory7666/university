function out = createF(A, B, C)
    out = zeros(1,length(A));
    for i = 1:length(A)
        if (B(i) == 0) || (B(i) == 1 && C(i) == 1)
            out(i) = 1;
        end;
    end;
end

