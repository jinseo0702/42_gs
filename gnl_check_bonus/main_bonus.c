#include <stdio.h>
#include <fcntl.h>
#include "get_next_line_bonus.h"

int main(void)
{
	int fd1 = open("get_next_line.c", O_RDONLY);
	char *a;
	int fd2 = open("get_next_line.c", O_RDONLY);
	char *b;
	int fd3 = open("get_next_line.c", O_RDONLY);
	char *c;
	a = get_next_line(fd1);
	b = get_next_line(fd2);
	c = get_next_line(fd3);
	while (a || b || c)
	{
		if (a != 0)
			printf("%s", a);
		if (b != 0)
			printf("%s", b);
		if (c != 0)
			printf("%s", c);
		if (a)
			free(a);
		if (b)
			free(b);
		if (c)
			free(c);
		a = get_next_line(fd1);
		b = get_next_line(fd2);
		c = get_next_line(fd3);
	}
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}
