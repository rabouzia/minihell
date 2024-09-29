/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minihell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:42:52 by ramzerk           #+#    #+#             */
/*   Updated: 2024/09/29 18:03:06 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <readline/history.h>
# include <readline/readline.h> // readline
# include <stdbool.h>
# include <stdio.h>     // printf
# include <stdlib.h>    // malloc, free, exit
# include <string.h>    // strerror
# include <sys/ioctl.h> // ioctl
# include <sys/stat.h>  // stat, lstat, fstat
# include <sys/types.h> // stat, lstat, fstat, unlink
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

typedef enum e_token_type
{
	WORD,
	REDIR,
	PIPE
}					t_token_type;

typedef struct s_token
{
	char			*str;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

typedef struct s_minishell
{
	t_token			*token;
}					t_minishell;

// ############# exec    #############

// ############# parsing #############

int					parsing(char *input, t_minishell *minishell);

bool				tokenization(char *input, t_minishell *minishell);

bool				syntax_analysis(t_minishell *minishell);

bool				init_state(t_token *token);

bool				word_state(t_token *token);

bool				pipe_state(t_token *token);

bool				redir_state(t_token *token);

bool				add_pipe(int *i, t_minishell *minishell);

bool				add_redir_double(char *input, int *i,
						t_minishell *minishell);

bool				add_redir_simple(char *input, int *i,
						t_minishell *minishell);

int					get_len_word(char *input, int i);

bool				add_word(char *input, int *i, t_minishell *minishell);

// ############# expand  #############

// ############# lib minihell ########

void				ft_tokenaddback(t_token **head, t_token *new);

t_token				*ft_tokennew(char *str, t_token_type type);

t_token				*ft_tokenlast(t_token *head);

void				ft_tokenclear(t_token *token);

int					ft_strlen(char *str);

char				*ft_substr(char *s, unsigned int start, int len);

int					ft_strncmp(char *s1, char *s2, int n);

bool				is_space(char c);

bool				is_not_word(char c);

// ############# debug tools ########

void				print_token(t_token *token);

#endif