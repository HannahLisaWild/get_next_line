/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawild <hawild@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:27:53 by hawild            #+#    #+#             */
/*   Updated: 2024/02/13 14:57:59 by hawild           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*str;
	size_t	i;

	i = 0;
	str = malloc(nmemb * size);
	if (!str)
		return (NULL);
	while (i < (nmemb * size))
		str[i++] = '\0';
	return (str);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

static char	*fill_line(char *line, char *remains)
{
	ssize_t	bytes;

	bytes = 0;
	while (line[bytes] != '\n' && line[bytes] != '\0')
		bytes++;
	if (line[bytes] == 0 || line[1] == 0)
		return (NULL);
	remains = ft_substr(line, bytes + 1, (ft_strlen(line) - bytes));
	if (remains[0] == 0)
	{
		free(remains);
		remains = NULL;
	}
	line[bytes + 1] = '\0';
	return (remains);
}

static char	*read_to_buffer(int fd, char *remains, char *buffer)
{
	ssize_t	bytes_read;
	char	*tmp;

	bytes_read = 1;
	while (bytes_read > 0 && (ft_strchr(buffer, '\n') != 1))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == 0)
			break ;
		if (bytes_read < 0)
		{
			free(remains);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		if (!remains)
			remains = ft_strdup("");
		tmp = remains;
		remains = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
	}
	free(buffer);
	buffer = NULL;
	return (remains);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	static char	*remains[4096];

	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(buffer);
		free(remains[fd]);
		buffer = NULL;
		remains[fd] = 0;
		return (NULL);
	}
	line = read_to_buffer(fd, remains[fd], buffer);
	if (!line)
		return (NULL);
	remains[fd] = fill_line(line, remains[fd]);
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("example.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("Error opening the file");
// 		return (1);
// 	}
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("Line read: %s", line);
// 		free(line);
// 	}
// 	if (close(fd) == -1)
// 	{
// 		perror("Error closing the file");
// 		return (1);
// 	}
// 	return (0);
// }

// int main()
// {
//     char *line;

//     while ((line = get_next_line(0)) != NULL)
//     {
//         printf("Line read: %s\n", line);
//         free(line);
//     }
//     return (0);
// }
