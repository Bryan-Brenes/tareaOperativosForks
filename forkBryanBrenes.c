#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
  pid_t pid;
  pid = fork();
  pid = fork();
  pid = fork();
  // esto no esta bien, después de cada fork tiene que estar el bloque del if para poder controlar que hace cada hijo
  if (pid < 0)
  {
    fprintf(stderr, "Fork falló");
  }
  else if (pid == 0)
  {
    // execlp("/bin/ls", "ls", NULL);
    printf("Proceso hijo pid=%d ppid=%d \n", getpid(), getppid());
    sleep(5);
    printf("Terminé!! (hijo)\n");
  }
  else
  {
    // ppid es el proceso padre, pid es el id del proceso actual
    printf("Proceso padre pid=%d ppid=%d \n", getpid(), getppid());
    //wait(NULL); // espera al último hijo creado, o puede esperar a uno en específico dándoselo como parámetro
    waitpid(pid, NULL, 0); // espera por el proceso hijo que yo le asigne
    sleep(2);
    printf("child %d completed\n", pid);
  }
  return 0;
}

/*
Enviar a danny
el padre recibe la cantidad de hijos que va a tener
y cada hijo va a tener n -1 hijos, si son 10, el primero 10 y el último 1 proceso
con pstree se puede ver los hijos

capturas de pantalla con pruebas, 2 o tres ejemplos y envíar el código
el hijo tiene que decir el numero del hijo el número del nieto
*/
