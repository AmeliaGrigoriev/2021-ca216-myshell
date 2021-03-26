/*
Student Name: Amelia Grigoriev
Student Number: 19348241
In submitting this project, I declare that the project material, which I now submit, is my own work. Any assistance received by way of borrowing from the work of others has been cited and acknowledged within the work. I make this declaration in the knowledge that a breach of the rules pertaining to project submission may carry serious consequences.
*/

#include <limits.h>
#include <string.h>

extern char **environ;

void environment(char *argv[])
{
   int i;
   for (i = 0; environ[i] != NULL; i++)
      printf("%s\n",environ[i]);
}

void shell_environment(void)
{
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    setenv("SHELL", strcat(cwd, "/myshell"), 1);
}

void echo(char *argv[])
{
    for (int i = 1; argv[i]; i++)
        printf("%s ", argv[i]);
    printf("\n");
}

void cd(char *argv[])
{
    char cwd[100];
    getcwd(cwd, sizeof(cwd));

    if(argv[1] == NULL)
    {
        printf("%s\n", cwd);
    }
    else
    {
        chdir(argv[1]);
        getcwd(cwd, sizeof(cwd));
        setenv("PWD", cwd, 1);
    }
}

void dir() // used https://www.tutorialspoint.com/c-program-to-list-all-files-and-sub-directories-in-a-directory
{
    struct dirent *files;
    DIR *dir = opendir(".");
    if (dir == NULL){
        printf("no such file or directory" );
    }

    while ((files = readdir(dir)) != NULL)
    printf("%s\n", files->d_name);
    closedir(dir);
}

void pause_shell()
{
    printf("To continue, press enter.\n");
    while(getchar() != '\n');
}

void pwd(char *argv[])
{
    char cwd[100];
    getcwd(cwd, sizeof(cwd));
    printf("%s\n", cwd);
}

int ext_commands(char **args)
{
  pid_t pid, wpid;
  int status;

  pid = fork();
  if (pid == 0) {
    // Child process
    if (execvp(args[0], args) == -1) {
      perror("myshell");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    // Error forking
    perror("myshell");
  } else {
    // Parent process
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}