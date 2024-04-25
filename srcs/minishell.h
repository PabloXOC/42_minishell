/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:14:43 by pximenez          #+#    #+#             */
/*   Updated: 2024/04/25 13:57:18 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
/*-------INCLUDES-------*/
# include "../libft/ft_printf.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <curses.h>
# include <signal.h>
# include <stdbool.h>

typedef struct s_command
{
	int		n_words;
	char	**command_parsed;
	char	*full_address;
}		t_command;

/*------PROTOYPES-------*/
int				main(int argc, char **argv, char **env);


//utils
bool	ft_empty(char *input);
bool	ft_there_is_equal(char *input);
int		ft_samestr(const char *s1, const char *s2);
int		ft_count_words(char **argv);

#endif