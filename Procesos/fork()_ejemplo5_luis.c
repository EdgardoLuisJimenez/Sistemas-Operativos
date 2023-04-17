/*
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{

          P
         / \
        /   \
       /     \
      A       B
     / \     / \
    C   D   E   F
       /       / \
      G       H   I
     / \         /
    J   K       L


  pid_t root = getpid();

  // Proceso P
  for (int i = 0; i < 2; i++)
  {
    if (fork() == 0)
    {
      // Proceso A
      if (i == 0)
      {
        for (int i = 0; i < 2; i++)
        {
          // Proceso C - D
          if (fork() == 0)
          {
            // Proceso D
            if (i == 1)
            {
              wait(NULL);
              printf("Soy proceso D - Mi PID:%d - Mi padre:%d\n", getpid(), getppid());
              // Proceso G
              if (fork() == 0)
              {
                for (int i = 0; i < 2; i++)
                {
                  // Proceso J - K
                  if (fork() == 0)
                  {
                    if (i == 0)
                    {
                      printf("Soy proceso J - Mi PID:%d - Mi padre:%d\n", getpid(), getppid());
                    }
                    else
                    {
                      printf("Soy proceso K - Mi PID:%d - Mi padre:%d\n", getpid(), getppid());
                    }
                    break;
                  }
                }
              }
              else
              {
                for (int i = 0; i < 2; i++)
                {
                  wait(NULL);
                  printf("Soy proceso G - Mi PID:%d - Mi padre:%d\n", getpid(), getppid());
                }
              }
            }
            printf("Soy proceso C - Mi PID:%d - Mi Padre:%d\n", getpid(), getppid());
            break;
          }
          else
          {
            wait(NULL);
            printf("Soy proceso A - Mi PID:%d - Mi padre:%d\n", getpid(), getppid());
          }
        }
      }
      // Proceso B
      else
      {
        // Proceso E - F
        for (int i = 0; i < 2; i++)
        {
          if (fork() == 0)
          {
            // Proceso F
            if (i == 1)
            {
              // Proceso H - I
              for (int i = 0; i < 2; i++)
              {
                if (fork() == 0)
                {
                  if (i == 1)
                  {
                    if (fork() == 0)
                    {
                      printf("Soy proceso L - Mi PID:%d - Mi Padre:%d\n", getpid(), getppid());
                    }
                    else
                    {
                      wait(NULL);
                      printf("Soy proceso I - Mi PID:%d - Mi Padre:%d\n", getpid(), getppid());
                    }
                  }
                  break;
                }
              }
              for (int i = 0; i < 2; i++)
              {
                wait(NULL);
                printf("Soy proceso F - Mi PID:%d - Mi padre:%d\n", getpid(), getppid());
              }
            }
            break;
          }
          else
          {
            wait(NULL);
            printf("Soy proceso B - Mi PID:%d - Mi padre:%d\n", getpid(), getppid());
          }
        }
      }
      break;
    }
  }

  if (getpid() == root)
  {
    for (int i = 0; i < 2; i++)
    {
      wait(NULL);
      printf("Soy proceso P - Mi PID:%d - Mi padre:%d\n", getpid(), getppid());
    }
  }

  return EXIT_SUCCESS;
}
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{

  /*
          P
         / \
        /   \
       /     \
      A       B
     / \     / \
    C   D   E   F
       /       / \
      G       H   I
     / \         /
    J   K       L
  */

  pid_t root = getpid();

  for (int i = 0; i < 2; i++)
  {
    if (fork() == 0)
    {
      // Proceso A
      if (i == 0)
      {
        for (int i = 0; i < 2; i++)
        {
          if (fork() == 0)
          {
            if (i == 0)
            {
              printf("Soy proceso C - Pid:%d - Mi Padre:%d\n", getpid(), getppid());
            }
            else
            {
              if (fork() == 0)
              {
                for (int i = 0; i < 2; i++)
                {
                  if (fork() == 0)
                  {
                    if (i == 0)
                    {
                      printf("Soy proceso J - Pid:%d - Mi Padre:%d\n", getpid(), getppid());
                    }
                    else
                    {
                      printf("Soy proceso K - Pid:%d - Mi Padre:%d\n", getpid(), getppid());
                    }
                    break;
                  }
                  else
                  {
                    wait(NULL);
                    printf("Soy proceso G - Pid:%d - Mi Padre:%d\n", getpid(), getppid());
                  }
                }
                break;
              }
              wait(NULL);
              printf("Soy proceso D - Pid:%d - Mi Padre:%d\n", getpid(), getppid());
            }
            break;
          }
          else
          {
            wait(NULL);
            printf("Soy proceso A - Mi PID:%d - Mi padre:%d\n", getpid(), getppid());
          }
        }
      }
      // Proceso B
      if (i == 1)
      {
        for (int i = 0; i < 2; i++)
        {
          if (fork() == 0)
          {
            if (i == 0)
            {
              printf("Soy proceso E - Mi PID:%d - Mi padre:%d\n", getpid(), getppid());
            }
            else
            {
              for (int i = 0; i < 2; i++)
              {
                if (fork() == 0)
                {
                  if (i == 0)
                  {
                    printf("Soy proceso H - Mi PID:%d - Mi padre:%d\n", getpid(), getppid());
                  }
                  else
                  {
                    if (fork() == 0)
                    {
                      printf("Soy proceso L - Mi PID:%d - Mi padre:%d\n", getpid(), getppid());
                      break;
                    }
                    else
                    {
                      wait(NULL);
                      printf("Soy proceso I - Mi PID:%d - Mi padre:%d\n", getpid(), getppid());
                    }
                  }
                  break;
                }
                else
                {
                  wait(NULL);
                  printf("Soy proceso F - Mi PID:%d - Mi padre:%d\n", getpid(), getppid());
                }
              }
            }
            break;
          }
          else
          {
            wait(NULL);
            printf("Soy proceso B - Mi PID:%d - Mi padre:%d\n", getpid(), getppid());
          }
        }
      }
      break;
    }
    else
    {
      wait(NULL);
      printf("Soy proceso P - Mi PID:%d - Mi padre:%d\n", getpid(), getppid());
    }
  }

  return EXIT_SUCCESS;
}