#ifndef FILES_H_
#define FILES_H_ 1

size_t  file_saveData(FILE *f, t_data *d);
int     file_getData (FILE *f, t_data *d);

size_t file_saveData (FILE *f, t_data *d)
{
    return fwrite(d, sizeof(t_data), 1, f);
}

int file_getData (FILE *f, t_data *d)
{
    return fread(d, sizeof(t_data), 1, f);
}

#endif

