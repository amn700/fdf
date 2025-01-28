/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohchaib <mohchaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:58:55 by marvin            #+#    #+#             */
/*   Updated: 2025/01/20 09:37:13 by mohchaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_and_append(int fd, char *st_buffer, char *buffer)
{
	int		bytes_read;
	char	*temp;

	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		if (st_buffer == NULL)
			temp = ft_strjoin("", buffer);
		else
			temp = ft_strjoin(st_buffer, buffer);
		free(st_buffer);
		st_buffer = NULL;
		if (temp == NULL)
			return (NULL);
		st_buffer = temp;
		if (ft_strchr_get(st_buffer, '\n') != -1)
			break ;
	}
	return (st_buffer);
}

char	*ft_copy_until_new_line(char *st_buffer, char *line)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (st_buffer[len] && st_buffer[len] != '\n')
		len++;
	if (st_buffer[len] == '\n')
		len++;
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	while (st_buffer[i] && st_buffer[i] != '\n')
	{
		line[i] = st_buffer[i];
		i++;
	}
	if (st_buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_copy_after_newline(char *st_buffer)
{
	int		i;
	int		j;
	char	*new_st_buffer;

	i = 0;
	j = 0;
	if (st_buffer == NULL)
		return (free(st_buffer), st_buffer = NULL, NULL);
	while (st_buffer[i] && st_buffer[i] != '\n')
		i++;
	if (st_buffer[i] == '\n')
		i++;
	if (st_buffer[i] == '\0')
		return (free(st_buffer), st_buffer = NULL, NULL);
	new_st_buffer = malloc((int)ft_strlen(st_buffer) - i + 1);
	if (new_st_buffer)
	{
		while (st_buffer[i + j])
		{
			new_st_buffer[j] = st_buffer[i + j];
			j++;
		}
		new_st_buffer[j] = '\0';
	}
	return (free(st_buffer), st_buffer = NULL, new_st_buffer);
}

char	*get_next_line(int fd)
{
	static char	*st_buffer;
	char		*buffer;
	char		*line;

	line = NULL;
	if (fd < 0)
		return NULL;
	if (BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free(st_buffer), st_buffer = NULL, NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(st_buffer), st_buffer = NULL, NULL);
	st_buffer = ft_read_and_append(fd, st_buffer, buffer);
	free(buffer);
	if (!st_buffer)
		return (free(st_buffer), st_buffer = NULL, NULL);
	line = ft_copy_until_new_line(st_buffer, line);
	if (!line)
		return (free(st_buffer), st_buffer = NULL, NULL);
	st_buffer = ft_copy_after_newline(st_buffer);
	return (line);
}
