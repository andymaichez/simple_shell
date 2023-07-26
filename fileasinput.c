#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024

void execute_command(const char *command)
{
char *args[2];
int status;
pid_t pid = fork();
if (pid < 0)
{
perror("fork");
exit(EXIT_FAILURE);
}
else if
(pid == 0)
{
args[0] = strdup(command);
args[1] = NULL;
execvp(args[0], args);
perror("execvp");
exit(EXIT_FAILURE);
}
else
{
waitpid(pid, &status, 0);
}
}
/*
 * main - introduces the entry point of the shell program.
 * @return 0 on success and non zero on failure.
 */
int main(int argc, char *argv[])
{
if (argc == 2)
{
FILE *file = fopen(argv[1], "r");
if (file == NULL)
{
perror("File not found");
exit(EXIT_FAILURE);
}
char command[MAX_COMMAND_LENGTH];
while
(fgets(command, MAX_COMMAND_LENGTH, file) != NULL)
{
command[strcspn(command, "\n")] = '\0';
execute_command(command);
}
fclose(file);
}
else
{
while (1)
{
printf("simple_shell$ ");
char command[MAX_COMMAND_LENGTH];
if
(fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
{
printf("\n");
break;
}
command[strcspn(command, "\n")] = '\0';
execute_command(command);
}
}
return (0);
}
