/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 12:13:50 by jthuysba          #+#    #+#             */
/*   Updated: 2022/06/10 13:00:20 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
		if (bytes < 0)
			return (free(stock), free(buffer), NULL);
		buffer[bytes] = '\0';
		stock = ft_strjoin(stock, buffer);
	}
	if (stock[0] == '\0')
		return (free(stock), free (buffer), NULL);
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
	if (!rest)
		return (free(stock), NULL);
	ft_strcpy(rest, stock + i + 1);
	return (free(stock), rest);
}

char	*get_next_line(int fd)
{
	static char	*stock[FOPEN_MAX];
	char		*line;

	if (fd < 0 || fd > FOPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	line = 0;
	if (!stock[fd])
	{
		stock[fd] = malloc(sizeof(char));
		if (!stock[fd])
			return (NULL);
		stock[fd][0] = '\0';
	}
	stock[fd] = get_read(stock[fd], fd);
	if (!stock[fd] || stock[fd][0] == '\0')
		return (free(stock[fd]), NULL);
	line = get_line(stock[fd], line);
	if (line == NULL)
		return (free(stock[fd]), NULL);
	stock[fd] = get_rest(stock[fd]);
	return (line);
}
