/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 12:13:50 by jthuysba          #+#    #+#             */
/*   Updated: 2022/06/08 15:34:58 by jthuysba         ###   ########.fr       */
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

char	*get_read(char *stock, int fd)
{
	int		bytes;
	char	*buffer;

	bytes = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (bytes > 0 && !check_endline(stock))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		buffer[bytes] = '\0';
		stock = ft_strjoin(stock, buffer);
	}
	return (free(buffer), stock);
}

char	*get_line(char *stock, char *line)
{
	int	i;

	i = 0;
	while (stock[i] != '\n' && stock[i])
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (stock[i] != '\n' && stock[i])
	{
		line[i] = stock[i];
		i++;
	}
	if (stock[i] == '\n')
	{
		line[i] = '\n';
		line[i + 1] = '\0';
	}
	else
		line[i] = '\0';
	return (line);
}

char	*get_rest(char *stock)
{
	int		i;
	char	*rest;

	i = 0;
	while (stock[i] != '\n' && stock[i])
		i++;
	if (stock[i] == '\0')
		return (free(stock), NULL);
	rest = malloc(sizeof(char) * (ft_strlen(stock + i + 1) + 1));
	ft_strcpy(rest, stock + i + 1);
	return (free(stock), rest);
}

char	*get_next_line(int fd)
{
	static char	*stock;
	char		*line;

	line = 0;
	if (!stock)
	{
		stock = malloc(sizeof(char));
		if (!stock)
			return (NULL);
		stock[0] = '\0';
	}
	stock = get_read(stock, fd);
	if (!stock || stock[0] == '\0')
		return (free(stock), NULL);
	line = get_line(stock, line);
	stock = get_rest(stock);
	return (line);
}

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main()
{
    int fd;
	char	*s = "";
    fd = open("bounce", O_RDONLY);
	//fd = 1 ;
	s = get_next_line(fd);
	printf("%s",s);
	while (s)
	{
		free(s);
		s = get_next_line(fd);
    	printf("%s", s);
	}
	free(s);
}
