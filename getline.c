#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

ssize_t custom_getline(char **lineptr, size_t *n)
{
static char buffer[BUFFER_SIZE];
static size_t buffer_pos = 0;
static ssize_t buffer_size = 0;

if (buffer_pos >= buffer_size)
{
buffer_size = read(STDIN_FILENO, buffer, BUFFER_SIZE);
buffer_pos = 0;
if (buffer_size <= 0)
{
return buffer_size;
}
}
size_t i;
for (i = buffer_pos; i < buffer_size; i++) {
if (buffer[i] == '\n')
{
break;
}
}
size_t line_length = i – buffer_pos;

if (*n < line_length + 1) {
*n = line_length + 1;
*lineptr = realloc(*lineptr, *n);
if (*lineptr == NULL)
{
perror("realloc");
return (-1);
}
}
for (i = buffer_pos; i < buffer_size; i++)
{
(*lineptr)[i - buffer_pos] = buffer[i];
if (buffer[i] == '\n') {
(*lineptr)[i - buffer_pos + 1] = '\0';
buffer_pos = i + 1;
return (i - buffer_pos + 1);
}
}
ssize_t read_bytes = custom_getline(lineptr, n);
if (read_bytes <= 0) {
return read_bytes;
}
buffer_pos += line_length;
line_length += read_bytes;
if (*n < line_length + 1)
{
*n = line_length + 1;
*lineptr = realloc(*lineptr, *n);
if (*lineptr == NULL)
{
perror("realloc");
return (-1);
}
}
for (i = buffer_pos; i < buffer_pos + read_bytes; i++)
{
(*lineptr)[i - buffer_pos] = buffer[i];
if (buffer[i] == '\n') {
(*lineptr)[i - buffer_pos + 1] = '\0';
buffer_pos = i + 1;
return i - buffer_pos + 1;
}
}
return line_length;
}
int main(void)
{
char *input = NULL;
size_t input_size = 0;
while (1)
{
printf("Shell> ");
ssize_t bytes_read = custom_getline(&input, &input_size);
if (bytes_read <= 0)
{
break;
}
printf("You entered: %s", input);
}
free(input);
return (0);
}
