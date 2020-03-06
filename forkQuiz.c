#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{

  if (argc >= 2)
  {
    int cantidadHijos = *argv[1] - '0';
    pid_t pid;

    for (int i = cantidadHijos; i > 0; i--)
    {
      // printf("ciclo externo %d\n", i);
      printf("Proceso padre pid= %d\n", getpid());
      pid = fork();
      //pid = 0;
      if (pid < 0)
      {
        fprintf(stderr, "Fork falló");
      }
      else if (pid == 0) // código del hijo
      {
        pid_t pidNieto;
        printf("\tProceso hijo pid= %d ppid= %d\n", getpid(), getppid());
        for (int j = i; j > 0; j--)
        {
          // printf("\tciclo interno %d\n", j);

          pidNieto = fork();

          if (pidNieto < 0)
          {
            fprintf(stderr, "fork del hijo falló\n");
          }
          else if (pidNieto == 0)
          {
            printf("\t\tProceso nieto pid=%d ppid=%d \n", getpid(), getppid());
            //sleep(6);
            return 0;
          }
          else
          {
            waitpid(pidNieto, NULL, 0);
            // printf("\tTerminó nieto pid= %d\n", pidNieto);
          }
        }
        return 0;
      }
      else // código del padre
      {
        waitpid(pid, NULL, 0);
        // printf("Terminó hijo pid= %d\n", pid);
        // sleep(1);
      }
    }
  }
  else
  {
    printf("no se ingresó la cantidad de hijos\n");
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
