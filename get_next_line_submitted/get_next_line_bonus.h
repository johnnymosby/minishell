/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maruzibo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:07:54 by maruzibo          #+#    #+#             */
/*   Updated: 2022/11/17 15:11:10 by maruzibo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 6
# endif

# ifndef FD_SETSIZE
#  define FD_SETSIZE 1024
# endif

char	*get_next_line(int fd);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char *s1, const char *s2);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif
