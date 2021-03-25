extern char **environ;

void environment(char *argv[])
{
   int i;
   for (i = 0; environ[i] != NULL; i++)
      printf("%s\n",environ[i]);
}

void echo(char *argv[])
{
    for (int i = 1; argv[i]; i++)              // print args
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
        printf("%s\n", cwd);
    }
}

void dir()
{
    char cmd[100];
    strcpy(cmd, "ls -al");
    system(cmd);
}

void pause_shell()
{
    printf("To continue, press enter.\n");
    while(getchar() != '\n');
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