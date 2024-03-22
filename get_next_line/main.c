#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main()
{
	static char	*read_str;
	int fd = open("./test.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("files not open");
		return (-1);
	}
	else
	{
		read_str = get_next_line(fd);
		while(read_str != NULL)
		{
			printf("%s",read_str);
			free(read_str);
			read_str = get_next_line(fd);
		}
	}
	return (0);
}
