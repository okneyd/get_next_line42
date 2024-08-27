/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydemyden <ydemyden@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:48:13 by ydemyden          #+#    #+#             */
/*   Updated: 2024/08/27 17:19:59 by ydemyden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Returns a line read from a file descriptor
#include "get_next_line.h"

int	readandstore(int fd, char **buffer)
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
		if (bytes < 0)
		{
			free(read_buffer);
			return (-1);
		}
		read_buffer[bytes] = '\0';
		temp = ft_strjoin(*buffer, read_buffer);
		free(*buffer);
		*buffer = temp;
		if (!*buffer)
		{
			free(read_buffer);
			return (-1);
		}
	}
	free(read_buffer);
	return (bytes);
}

char	*get_line(char **buffer)
{
	char	*line;
	char	*newline_pos;
	char	*temp_buffer;
	size_t	len;

	if (!*buffer || **buffer == '\0')
		return (NULL);
	newline_pos = ft_strchr(*buffer, '\n');
	if (newline_pos)
	{
		len = newline_pos - *buffer;
		line = ft_substr(*buffer, 0, len + 1);
		if (!line)
			return (NULL);
		temp_buffer = ft_strdup(newline_pos + 1);
		free(*buffer);
		*buffer = temp_buffer;
		if (!*buffer || **buffer == '\0')
		{
			free(*buffer);
			*buffer = NULL;
		}
	}
	else
	{
		line = ft_strdup(*buffer);
		free(*buffer);
		*buffer = NULL;
		if (!line)
			return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	int			reading;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	reading = readandstore(fd, &buffer);
	if (reading < 0 || (reading == 0 && (!buffer || *buffer == '\0')))
		return (NULL);
	return (get_line(&buffer));
}

int main()
{
	int	fd;
	
	fd = open("file.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	return (0);
}