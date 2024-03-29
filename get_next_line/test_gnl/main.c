#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int main()
{
	int fd = open("test.txt", O_RDONLY);
	int fd = 42;
	char *a;
	while ((a = get_next_line(fd)))
	{
		printf("%s", a);
		free (a);
		a = NULL;
	}
	return (0);
}
