/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 18:37:43 by maruzibo          #+#    #+#             */
/*   Updated: 2023/06/25 15:34:37 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*sfiles(int fd, char *buf, char *stor)
{
	ssize_t	rff;
	char	*story;

	rff = 1;
	while (rff > 0)
	{
		rff = read(fd, buf, BUFFER_SIZE);
		if (rff < 0)
			return (NULL);
		else if (rff == 0)
			break ;
		buf[rff] = '\0';
		if (!stor)
			stor = ft_strdup("");
		story = stor;
		stor = ft_strjoin(story, buf);
		free(story);
		story = NULL;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (stor);
}

static char	*rline(char *lin)
{
	char	*newstor;
	size_t	br;

	br = 0;
	while (lin[br] != '\0' && lin[br] != '\n')
		br++;
	if (lin[br] != '\n' || lin[br + 1] == '\0')
		return (NULL);
	newstor = ft_substr(lin, br + 1, ft_strlen(lin) - br);
	if (*newstor == '\0')
	{
		free(newstor);
		newstor = NULL;
		return (0);
	}
	lin[br + 1] = '\0';
	return (newstor);
}

char	*get_next_line(int fd)
{
	static char	*stor;
	char		*buf;
	char		*lin;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	else if (read(fd, 0, 0) < 0)
	{
		free(stor);
		stor = NULL;
		return (NULL);
	}
	buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	lin = sfiles(fd, buf, stor);
	free(buf);
	buf = NULL;
	if (!lin)
		return (NULL);
	stor = rline(lin);
	return (lin);
}
