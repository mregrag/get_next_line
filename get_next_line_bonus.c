/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 02:52:09 by mregrag           #+#    #+#             */
/*   Updated: 2023/12/26 13:52:46 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	join_line(char **str, char **buff)
{
	char	*tmp;

	if (!*str)
		*str = ft_strdup("");
	tmp = *str;
	*str = ft_strjoin(tmp, *buff);
	free(tmp);
	tmp = NULL;
}

static char	*get_rest(char *str)
{
	char	*new_str;
	char	*rest;
	int		len;

	rest = ft_strchr(str, '\n');
	if (!rest)
		return (free(str), str = NULL, NULL);
	len = (ft_strlen(str) - ft_strlen(rest)) + 1;
	if (str[len] == '\0')
		return (free(str), str = NULL, NULL);
	new_str = ft_substr(str, len, ft_strlen(str) - len);
	free(str);
	str = NULL;
	if (!new_str)
		return (NULL);
	return (new_str);
}

static char	*get_line(char *str)
{
	char	*line;
	char	*ptr;
	int		len;

	ptr = ft_strchr(str, '\n');
	len = ft_strlen(str) - ft_strlen(ptr);
	line = ft_substr(str, 0, len + 1);
	return (line);
}

static char	*read_from_file(int fd, char *str)
{
	int		bytes;
	char	*buffer;

	bytes = 1;
	buffer = malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!buffer)
		return (free(str), str = NULL, NULL);
	buffer[0] = '\0';
	while (bytes > 0 && !ft_strchr(buffer, '\n'))
	{
		bytes = read (fd, buffer, BUFFER_SIZE);
		if (bytes > 0)
		{
			buffer[bytes] = '\0';
			join_line(&str, &buffer);
		}
	}
	free(buffer);
	buffer = NULL;
	if (bytes == -1)
		return (free(str), str = NULL, NULL);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	str[fd] = read_from_file(fd, str[fd]);
	if (!str[fd])
		return (NULL);
	line = get_line(str[fd]);
	if (!line)
		return (free(str[fd]), str[fd] = NULL);
	str[fd] = get_rest(str[fd]);
	return (line);
}
