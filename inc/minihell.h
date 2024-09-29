/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minihell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:42:52 by ramzerk           #+#    #+#             */
/*   Updated: 2024/09/29 21:31:45 by rabouzia         ###   ########.fr       */
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
	PIPE,
}						t_token_type;

typedef struct s_token
{
	char				*str;
	t_token_type		type;
	struct s_token		*next;
}						t_token;

typedef enum e_redir_type
{
	IN,
	OUT,
	HEREDOC,
	APPEND,
}						t_redir_type;

typedef struct s_redir
{
	char				*file;
	t_redir_type		type;
	struct s_redir		*next;
}						t_redir;

typedef struct s_command
{
	char				**arguments;
	t_redir				*redir;
	struct s_command	*next;
}						t_command;

typedef struct s_minishell
{
	t_token				*token;
	t_command			*command;
}						t_minishell;

// ############# parsing #############

int						parsing(char *input, t_minishell *minishell);

bool					tokenization(char *input, t_minishell *minishell);

bool					syntax_analysis(t_minishell *minishell);

bool					init_state(t_token *token);

bool					word_state(t_token *token);

bool					pipe_state(t_token *token);

bool					redir_state(t_token *token);

bool					add_pipe(int *i, t_minishell *minishell);

bool					add_redir_double(char *input, int *i,
							t_minishell *minishell);

bool					add_redir_simple(char *input, int *i,
							t_minishell *minishell);

int						get_len_word(char *input, int i);

bool					tidying(t_minishell *minishell);

bool					add_word(char *input, int *i, t_minishell *minishell);

// ############# exec    #############

// ############# expand  #############

// ############# lib minihell ########

int						ft_strlen(char *str);

char					*ft_strdup(char *str);

char					*ft_substr(char *s, unsigned int start, int len);

int						ft_strcmp(char *s1, char *s2);

int						ft_strncmp(char *s1, char *s2, int n);

bool					is_space(char c);

bool					is_not_word(char c);

char					**add_argument(char **tab, char *str);

void					free_tab(char **tab);

// token ########

void					ft_tokenaddback(t_token **head, t_token *new);

t_token					*ft_tokennew(char *str, t_token_type type);

t_token					*ft_tokenlast(t_token *head);

void					ft_tokenclear(t_token *token);

// redir ########

void					ft_commandaddback(t_command **head, t_command *new);

t_command				*ft_commandnew(char **tab, t_redir *new);

t_command				*ft_commandlast(t_command *head);

void					ft_commandclear(t_command *cmd);

// command #######

void					ft_rediraddback(t_redir **head, t_redir *new);

t_redir					*ft_redirnew(char *str, t_redir_type type);

t_redir					*ft_redirlast(t_redir *head);

void					ft_redirclear(t_redir *redir);

// ############# debug tools ########

void					print_tab(char **tab);

void					print_token(t_token *token);

void					print_command(t_command *command);

void					print_redir(t_redir *redir);

#endif