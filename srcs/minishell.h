/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:14:43 by pximenez          #+#    #+#             */
/*   Updated: 2024/06/20 16:52:28 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*-------INCLUDES-------*/
# include "../libft/ft_printf.h"
# include "../libft/libft.h"
# include "../libft_lst/lst_com.h"
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
	WRITE_ERROR,
}		t_cases;

typedef struct s_var
{
	char			*var;
	char			*content;
	t_var			*next;
}					t_var;

typedef struct s_input_var
{
	char		*init_input; //the inital input recieved
	char		**init_input_split; // the initial input recieved split with spaces
	char		*first_line;  // the final first line
	char		*first_line_ref; //the final first line reformated (spaces and /)
	char		**first_line_split; //the final first line split with spaces
	char		*search_eof; //to search through terminal input to find eof
	char		*terminal_input; // beginning of << terminal input
	char		*final_text; //what we will actually use for << input text BAD
	char		*final_text_last; //what we will actually use for << input text GOOD
	char		**list_eof; //list of all the eof to look for
	int			n_eof; //how many eof to look for
	char		*first_line_and_final_text;//first_line + final_text
	char		**text_input; //    text of  < or <<
	bool		invalid_token;
}				t_input_var;

typedef struct s_data
{
	//char		**input_split;
	//char		*input;

	//for terminal entry information
	char		*user;
	char		*hostname;
	char		*dir;
	char		*entry;
	char		**env;

	int			paired; //to deal with '' ""
	bool		exit; //if command == exit
	int			input_index; //until where have we read the input

	//char		*first_line;
	//char		*first_line_ref;
	//char		**first_line_split;
	//int			n_eof;
	//char		**list_eof;  //all the eof in order;
	//char		*search_eof; //to search for eof
	//char		*final_text; //what we will actually use for << input text
	t_input_var	*input_info;
	//char		*limiter;
	t_command	*command_list; //list of the commands in the input + command info
	char		**text_input; //    text of  < or <<
	char		*redirect_input; // file name if we have a < I AM NOT USING THIS
	char		*redirect_output; // file name if we have a > or >>
	int			fd_in;
	int			fd_out;
	//char		*terminal_input; // beggining of << terminal input
	bool		file_input; // boolean for (true == <)
	bool		append_output; // boolean for (true == >>) & (false == >)
	char		*next_eof;
	t_var		*var; //list of all variables
	t_var		*var_export; //list of all export variables
	int			i;
	int			i_ter;
	int			j;
	int			k;
	int			ii;
	int			kk;
	int			kkk;
	int			idx_com;
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
bool		ft_samestr(const char *s1, const char *s2);
int			ft_count_words(char **argv);
void		print_char_pp(char **stack);
void		ft_free_char_pp(char **stack);
bool		ft_quote_switch(char *str, int i, bool single_q, bool double_q);

/*------INPUT------*/
char		*ft_join_input(char *s1, char *s2);
int			recieve_complete_input(t_data *data);

/*------TERMINAL_INPUT------*/
int			ft_terminal_input(t_data *data, int n_single_q, int n_double_q);

/*------TERMINAL_INPUT_UTILS------*/
int	ft_eofsize(char *str, int i, bool single_q, bool double_q);
char	*ft_write_eof(char *str, char *eof, int size, int i);
char	*ft_find_eof(char *str, int i, t_data *data);
bool	ft_compare_eof(char *str, char *eof, t_data *data);


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
int	ft_varsize(t_var *var);
int	save_variables(t_data *data);
int			delete_var(t_data *data, char *var_to_del);

/*------REFORMAT------*/
char		*ft_reformat_input(char *input, t_data *data);


/*------CHECK IF VAR------*/
bool		check_if_we_save_variables(t_data *data);


char	**ft_minishell_split(char const *s, char c);


/*------TOKEN DETECTION------*/
int	ft_check_token(t_data *data);

/*------INIT------*/
t_data	*data_init(void);
int		init_input_struct(t_data *data);

int	open_input(t_data *data);
int	ft_open_out(char *file, t_data *data, bool trunc);

/*------CLEANUP------*/
void data_cleanup(t_data *data);


/*------PIPES------*/
/* Access */
/* int		ft_file_exists(char *file);
int		ft_read_permission(char *file);
int		ft_write_permission(char *file);
int		ft_infile_permissions(char *file, t_info *commands);
int		ft_outfile_permissions(char *file, t_info *commands); */

/* Command path */
char	*ft_find_command_path(char **envp, char *command, int i);
char	*ft_return_accessible_path(char **available_paths, char *command);
void	ft_free_commands(t_data *data);
t_command	*ft_fill_middle_commands(char **argv, char **envp, int argc);
//t_data	*ft_commands(char **argv, char **envp, int argc);

/* Aid */
void	ft_free_char_pp(char **stack);
int		ft_char_pp_len(char **stack);
void	print_char_pp(char **stack);
int		ft_open_infile(char *file, t_data *data);
int		ft_open_outfile(char *file, t_data *data);
int		ft_file_permissions(char *file1, char *file2, t_data *data);
char	*ft_create_file_name(void);
int		**open_pipes(t_data *data);
void	close_pipes(int	**pipe_fd, t_data *data);

/* Clean up */
void	ft_cleanup(char *in_file, t_data *data);

/* Bonus */
int		pipe_exec_coms(t_data *data);
bool	ft_compare_eof_ind(char *str, char *eof, t_data *data);

/* 
int	recieve_complete_input(t_data *data);
int	ft_check_token(t_data *data);
int	ft_ter_input(t_data *data, int num_single_quote, int num_double_quote, int j);
int	ft_get_ter_input(t_data *data, char *eof);
int	ft_save_until_eof(t_data *data);
char	*ft_reformat_input(char *input, t_data *data); */



#endif