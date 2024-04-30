/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farah <farah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:14:43 by pximenez          #+#    #+#             */
/*   Updated: 2024/04/30 14:05:32 by farah            ###   ########.fr       */
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
# include <string.h>
# include <errno.h>
# include <signal.h>
# include <stdbool.h>

// Regular Colors
# define BLK   "\033[0;30m"     /* Black */
# define R     "\033[0;31m"     /* Red */
# define G   "\033[0;32m"     /* Green */
# define YE  "\033[0;33m"     /* Yellow */
# define B    "\033[0;34m"     /* Blue */
# define M "\033[0;35m"     /* Magenta */
# define Y    "\033[0;36m"     /* Cyan */
# define W   "\033[0;37m"     /* White */

// Bold
# define BBLK   "\033[1;30m"      /* Bold Black */
# define BR     "\033[1;31m"      /* Bold Red */
# define BG   "\033[1;32m"      /* Bold Green */
# define BYE  "\033[1;33m"      /* Bold Yellow */
# define BB    "\033[1;34m"      /* Bold Blue */
# define BM "\033[1;35m"      /* Bold Magenta */
# define BC    "\033[1;36m"      /* Bold Cyan */
# define BW   "\033[1;37m"      /* Bold White */

typedef enum e_cases
{
	SUCCESS,
	FAILURE,
	MALLOC_ERROR,
	EMPTY,
	INVALID_COMMAND
}		t_cases;

typedef struct s_var
{
	char			*var;
	char			*content;
	struct s_var	*next;
}					t_var;

typedef struct s_command
{
	int			n_words;
	char		**command_parsed;
	char		*full_address;
	char		*input;

	char		*user;
	char		*hostname;
	char		*dir;
	char		*entry;

	int			paired;
	int			exit;

	t_list	*command_list;
	char		*create_var;
	char		*redirect_input;
	char		*redirect_output;
	char		*limiter;
	char		*append_output;
	t_var		*var;
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
int			main(int argc, char **argv, char **env);

/*------UTILS------*/
bool		ft_empty(char *input);
bool		ft_there_is_equal(char *input);
int			ft_samestr(const char *s1, const char *s2);
int			ft_count_words(char **argv);
void		print_char_pp(char **stack);
void	ft_free_char_pp(char **stack);

/*------INPUT------*/
t_command	*command_init(void);
int			ft_pair(char *input, char c, int i, t_command *command);
bool		ft_not_complete(char *input, t_command *command);
char		*ft_join_input(char *s1, char *s2);

/*------COMMANDS------*/
int			find_command(t_command *command, char **env);
void	save_commands(t_command *command);
void	delete_commands(t_command *command);

/*------WRITE------*/
int			ft_write_error_i(t_cases case_code, t_command *command);
char		*ft_write_error_c(t_cases case_code, t_command *command);

/*------TERMINAL------*/
int	get_user(t_command *command, char **env);
//int	get_hostname();
int	ft_get_dir(t_command *command, char **env);
int	terminal_entry(t_command *command, char **env);

/*------VARIABLES------*/
int	safe_var(t_command *command);
int	delete_var(t_command *command, char *var_to_del);

#endif