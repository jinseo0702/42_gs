/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinseo <jinseo@student.42gyeongsan.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 21:36:12 by jinseo            #+#    #+#             */
/*   Updated: 2024/03/27 20:40:25 by jinseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_get_head(char **backup, ssize_t re_frf)
{
	char	*gnl;
	int		i;

	i = ft_new_line(*backup, re_frf);
	if (i == 1 && *backup[0] == '\n')
		i -= 1;
	else if (i == 1 && re_frf == 0 && *backup[0] != '\n')
		i -= 1;
	gnl = ft_gnl_strdup(backup, i + 1);
	*backup = ft_gnl_substr(backup, i + 1);
	if (**backup == 0)
		free_backup(backup);
	return (gnl);
}

ssize_t	ft_new_line(const char *str, ssize_t read_len)
{
	ssize_t	len;

	len = 0;
	if (str[len] == '\n')
		return (1);
	if (*str && read_len != 0)
		return (0);
	while (str[len] != '\n')
	{
		if (str[len] == '\0' && read_len != 0)
			return (0);
		else if (str[len] == '\0' && read_len == 0)
			return (len);
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
		read_len = ft_read_sub(fd, buf);
		*backup = ft_gnl_strdup(&buf, ft_gnl_strlen(buf));
		if (read_len <= 0 && **backup == 0)
		{
			free_backup(&buf);
			return (read_len);
		}
	}
	while (!ft_new_line(*backup, read_len))
	{
		read_len = ft_read_sub(fd, buf);
		*backup = ft_gnl_strjoin(backup, buf);
	}
	free_backup(&buf);
	return (read_len);
}

ssize_t	ft_read_sub(int fd, char *buf)
{
	ssize_t	read_len_sub;
	ssize_t	i;

	i = -1;
	read_len_sub = 0;
	while (++i < BUFFER_SIZE + 1)
		buf[i] = 0;
	read_len_sub = read(fd, buf, BUFFER_SIZE);
	return (read_len_sub);
}

char	*get_next_line(int fd)
{
	static char	*backup[1024];
	char		*gnl;
	ssize_t		re_frf;

	re_frf = 0;
	if ((fd < 0 || fd > 1023) || BUFFER_SIZE <= 0)
		return (NULL);
	re_frf = ft_read_file(fd, &backup[fd]);
	if (read(fd, backup[fd], 0) == -1)
	{
		free_backup(&backup[fd]);
		return (NULL);
	}
	if (re_frf <= 0 && *backup[fd] == 0)
	{
		free_backup(&backup[fd]);
		return (NULL);
	}
	gnl = ft_get_head(&backup[fd], re_frf);
	return (gnl);
}