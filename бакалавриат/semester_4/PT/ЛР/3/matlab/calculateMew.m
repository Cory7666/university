function ret = calculateMew (array, k)
    M = calculateMathExpect(array);
    t = array;
    t = (array - M) .^ k;
    ret = sum(t);
end
