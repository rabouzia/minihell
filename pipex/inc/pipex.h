/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:45:25 by ramzerk           #+#    #+#             */
/*   Updated: 2024/04/09 17:06:52 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipe
{
	int		fd_in;
	int		fd_out;
	int		pipe[2];
	int		oldfd;
	char	**env;
	char	**av;
	int		flag;

	int		ac;
	int		i;
}			t_pipe;

//---------------- pipexu --------------------
void		excute(char **cmd, char **env);
void		error_msg(char *path, char **cmd);

//---------------- pipex_bonus -------------
int			ac_loop(t_pipe *pipex);
int			flag_out(t_pipe *pipex);
char		**cmd_get(char *cmd);
int			here_doc(t_pipe *p);
int			foruku(t_pipe *p);
void		loop_here_doc(char *tmp, t_pipe *p, int fd);

// ---------------- mini_libft ----------------
char		**ft_split(char *s, char c);
char		*ft_strjoin(char *s1, char *s2);
int			ft_strlen(char *str);
char		*ft_substr(char *s, int start, int len);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*empty(void);
char		*get_next_word(char *str, int *ptr, char c);
int			count_words(char *str, char c);
int			ft_strlcpy(char *dst, char *src, int size);
void		warp_pipe(char **av, char **env);
int			ft_strchr(char *str, char c);
char		*ft_strdup(char *src);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);

#endif
