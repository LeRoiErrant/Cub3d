/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:28:21 by 0xNino            #+#    #+#             */
/*   Updated: 2022/02/11 15:42:24 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 100
#endif

char	*get_next_line(int fd)
{
	char		*line;
	static char	*reminder;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	reminder = ft_read_reminder(fd, reminder);
	if (!reminder)
		return (NULL);
	line = ft_get_line(reminder);
	reminder = ft_new_reminder(reminder);
	return (line);
}

char	*ft_read_reminder(int fd, char *reminder)
{
	char	*buf;
	int		read_return;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	read_return = 1;
	while (!ft_strchr(reminder, '\n') && read_return)
	{
		read_return = read(fd, buf, BUFFER_SIZE);
		if (read_return == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[read_return] = '\0';
		reminder = ft_strjoin_gnl(reminder, buf);
	}
	free(buf);
	return (reminder);
}

char	*ft_get_line(char *reminder)
{
	int		i;
	char	*line;

	i = 0;
	if (!reminder[i])
		return (NULL);
	while (reminder[i] && reminder[i] != '\n')
		i++;
	line = (char *)malloc((i + 2) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (reminder[i] && reminder[i] != '\n')
	{
		line[i] = reminder[i];
		i++;
	}
	if (reminder[i] == '\n')
	{
		line[i] = reminder[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_new_reminder(char *reminder)
{
	int		i;
	int		j;
	char	*new_reminder;

	i = 0;
	while (reminder[i] && reminder[i] != '\n')
		i++;
	if (!reminder[i])
	{
		free(reminder);
		return (NULL);
	}
	new_reminder = (char *)malloc((ft_strlen(reminder) - i + 1) * sizeof(char));
	if (!new_reminder)
		return (NULL);
	i++;
	j = 0;
	while (reminder[i])
	{
		new_reminder[j++] = reminder[i++];
	}
	new_reminder[j] = '\0';
	free(reminder);
	return (new_reminder);
}

char	*ft_strjoin_gnl(char *reminder, char *buf)
{
	char	*s3;
	size_t	dstsize;

	s3 = NULL;
	if (!reminder)
	{
		reminder = (char *)malloc(sizeof(char));
		reminder[0] = '\0';
	}
	if (reminder && buf)
	{
		dstsize = ft_strlen(reminder) + ft_strlen(buf) + 1;
		s3 = (char *)malloc(sizeof(char) * dstsize);
		if (!s3)
			return (NULL);
		ft_strlcpy(s3, reminder, dstsize);
		ft_strlcat(s3, buf, dstsize);
	}
	free(reminder);
	return (s3);
}
/*
int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
		printf("open() error\n");
	line = get_next_line(fd);
	while (line)
	{
		printf("line =\n%s", line);
		line = get_next_line(fd);
	}
	free(line);
	if (close(fd) == -1)
	{
		printf("close() error\n");
		return (1);
	}
	printf("success\n");
	return (0);
}
*/