/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farah <farah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:14:43 by pximenez          #+#    #+#             */
/*   Updated: 2024/04/26 12:25:40 by farah            ###   ########.fr       */
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

typedef enum e_cases
{
	SUCCESS,
	FAILURE,
	INVALID_COMMAND
}		t_cases;

typedef struct s_command
{
	int		n_words;
	char	**command_parsed;
	char	*full_address;
	char	*input;

	int		paired;
	int		exit;
}			t_command;

typedef enum e_command_code
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
}			t_command_code;

/*------PROTOYPES-------*/
int		main(int argc, char **argv, char **env);

/*------UTILS------*/
bool	ft_empty(char *input);
bool	ft_there_is_equal(char *input);
int		ft_samestr(const char *s1, const char *s2);
int		ft_count_words(char **argv);
void	print_char_pp(char **stack);

/*------INPUT------*/
t_command	*command_init(void);
int	ft_pair(char *input, char c, int i, t_command *command);
bool	ft_not_complete(char *input, t_command *command);
char	*ft_join_input(char *s1, char *s2);

/*------COMMANDS------*/
int	find_command(t_command *command, char **env);

#endif