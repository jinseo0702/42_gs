/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinseo <jinseo@student.42gyeongsan.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 21:36:12 by jinseo            #+#    #+#             */
/*   Updated: 2024/03/23 02:00:24 by jinseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_get_head(char **backup)
{
	char	*gnl;
	int		i;

	i = ft_new_line(*backup);
	if (i == 1 && *backup[0] == '\n')
		i -= 1;
	gnl = ft_gnl_strdup(backup, i + 1);
	*backup = ft_gnl_substr(backup, i + 1);
	if (**backup == 0)
		free_backup(backup);
	return (gnl);
}

size_t	ft_new_line(const char *str)
{
	size_t	len;

	len = 0;
	if (str[len] == '\n')
		return (1);
	while (str[len] != '\n')
	{
		if (str[len] == '\0')
			return (0);
		len++;
	}
	return (len);
}

ssize_t	ft_read_file(int fd, char **backup)
{
	char	*buf;
	ssize_t	read_len;

	read_len = 0;
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (0);
	if (*backup == NULL)
	{
		read_len = read(fd, buf, BUFFER_SIZE);
		buf[read_len] = '\0';
		*backup = ft_gnl_strdup(&buf, ft_gnl_strlen(buf));
		if (read_len <= 0 && **backup == 0)
		{
			free_backup(&buf);
			return (read_len);
		}
	}
	while (!ft_new_line(*backup))
	{
		read_len = read(fd, buf, BUFFER_SIZE);
		buf[read_len] = '\0';
		*backup = ft_gnl_strjoin(backup, buf);
	}
	free_backup(&buf);
	return (read_len);
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*gnl;
	ssize_t		re_frf;

	re_frf = 0;
	if ((fd < 0 && fd > 1023) || BUFFER_SIZE <= 0)
		return (NULL);
	re_frf = ft_read_file(fd, &backup);
	if (re_frf <= 0 && *backup == 0)
	{
		free_backup(&backup);
		return (NULL);
	}
	gnl = ft_get_head(&backup);
	return (gnl);
}
