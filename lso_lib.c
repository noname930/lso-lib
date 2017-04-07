#include <sys/types.h> /*open*/
#include <sys/stat.h>
#include <fcntl.h> /*open*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h> /*perror*/
#include "lso_lib.h"
#define BUFFDIM 1000

/*==========================APERTURA DEL FILE=====================*/
int aperturafile(char *nomefile,int type, int R_or_W)
{

  int fd;

  // voglio aprire in lettura un file senza crearlo
  if(type==0 && R_or_W == 0) fd=open(nomefile, O_RDONLY);

  //voglio aprire un file in lettura creandolo
  else if(type == 1 && R_or_W==0) fd=open(nomefile,O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR );

  //voglio aprire un file in scrittura senza crearlo
  else if(type == 0 && R_or_W==1) fd=open(nomefile, O_WRONLY, S_IRUSR | S_IWUSR );

  //voglio aprire un file in scrittura creandolo
  else fd=open(nomefile, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);


  if(fd == -1)
  {
    perror("\nErrore nell'apertura del File");
    exit(-1);
  }
  else printf("\nApertura del File eseguita.\n");

  return fd;

}



/*==========================SCRITTURA SU FILE================================*/
void writeonfile(char *stringa,int fd)
{
  int nwrite;

   if (fd == 0)
   {
     perror("\nFile non aperto!\n");
     exit(-1);
   }

   nwrite=write(fd,stringa,strlen(stringa));

   if(nwrite == -1)
   {
     perror("\nErrore in Scrittura\n");
     exit(-1);
   }
   else printf("\nScrittura nel File eseguita\n");


}




/*==========================LETTURA SU FILE================================*/
void readonfile (int fd)
{
 int nread;
 char buffer[BUFFDIM];

 if (fd == 0) {
   perror("\nFile non aperto.");
 }

 printf("\nInizio la stampa\n\n\n");

while((nread=read(fd,buffer,BUFFDIM)) > 0)
 {
     if ( write(STDOUT_FILENO,buffer, nread) == -1) {
        exit(1);
     }


 }

  printf("\n\nFine Stampa la stampa\n\n\n");


}


/*=================LETTURA DEL FILE CON MODELLIZZAZIONI SULL'OFFSET==========*/

void readonfile_with_offset(int fd,int buff, int offset_incremetation, int direction)
{
  int nread;
  char buffer[BUFFDIM];
  int i;

  if (fd == 0)
   {
    perror("\nFile non aperto.");
  }


  if (direction == 0) {
    i=0;
  }
  else
  {
    if(lseek(fd,0,SEEK_END)== -1)  // se la direzione della lettura è al contrario, metto il cursore alla fine della stringa
    {
      perror("\nErrore Offset");
      close(fd);
      exit(1);
    }

    i=lseek(fd,0,SEEK_CUR);
    i=i-1;

    if(lseek(fd,i,SEEK_SET)== -1) // dico che l'offset corrente è appunto l'ultima lettera
    {                                // e se è minore di 1 faccio uscire il programma
      perror("\nErrore di offset\n");
      close(fd);
      exit(-1);
    }

  }

  printf("\nInizio la stampa\n\n\n");
      //nread=read(fd,buffer,buff);
      //printf("nread= %d\n", nread);


 while((nread=read(fd,buffer,buff)) > 0) // leggo n caratteri alla volta, e n è uguale al valore inserito da buff
  {
      if ( write(STDOUT_FILENO,buffer, nread) == -1) {
         perror("\nErrore LETTURA\n");
         exit(1);
      }



    if(direction==0)
     {
       i=i+offset_incremetation; // incremento i con il valore di offset in modo da spostarmi sulla stringa di offset_incremetation posti

            if (lseek(fd,i,SEEK_SET) == -1)       // la funz. lseek SETTA l'offset alla posizione i, e restituisce il nuovo offset. Se questo
            {                                     // è oltre al end of file, ritorna -1.
             perror("\nErrore sull'Offset\n");
              exit(1);
              close(fd);
            }
     }
   else    // se invece la direzione della lettura è 0 quindi da destra  verso sinistra
   {

         i=i-offset_incremetation;  // decremento il valore del cursore di tanto quanto è offset incre.

         if(i>=0)
         {
              if(lseek(fd,i,SEEK_SET) == -1 )     // la i avrà il valore del offset corrente decrementato di uno in modo da procedere da dx a sx
              {
                  perror("\nErrore Offset\n");
                  close(fd);
                  exit(-1);
              }

         }
         else
           close(fd);


      }
   } /*fine ciclo*/

   printf("\n\nFine Stampa la stampa\n\n\n");


}


/*=================================COPIA FILE1 IN FILE2=======================*/
void copiafile(int fd1, int fd2)
{
  char buffer[BUFFDIM];
  int nread;

  while((nread=read(fd1,buffer,BUFFDIM)) > 0) // legge nel file fd1 e salva nel buffer
  {
    if(write(fd2,buffer,nread) == -1)  // scrive il buffer nel file fd2
    {
      //perror("\nFile Sorgente Vuoto\n");
      close(fd1);
      close(fd2);
      exit(1);
    }

    close(fd1);
    close(fd2);

  }




}
