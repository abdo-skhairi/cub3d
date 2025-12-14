/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeskhai <maeskhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 11:17:14 by maeskhai          #+#    #+#             */
/*   Updated: 2025/09/24 16:36:33 by maeskhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

char	*get_next_line(int fd);
void	ft_readjoin(int fd, char **next1);
char	*ft_new_line(char *next1);
char	*ft_next(char *next1);
int		ft_strchr(char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
void	*ft_calloc(size_t count, size_t size);
void	ft_free(char **s1, char **s2);
int	ft_strlen(char *s);
char	*ft_strdup(char *s1);
char	*ft_substr(char *s, unsigned int start, size_t len);
#endif