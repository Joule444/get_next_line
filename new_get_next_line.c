/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_get_next_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 12:13:50 by jthuysba          #+#    #+#             */
/*   Updated: 2022/06/07 17:15:30 by jthuysba         ###   ########.fr       */
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

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes = read(fd, buffer, BUFFER_SIZE);
	if (bytes <= 0)
		return (NULL);
	while (bytes > 0 && !check_endline(buffer))
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
	line = malloc(sizeof(char) * i + 1);
	if (!line)
		return (NULL);
	ft_strcpy(line, stock);
	line[i] = '\0';
	return (line);
}

char	*get_rest(char *stock)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = malloc(sizeof(char) * (ft_strlen(stock) + 1));
	if (!tmp)
		return (NULL);
	ft_strcpy(tmp, stock);
	//free(stock);
	while (tmp[i] != '\n' && tmp[i])
		i++;
	stock = malloc(sizeof(char) * ft_strlen(tmp + i) + 1);
	if (!stock)
		return (NULL);
	ft_strcpy(stock, tmp + i + 1);
	return (free(tmp), stock);
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
	if (!stock)
		return (NULL);
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
	printf("\n");
	while (s)
	{
		free(s);
		s = get_next_line(fd);
    	printf("%s", s);
		printf("\n");
	}
	free(s);
}
