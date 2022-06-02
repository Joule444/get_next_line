/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 11:37:04 by jthuysba          #+#    #+#             */
/*   Updated: 2022/06/02 15:40:05 by jthuysba         ###   ########.fr       */
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

char	*keep_rest(char *buffer)
{
	int		i;
	char	*rest;

	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	rest = malloc(sizeof(char) * ft_strlen(buffer + i + 1) + 1);
	ft_strcpy(rest, buffer + i + 1);
	return (rest);
}

char	*cut_end(char *buffer)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = malloc(sizeof(char) * ft_strlen(buffer) + 1);
	ft_strcpy(tmp, buffer);
	free (buffer);
	while (tmp[i] && tmp[i] != '\n')
		i++;
	tmp[i] = '\0';
	buffer = malloc(sizeof(char) * i + 1);
	ft_strcpy(buffer, tmp);
	free(tmp);
	return (buffer);
}

char	*get_next_line(int fd)
{
	char			*buffer;
	char			*buffer_tmp;
	static char		*rest;
	static int		end;
	int				x;

	if (end != 1)
		end = 0;
	else
		return (NULL);
	if (!rest)
	{
		rest = malloc(sizeof(char) * 1);
		rest[0] = '\0';
	}
	buffer = malloc(sizeof(char) * (ft_strlen(rest) + 1));
	ft_strcpy(buffer, rest);
	buffer_tmp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (!check_endline(buffer))
	{
		x = read(fd, buffer_tmp, BUFFER_SIZE);
		if (x <= 0)
		{
			end = 1;
			free(buffer);
			free(buffer_tmp);
			break ;
		}
		buffer_tmp[x] = '\0';
		buffer = ft_strjoin(buffer, buffer_tmp);
	}
	free(rest);
	rest = keep_rest(buffer);
	buffer = cut_end(buffer);
	return (buffer);
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
	printf("%s\n",s);
	while (s)
	{
		free(s);
		s = get_next_line(fd);
    	printf("%s", s);
		printf("\n");
	}
	free(s);
}