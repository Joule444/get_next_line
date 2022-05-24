/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 11:37:04 by jthuysba          #+#    #+#             */
/*   Updated: 2022/05/24 15:54:59 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int check_endline(char *buffer)
{
    int i;

    i = 0;
    while (buffer[i])
    {
        if (buffer[i] == '\n')
            return (1);
        i++;
    }
    return (0);
}

char    *get_next_line(int fd)
{
    char    *buffer;
    char    *buffer_tmp;
    ssize_t size;
    int     i;

    buffer = "";
    buffer_tmp = malloc(sizeof(char) * BUFFER_SIZE + 1);
    i = 0;
    while (!check_endline(buffer))
    {
        read(fd, buffer_tmp, BUFFER_SIZE);
        buffer = ft_strjoin(buffer, buffer_tmp);
    }
    while (buffer[i] && buffer[i] != '\n')
        i++;
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
}