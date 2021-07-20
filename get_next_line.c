/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbathe <bbathe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 16:29:49 by bbathe            #+#    #+#             */
/*   Updated: 2021/05/23 19:58:58 by bbathe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	update_line(char *buf, char **line)
{
	char		*t_line;

	t_line = *line;
	*line = ft_strjoin(*line, buf);
	free(t_line);
}

int	while_cycle(char *buf, char **line, int fd, int *rd)
{
	int		i;
	char	*t_line;

	i = 0;
	while (buf[i] != '\n' && *rd > 0)
	{
		if (buf[i] == '\0')
		{
			if ((*line)[0] == '\0')
			{
				t_line = *line;
				*line = ft_strdup(buf);
				free(t_line);
			}
			else
				update_line(buf, &(*line));
			i = 0;
			*rd = read(fd, buf, BUFFER_SIZE);
			if (*rd >= 0)
				buf[*rd] = '\0';
		}
		else
			i++;
	}
	return (i);
}

int	main_gnl(int fd, char **line)
{
	int			i;
	static char	buf[BUFFER_SIZE + 1];
	int			rd;

	rd = 1;
	(*line)[0] = '\0';
	if (buf[0] == '\0')
	{
		rd = read(fd, buf, BUFFER_SIZE);
		if (rd >= 0)
			buf[rd] = '\0';
	}
	i = while_cycle(buf, line, fd, &rd);
	if (rd == 0)
		return (0);
	if (buf[i] == '\n')
	{
		buf[i] = '\0';
		update_line(buf, &(*line));
		ft_strlcpy(buf, &buf[i + 1], BUFFER_SIZE + 1);
		return (1);
	}
	return (-1);
}

int	get_next_line(int fd, char **line)
{
	if (BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0 || line == 0)
		return (-1);
	*line = malloc(1);
	if (*line == 0)
		return (-1);
	return (main_gnl(fd, line));
}
