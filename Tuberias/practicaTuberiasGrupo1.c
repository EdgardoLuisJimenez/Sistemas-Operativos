#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
  FILE *file;
  int i, n;
  char contenido[1000] = "";
  char linea[1000] = "";

  int tubs[2][2];
  for (i = 0; i < 2; i++)
    pipe(tubs[i]);

  pid_t root = getpid();

  for (i = 0; i < 2; i++)
  {
    if (fork() == 0)
      break;
  }

  if (getpid() == root)
  {
    close(tubs[0][1]);
    close(tubs[1][1]);

    printf("Padre esperando a que los hijos escriban...\n");
    for (int j = 0; j < 2; j++)
    {
      n = read(tubs[j][0], linea, 1000);
      linea[n] = '\n';
      linea[n + 1] = '\0';
      strcat(contenido, linea);
    }

    printf("Texto recibido por el padre: \n%s", contenido);

    for (int j = 0; j < 2; j++)
    {
      wait(NULL);
    }
  }
  else
  {
    if (i == 0)
    {
      close(tubs[0][0]);
      close(tubs[1][0]);
      close(tubs[1][1]);

      file = fopen(argv[1], "r");

      if (file == NULL)
      {
        perror("Error al abrir el archivo");
        exit(1);
      }

      while (fgets(linea, sizeof(linea), file) != NULL)
      {
        strcat(contenido, linea);
      }

      // printf("Contenido del archivo 1: \n%s", contenido);
      contenido[strlen(contenido) - 1] = '\0';

      write(tubs[0][1], contenido, strlen(contenido));

      fclose(file);
      close(tubs[0][1]);
    }
    else if (i == 1)
    {
      close(tubs[0][0]);
      close(tubs[0][1]);
      close(tubs[1][0]);

      file = fopen(argv[2], "r");

      if (file == NULL)
      {
        perror("Error al abrir el archivo");
        exit(1);
      }

      while (fgets(linea, sizeof(linea), file) != NULL)
      {
        strcat(contenido, linea);
      }

      // printf("Contenido del archivo 2: \n%s", contenido);
      contenido[strlen(contenido) - 1] = '\0';

      write(tubs[1][1], contenido, strlen(contenido));

      fclose(file);
      close(tubs[1][1]);
    }
  }
  return EXIT_SUCCESS;
}