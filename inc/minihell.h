/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minihell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramzerk <ramzerk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:42:52 by ramzerk           #+#    #+#             */
/*   Updated: 2024/09/29 01:02:03 by ramzerk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <readline/history.h>  // add_history, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay
#include <readline/readline.h> // readline
#include <dirent.h>
#include <unistd.h>
#include <termios.h>
#include <sys/wait.h>
#include <sys/types.h> // stat, lstat, fstat, unlink
#include <sys/stat.h>  // stat, lstat, fstat
#include <sys/ioctl.h> // ioctl
#include <string.h>	   // strerror
#include <stdlib.h>	   // malloc, free, exit
#include <stdio.h>	   // printf
#include <stdbool.h>

typedef enum e_token_type
{
	WORD,
	REDIR,
	PIPE
} t_token_type;

typedef struct s_token
{
	char *str;
	t_token_type type;
	struct s_token *next;
} t_token;


typedef struct s_minishell
{
	t_token *token;
}	t_minishell;

// ############# exec    #############

// ############# parsing #############

int 	parsing(char *input, t_minishell *minishell);

bool 	tokenization(char *input, t_minishell *minishell);

bool 	syntax_analysis(t_minishell *minishell);

// ############# expand  #############


#endif