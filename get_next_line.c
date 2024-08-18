/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydemyden <ydemyden@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:48:13 by ydemyden          #+#    #+#             */
/*   Updated: 2024/08/18 17:49:03 by ydemyden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Returns a line read from a file descriptor
#include "get_next_line.h"

static int	readandstore(int fd, char **buffer)
{
	char	*temp;
	char	*read_buffer;
	ssize_t	bytes;

	read_buffer = malloc(BUFFER_SIZE + 1);
	if (!read_buffer)
		return (-1);
	bytes = 1;
	while (!ft_strchr(*buffer, '\n') && bytes > 0)
	{
		bytes = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes > 0)
		{
			read_buffer[bytes] = '\0';
			temp = ft_strjoin(*buffer, read_buffer);
			free(*buffer);
			*buffer = temp;
		}
	}
	free(read_buffer);
	return (bytes);
}

static char	*get_line(char **buffer)
{
	char	*line;
	char	*temp;
	size_t	len;

	len = 0;
	while ((*buffer[len]) && (*buffer[len]) != '\n')
		len++;
	if ((*buffer[len]) == '\n')
	{
		line = ft_strdup(*buffer);
		temp = ft_strdup(*buffer);
		free(*buffer);
		*buffer = temp;
		if (**buffer == '\0')
		{
			free(*buffer);
			*buffer = NULL;
		}
		return (line);
	}
	line = ft_strdup(*buffer);
	free(*buffer);
	*buffer = NULL;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	int			reading;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	reading = readandstore(fd, &buffer);
	if (reading < 0 || (reading == 0 && !buffer))
		return (NULL);
	return (get_line(&buffer));
}

// int main()
// {
// 	int	fd;
	
// 	fd = open("file.txt", O_RDONLY);
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	return (0);
// }