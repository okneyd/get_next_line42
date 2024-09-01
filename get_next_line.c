/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydemyden <ydemyden@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:48:13 by ydemyden          #+#    #+#             */
/*   Updated: 2024/09/01 17:03:00 by ydemyden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Returns a line read from a file descriptor
#include "get_next_line.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

int	readandstore(int fd, char **buffer)
{
	char	*temp;
	char	*read_buffer;
	ssize_t	bytes;

	read_buffer = malloc(BUFFER_SIZE + 1);
	if (!read_buffer)
		return (-1);
	bytes = read(fd, read_buffer, BUFFER_SIZE);
	while (bytes > 0)
	{
		read_buffer[bytes] = '\0';
		if (*buffer == NULL)
			temp = ft_strdup(read_buffer);
		else
			temp = ft_strjoin(*buffer, read_buffer);
		free(*buffer);
		*buffer = temp;
		if (ft_strchr(*buffer, '\n'))
		{
			free(read_buffer);
			return (1);
		}
		bytes = read(fd, read_buffer, BUFFER_SIZE);
	}
	free(read_buffer);
	return (bytes);
}

char	*get_a_line(char **buffer)
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
	return (get_a_line(&buffer));
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
// int main()
// {
// 	int fd = open("file.txt", O_RDONLY);
// 	if (fd < 0)
// 	{
// 		perror("Failed to open file");
// 		return 1;
// 	}

// 	char *line;
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return 0;
// }