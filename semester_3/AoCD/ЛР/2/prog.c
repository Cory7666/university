#include <stdio.h>

int main ()
{
    int hash_table[] = {90, 52, 96, 53, 0, 0},
        in_arr[] = {90, 55, 56, 96, 96, 0},
        out_arr[] = {0, 0, 0, 0, 0};
    
    int *counter_hash = hash_table,
        *counter_in_arr = in_arr,
        *counter_out_arr = out_arr;
    int tmp = 0;
    
    A:
        tmp = *counter_in_arr;
        counter_hash = hash_table;
        B:
            if ((*counter_hash) != (*counter_in_arr)) goto C;
            counter_hash++;
            tmp = *counter_hash;
            goto D;
            C: counter_hash++;
            D: counter_hash++;
        if (*counter_hash != 0) goto B;
        *counter_out_arr = tmp;
        counter_in_arr++;
        counter_out_arr++;
    if (*counter_in_arr != 0) goto A;

    printf("arr = [%d, %d, %d, %d, %d]\r\n", out_arr[0], out_arr[1], out_arr[2], out_arr[3], out_arr[4]); // 52, 55, 56, 53, 53

    return 0;
}

/*#include <stdio.h>

int main ()
{   
    // Hello, world! Or new user... I dont know, I'm the computer btw...
    char str[] = "AaBbCcDdEeFf!.?.,.{([(})])";

    char *str_tmp = str;
    while (*str_tmp)
        {printf("%X (%c) -> %X (%c)\r\n", (int) *(str_tmp), (int) *(str_tmp), (int) *(str_tmp + 1), (int) *(str_tmp + 1)); (str_tmp += 2);}

    return 0;
}*/