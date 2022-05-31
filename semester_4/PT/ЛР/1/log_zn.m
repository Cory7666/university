function out = log_zn (am, aM, x)
    if (( am <= x ) && ( x < aM ))
        out = 1;
    else
        out = 0;
    end;