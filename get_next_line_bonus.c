/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:27:53 by hawild            #+#    #+#             */
/*   Updated: 2024/02/12 10:44:47 by szerzeri         ###   ########.fr       */
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

// int main(void)
// {
//     int fd1;
//     int fd2;
//     int fd3;

//     fd1 = open("example.txt", O_RDONLY);
//     fd2 = open("test2.txt", O_RDONLY);
//     fd3 = open("test3.txt", O_RDONLY);

//     if (fd1 == -1 || fd2 == -1)
//     {
//         perror("Error opening files");
//         return (1);
//     }

//     char *line1;
//     while ((line1 = get_next_line(fd1)) != NULL)
//     {
//         printf("File 1: %s\n", line1);
//         free(line1);
//     }

//     char *line2;
//     while ((line2 = get_next_line(fd2)) != NULL)
//     {
//         printf("File 2: %s\n", line2);
//         free(line2);
//     }

//     char *line3;
//     while ((line3 = get_next_line(fd3)) != NULL)
//     {
//         printf("File 3: %s\n", line3);
//         free(line3);
//     }

//     close(fd1);
//     close(fd2);
//     close(fd3);
//     return (0);
// }

// int main(void)
// {
//     int fd1;
//     int fd2;
//     int fd3;

//     fd1 = open("example.txt", O_RDONLY);
//     fd2 = open("test2.txt", O_RDONLY);
//     fd3 = open("test3.txt", O_RDONLY);

//     if (fd1 == -1 || fd2 == -1)
//     {
//         perror("Error opening files");
//         return (1);
//     }

//     char *line1;
//     while ((line1 = get_next_line(fd1)) != NULL)
//     {
//         printf("File 1: %s\n", line1);
//         free(line1);
// 		char *line2;
//     	while ((line2 = get_next_line(fd2)) != NULL)
//     	{
//         	printf("File 2: %s\n", line2);
//         	free(line2);
// 			char *line3;
//     		while ((line3 = get_next_line(fd3)) != NULL)
//     		{
//         		printf("File 3: %s\n", line3);
//        			free(line3);
//    			}
//    		}
//     }
//     close(fd1);
//     close(fd2);
//     close(fd3);
//     return (0);
// }