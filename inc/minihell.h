/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minihell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:42:52 by ramzerk           #+#    #+#             */
/*   Updated: 2024/10/18 20:40:13 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIHELL_H
# define MINIHELL_H

# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

// token
extern volatile sig_atomic_t	g_signal;

typedef enum e_token_type
{
	WORD,
	REDIR,
	PIPE,
}								t_token_type;

typedef struct s_token
{
	char						*str;
	t_token_type				type;
	struct s_token				*next;
}								t_token;

// command

typedef enum e_redir_type
{
	IN,
	OUT,
	HEREDOC,
	APPEND,
}								t_redir_type;

typedef struct s_redir
{
	char						*file;
	t_redir_type				type;
	char						**heredoc_content;
	struct s_redir				*next;
}								t_redir;

typedef struct s_command
{
	char						**arguments;
	t_redir						*redir;
	struct s_command			*next;
	int							pid;
}								t_command;

// env

typedef struct s_env
{
	char						*key;
	char						*value;
	struct s_env				*next;
}								t_env;

// minishell

typedef struct s_minishell
{
	t_env						*env;
	t_token						*token;
	t_command					*command;
	char						**envp;
	int							state;
}								t_minishell;

// ############# parsing #############

int								parsing(char *input, t_minishell *minishell);

bool							tokenization(char *input,
									t_minishell *minishell);

bool							syntax_analysis(t_minishell *minishell);

bool							init_state(t_token *token);

bool							word_state(t_token *token);

bool							pipe_state(t_token *token);

bool							redir_state(t_token *token);

bool							add_pipe(int *i, t_minishell *minishell);

bool							add_redir_double(char *input, int *i,
									t_minishell *minishell);

bool							add_redir_simple(char *input, int *i,
									t_minishell *minishell);

int								get_len_word(char *input, int i);

bool							tidying(t_minishell *minishell);

bool							add_word(char *input, int *i,
									t_minishell *minishell);

// ############# exec    #############

bool							is_a_builtin(char **arg);

bool							exec(t_command *cmd, t_minishell *minishell);

int								builtins(t_minishell *minishell,
									t_command *cmd);

int								open_redirections(t_command *cmd,
									t_minishell *minishell);

int								ft_cd(t_minishell *minishell, char **arg);

int								ft_echo(t_minishell *minishell, char **arg);

int								good_flag(const char *str);

int								ft_env(t_minishell *minishell, char **arg);

void							env_print(t_env *env);

int								ft_exit(t_minishell *minishell, char **arg);

int								ft_export(t_minishell *minishell, char **arg);

void							export_print(t_env *env);

char							*get_exportkey(char *str);

void							export_create(t_minishell *minishell,
									char *arg);

int								ft_pwd(t_minishell *minishell, char **arg);

int								ft_unset(t_minishell *minishell, char **arg);

void							ft_end(t_minishell *minishell);

// pipe

void							excute(char **cmd, char **env,
									t_minishell *minishell);

void							ft_tabupdate(t_minishell *minishell);

void							error_msg(char *path, char **cmd,
									t_minishell *minishell);

char							*cmd_finder(char **cmd, char **env);

// ############# expand  #############

char							*expand(char *str, t_minishell *minishell);

int								change_quote(char quote, int i);

void							if_expand(t_minishell *minishell,
									char *expanded, int *i);

void							set_signal_child(void);

bool							init_env(char **env, t_minishell *minishell);

int								get_expanded_len(char *str,
									t_minishell *minishell);

// ############# lib minihell ########

int								ft_isspace(char c);

bool							is_env_valid(char c, bool start);

char							*ft_strjoin3(char *s1, char *s2, char *s3);

char							*ft_strjoin(char *s1, char *s2);

void							ft_putendl_fd(char *s, int fd);

char							**ft_split(char const *s, char c);

size_t							ft_strlcpy(char *dst, char *src, size_t size);

char							*get_key(char *str);

int								ft_atoi(char *str);

char							*get_value_env(char *key, t_env *env);

int								ft_strlen(char *str);

char							*ft_strdup(char *str);

void							ft_signal(void);

char							*ft_substr(char *s, unsigned int start,
									int len);

int								ft_strcmp(char *s1, char *s2);

int								ft_strncmp(char *s1, char *s2, int n);

void							ft_strncat(char *dst, const char *src,
									size_t size);

void							ft_putstr_fd(char *str, int fd);

bool							is_space(char c);

bool							is_not_word(char c);

char							**add_argument(char **tab, char *str);

void							*ft_memset(void *s, int c, size_t n);

void							free_tab(char **tab);

bool							ft_isalpha(char c);

void							export_print(t_env *env);

int								search_env(t_env *env, char *key);

int								ft_strchr(char *str, char c);

bool							delete_node(t_env **env, char *to_delete);

char							*ft_itoa(int n);

void							remove_first(t_env **env);

void							remove_last(t_env *env);

void							remove_node(t_env *env, char *to_delete);

void							modify_value(t_env *env, char *key,
									char *value);

void							free_node(t_env *env);

int								count_env(t_env *env);

bool							ft_isnum(char c);

// token ########

void							ft_tokenaddback(t_token **head, t_token *new);

t_token							*ft_tokennew(char *str, t_token_type type);

t_token							*ft_tokenlast(t_token *head);

void							ft_tokenclear(t_token **token);

// redir ########

void							ft_commandaddback(t_command **head,
									t_command *new);

t_command						*ft_commandnew(char **tab, t_redir *new);

t_command						*ft_commandlast(t_command *head);

void							ft_commandclear(t_command **cmd);

void							free_all_heredoc(t_command *cmd);

// command #######

void							ft_rediraddback(t_redir **head, t_redir *new);

t_redir							*ft_redirnew(char *str, t_redir_type type,
									t_minishell *minishell);

t_redir							*ft_redirlast(t_redir *head);

void							ft_redirclear(t_redir *redir);

// env ###########

void							ft_envaddback(t_env **head, t_env *new);

t_env							*ft_envnew(char *key, char *value);

t_env							*ft_envlast(t_env *head);

void							ft_envclear(t_env **env);

bool							init_env(char **env, t_minishell *minishell);

char							*get_key(char *str);

char							*get_value(char *str);

void							print_tab(char **tab);

void							print_token(t_token *token);

void							print_command(t_command *command);

void							print_redir(t_redir *redir);

void							print_env(t_env *env);

#endif
