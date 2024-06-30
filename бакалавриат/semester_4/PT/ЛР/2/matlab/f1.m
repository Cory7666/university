function out = f1(interval_start, interval_end, origin_matrix)
    out = zeros (1, length(origin_matrix));
    for i = 1:length(origin_matrix)
        if ((interval_start <= origin_matrix(i)) && (origin_matrix(i) <= interval_end))
            out(i) = 1;
        end;
    end;
end

