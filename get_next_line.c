/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 11:37:04 by jthuysba          #+#    #+#             */
/*   Updated: 2022/05/26 17:31:29 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_endline(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	char			*buffer;
	char			*buffer_tmp;
	static char		*rest;
	ssize_t			size;
	int				i;

	if (!rest)
		rest = "";
	buffer = malloc(sizeof(char) * ft_strlen(rest) + 1);
	size = 0;
	ft_strcpy(buffer, rest);
	buffer_tmp = malloc(sizeof(char) * BUFFER_SIZE + 1);
	i = 0;
	while (!check_endline(buffer))
	{
		size += read(fd, buffer_tmp, BUFFER_SIZE);
		buffer = ft_strjoin(buffer, buffer_tmp);
	}
	buffer[size] = '\0';
	while (buffer[i] && buffer[i] != '\n')
		i++;
	rest = malloc(sizeof(char) * ft_strlen(buffer + i) + 1);
	ft_strcpy(rest, buffer + i + 1);
	buffer[i] = '\0';
	return (buffer);
}

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main()
{
    int fd;

    fd = open("bounce", O_RDONLY);
    printf("%s\n", get_next_line(fd));
    printf("%s\n", get_next_line(fd));
    printf("%s\n", get_next_line(fd));
	printf("%s\n", get_next_line(fd));
    printf("%s\n", get_next_line(fd));
    printf("%s\n", get_next_line(fd));
	printf("%s\n", get_next_line(fd));
    printf("%s\n", get_next_line(fd));
    printf("%s\n", get_next_line(fd));
}