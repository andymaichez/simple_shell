#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_CMD_LENGTH 100
#define MAX_ARGS 10
void print_prompt(void)
{
char prompt[] = "Shell> ";
write(1, prompt, sizeof(prompt) - 1);
}
int main(void)
{
char cmd[MAX_CMD_LENGTH];
char *args[MAX_ARGS];
char *token;
int arg_count = 0;
int status;
while (1)
{
print_prompt();
if (read(0, cmd, sizeof(cmd)) == 0)
{
write(1, "\n", 1);
break;
}
cmd[strcspn(cmd, "\n")] = '\0';
int arg_count = 0;
token = strtok(cmd, " ");
while (token != NULL && arg_count < MAX_ARGS - 1)
{
args[arg_count] = token;
token = strtok(NULL, " ");
arg_count++;
}
args[arg_count] = NULL;
if (strcmp(args[0], "env") == 0)
{
char **env = environ;
while (*env != NULL)
{
write(1, *env, strlen(*env));
write(1, "\n", 1);
env++;
}
}
pid_t pid;
else
{
pid_t pid = fork();
if (pid == 0)
execvp(args[0], args);
char error_msg[] = "Command execution failed\n";
write(2, error_msg, sizeof(error_msg) - 1);
exit(EXIT_FAILURE);
}
else if
(pid > 0)
{
waitpid(pid, &status, 0);
}
else
{
char error_msg[] = "Fork failed\n";
write(2, error_msg, sizeof(error_msg) - 1);
}
}
}
{
return (0);
}
}

