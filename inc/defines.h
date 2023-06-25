/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbasyrov <rbasyrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:30:44 by rbasyrov          #+#    #+#             */
/*   Updated: 2023/06/25 14:44:22 by rbasyrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# ifndef TRUE
#  define TRUE 1
# endif
# ifndef FALSE
#  define FALSE (!TRUE)
# endif

# define SPACES "\t\n\v\f\r "
# define FT_ERROR 1
# define FT_NOT_ERROR 0
# define FT_PATH_MAX 256

# define NOCMD_NOSIG 0
# define NOCMD_SIG 1
# define CMD_NOSIG 2
# define CMD_SIG 3
# define HEREDOC 4

#endif