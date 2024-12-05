/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaiduc <thaiduc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:54:49 by thaiduc           #+#    #+#             */
/*   Updated: 2024/12/05 20:04:53 by thaiduc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 99999
# endif

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>

char	*get_next_line(int fd);
size_t	gnl_strlen(const char *str);
char	*gnl_strdup(const char *src, size_t len);
char	*gnl_strjoin(char *s1, char *s2);
int		gnl_has_newline(const char *str);

#endif
