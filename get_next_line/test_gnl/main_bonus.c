#include <stdio.h>
#include <fcntl.h>
#include "get_next_line_bonus.h"

int main()
{
	int fd1 = open("test.txt", O_RDONLY);
	char *a;
	int fd2 = open("test2.txt", O_RDONLY);
	char *b;
	int fd3 = open("test3.txt", O_RDONLY);
	char *c;
	a = get_next_line(fd1);
	b = get_next_line(fd2);
	c = get_next_line(fd3);
	while (a || b || c)
	{
		if (a != 0)
			printf("%s\n", a);
		if (b != 0)
			printf("%s\n", b);
		if (c != 0)
			printf("%s\n", c);
		if (!a)
			free(a);
		if (!b)
			free(b);
		if (!c)
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
