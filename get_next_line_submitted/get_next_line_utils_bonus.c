/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maruzibo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:07:01 by maruzibo          #+#    #+#             */
/*   Updated: 2022/11/17 15:07:05 by maruzibo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (s == NULL)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strdup(const char *s)
{
	char	*str;
	size_t	i;

	i = ft_strlen(s) + 1;
	str = (char *)malloc(sizeof(char) * i);
	if (!str)
		return (NULL);
	while (i--)
		str[i] = s[i];
	return (str);
}

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	if (!s1)
		s1 = ft_strdup("\0");
	if (s1)
		while (s1[i])
			str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	char	*ptr;

	if (!s)
		return (NULL);
	if (c == 0)
		return ((char *)&s[ft_strlen(s)]);
	ptr = (char *)s;
	while (*ptr != (char)c && *ptr != '\0')
		ptr++;
	if (*ptr == (char)c)
		return ((char *)ptr);
	if (!c && *ptr == '\0')
		return ((char *)ptr);
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;

	if (!s)
		return (NULL);
	if ((size_t)start > ft_strlen(s))
		return (ft_strdup(""));
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while ((char)s[start] && (size_t)i < len)
		str[i++] = (char)s[start++];
	str[i] = 0;
	return (str);
}
