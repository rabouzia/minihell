/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramzerk <ramzerk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:42:52 by ramzerk           #+#    #+#             */
/*   Updated: 2024/09/05 17:48:33 by ramzerk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		MINISHELL_H
# define	MINISHELL_H

# include <readline/history.h> 		// add_history, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay
# include <readline/readline.h>     // readline
# include <dirent.h>
# include <unistd.h>
# include <termios.h>
# include <sys/wait.h>		
# include <sys/types.h>				// stat, lstat, fstat, unlink
# include <sys/stat.h>				// stat, lstat, fstat
# include <sys/ioctl.h>				// ioctl
# include <string.h>				// strerror
# include <stdlib.h>				// malloc, free, exit
# include <stdio.h>   				// printf
# include <stdbool.h>



#endif