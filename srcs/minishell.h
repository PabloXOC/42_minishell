/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:14:43 by pximenez          #+#    #+#             */
/*   Updated: 2024/05/22 15:08:54 by paxoc01          ###   ########.fr       */
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


typedef enum e_cases		t_cases;
typedef struct s_var		t_var;
typedef struct s_command	t_command;

typedef enum e_cases
{
	SUCCESS,
	FAILURE,
	MALLOC_ERROR,
	EMPTY,
	INVALID_COMMAND,
	INVALID_TOKEN,
	OPEN_ERROR,
	CLOSE_ERROR,
	READ_ERROR,
	OPEN_ERROR,
	CLOSE_ERROR,
	READ_ERROR,
}		t_cases;

typedef struct s_var
{
	char			*var;
	char			**content;
	t_var			*next;
}					t_var;

typedef struct s_command
{
	char			**content;
	char			*full_path;
	t_command		*next;
}					t_command;

typedef struct s_data
{
	char		**input_split;
	char		*input;

	//for terminal entry information
	char		*user;
	char		*hostname;
	char		*dir;
	char		*entry;

	int			paired; //to deal with '' ""
	bool		exit; //if command == exit
	int			input_index; //until where have we read the input
	int			eof_index; //last eof read

	t_command	*command_list; //list of the commands in the input + command info
	char		*text_input; //     < or <<
	char		*redirect_input; // file name if we have a < I AM NOT USING THIS
	char		*redirect_output; // file name if we have a > or >>
	char		*limiter; // string that stops << I AM NOT USING THIS. INSTEAD LOCAL, VARIABLE
	bool		*terminal_input; // boolean for (true == <<)
	bool		*file_input; // boolean for (true == <)
	bool		append_output; // boolean for (true == >>) & (false == >)
	char		*next_eof; //pointer to where i left off in <<
	t_var		*var; //list of all variables
	t_var		*var_export; //list of all export variables

	//errors
	bool		malloc_error;
}			t_data;

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
bool			ft_samestr(const char *s1, const char *s2);
int			ft_count_words(char **argv);
void		print_char_pp(char **stack);
void		ft_free_char_pp(char **stack);

/*------INPUT------*/
t_data		*data_init(void);
int			ft_pair(char *input, char c, int i, t_data *data);
bool		ft_not_complete(char *input, t_data *data);
char		*ft_join_input(char *s1, char *s2);

/*------COMMANDS------*/
int			find_command(t_data *data, t_list *com, char **env);
int			save_commands(t_data *data);
void		delete_commands(t_data *data);

/*------WRITE------*/
int			ft_write_error_i(t_cases case_code, t_data *data);
char		*ft_write_error_c(t_cases case_code, t_data *data);

/*------TERMINAL------*/
int			get_user(t_data *data, char **env);
//int	get_hostname();
int			ft_get_dir(t_data *data, char **env);
int			terminal_entry(t_data *data, char **env);

/*------VARIABLES------*/

int			delete_var(t_data *data, char *var_to_del);

/*------REFORMAT------*/
char		*ft_reformat_input(char *input, t_data *data);


/*------CHECK IF VAR------*/
bool		check_if_we_save_variables(t_data *data);





int	open_input(t_data *data);
int	recieve_complete_input(t_data *data);



#endif