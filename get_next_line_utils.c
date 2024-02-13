/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawild <hawild@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:04:09 by hawild            #+#    #+#             */
/*   Updated: 2024/01/25 11:41:24 by hawild           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		j;
	int		i;
	char	*joinedstr;

	j = 0;
	i = 0;
	joinedstr = malloc(sizeof(*joinedstr) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!joinedstr)
		return (NULL);
	while (s1[j])
	{
		joinedstr[j] = s1[j];
		j++;
	}
	while (s2[i])
	{
		joinedstr[j + i] = s2[i];
		i++;
	}
	joinedstr[j + i] = 0;
	return (joinedstr);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(src);
	if (n == 0)
		return (len);
	if (n != 0)
	{
		while (src[i] != '\0' && i < (n - 1))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (len);
}

char	*ft_strdup(const char *s)
{
	int		len;
	char	*new;
	int		i;

	i = 0;
	len = ft_strlen((char *)s);
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (new != NULL)
	{
		while (s[i] != '\0')
		{
			new[i] = s[i];
			i++;
		}
		new[i] = '\0';
		return (new);
	}
	return (NULL);
}

int	ft_strchr(char *s, char c)
{
	size_t	i;

	i = 0;
	while (i <= ft_strlen(s))
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	i;

	if (!s)
		return (0);
	i = ft_strlen(s);
	if (i < start)
	{
		return (ft_strdup(""));
	}
	else if (ft_strlen(s + start) < len && len != 0)
		len = ft_strlen(s + start);
	substr = malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (0);
	ft_strlcpy(substr, s + start, len + 1);
	return (substr);
}
