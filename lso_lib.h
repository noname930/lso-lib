#ifndef lso_lib_h
#define lso_lib_h

/*Crea il file con il nome "nomefile" e ci scrive dentro la stringa*/
void writeonfile(char *stringa,int fd);

/*apre il file con nome messo in input, type indica con 1 se lo vuoi creare e 0 viceversa, R_or_W indica con 0 se
lo vuoi aprire in lettura e 1 se lo vuoi aprire in scrittura*/
int aperturafile(char *nomefile, int type, int R_or_W);

/*legge il file*/
void readonfile (int fd);

/*legge il file secondo i parametri buff e offset_incremetation.
1)buff indica quanti caratteri alla volta deve leggere
2)offset_incremetation indica ad ogni lettura di quanto deve incrementare l'offset, o decrementare ( a seconda della direzione della lettura)
3) 0 per leggere da sx a dx, 1 per leggere da dx a sx */
void readonfile_with_offset(int fd, int buff, int offset_incremetation,int direction);

/*copia il file1 all'interno del file2*/
void copiafile(int fd1, int fd2);


#endif
