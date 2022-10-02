/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hohayrap <hohayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 18:57:41 by hohayrap          #+#    #+#             */
/*   Updated: 2021/03/22 16:22:33 by hohayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
# endif

int		get_next_line(int fd, char **line);

int		ft_gnl_strchr(const char *s, int c);

size_t	ft_gnl_strlen(const char *s1);

char	*ft_gnl_strjoin(char *s1, char *s2);

char	*get_gnl_line(char *memory);

char	*get_gnl_buffer(char *s);

#endif
