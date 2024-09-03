/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/09/02 12:51:23 by paxoc01          ###   ########.fr       */
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
#include <termios.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/types.h>
# include <dirent.h>

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
	FAILURE = 10,
	ERROR,
	MALLOC_ERROR,
	EMPTY,
	INVALID_COMMAND,
	INVALID_DIR,
	INVALID_TOKEN,
	OPEN_ERROR,
	CLOSE_ERROR,
	READ_ERROR,
	WRITE_ERROR,
	CONTROL_D,
	NO_COMMANDS,
	INCOMPLETE_INPUT,
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
	char		**first_line_split_ref; //the final first line split with spaces removed slash
	char		*search_eof; //to search through terminal input to find eof
	char		*terminal_input; // beginning of << terminal input
	char		*final_text; //what we will actually use for << input text BAD
	char		*final_text_last; //what we will actually use for << input text GOOD
	char		**list_eof; //list of all the eof to look for
	int			n_eof; //how many eof to look for
	char		*first_line_and_final_text;//first_line + final_text
	char		**text_input; //    text of  < or <<
	bool		*real_eof;
	bool		invalid_token;
	bool		incomplete_input;
}				t_input_var;

typedef struct s_data
{
	char		*user;
	char		*dir;
	char		*entry;
	char		**env;
	t_var		*env_lst;

	int			paired; //to deal with '' ""
	bool		exit; //if command == exit
	bool		control_d;
	int			input_index; //until where have we read the input
	t_input_var	*input_info;
	t_command	*command_list; //list of the commands in the input + command info
	int			stdin_cpy;
	int			stdout_cpy;
	char		*next_eof;
	t_var		*var; //list of all variables
	t_var		*var_export; //list of all export variables
	int			i;
	int			i_ter;
	int			j;
	int			k;
	int			ii;
	int			kk;

	int			iii;
	int			jjj;
	int			size_var;
	int			jj;
	int			kkk;
	int			idx_com;
	int			size;
	int			pointer;
	pid_t		fork_id;
	char		quote;
	//errors
	bool		fatal_error;
	bool		write_error;
}			t_data;

typedef enum e_command_code
{
	//ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
}			t_command_code;

typedef enum e_exit_code
{
	EXIT_0 = 0,
	EXIT_1 = 1,
	EXIT_2 = 2,
	EXIT_8 = 8,
	EXIT_126 = 126,
	EXIT_127 = 127,
	EXIT_128 = 128,
	EXIT_130 = 130,
}			t_exit_code;

extern int g_exit_status;

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
char		*init_terminal_input(t_data *data, char *input, int i);
int			found_end_first_line(t_data *data, int i, char *input);
int			first_line_complete(char *input, t_data *data, int d_q, int s_q);
char		*ft_join_input(char *s1, char *s2);
int			ft_eofsize_total(t_data *data, int i, int j);
void		ft_save_until_eof_2(t_data *data, int k, int len, int i);
int			ft_save_until_eof(t_data *data);
int			ft_len_to_eof(t_data *data, t_input_var *input_info, int i, int k);
int			ft_ask_user_for_more_input(t_data *data);
int			ft_combine_fl_ft(t_data *data, t_input_var *info, int i);
int			found_end_first_line(t_data *data, int i, char *input);

/*------TERMINAL_INPUT------*/
int			ft_terminal_input(t_data *data, int n_single_q, int n_double_q);

/*------TERMINAL_INPUT_UTILS------*/
int			ft_eofsize(char *str, int i, bool single_q, bool double_q);
char		*ft_write_eof(char *str, char *eof, int size, int i);
char		*ft_find_eof(char *str, int i, t_data *data);
bool		ft_compare_eof(char *str, char *eof, t_data *data);
int			ft_control_d_heredoc(t_data *data, t_input_var *info, int i);

/*------COMMANDS------*/
int			find_command(t_data *data, t_command *com, char **env);
int			write_in_command(t_data *data, t_input_var *info);
int			save_pipelines(t_data *data, t_input_var *info);
void		print_commands(t_data *data);

/*------WRITE------*/
int			ft_write_error_i(t_cases case_code, t_data *data);
char		*ft_write_error_c(t_cases case_code, t_data *data);

/*------TERMINAL------*/
int			get_user(t_data *data, char **env);
//int	get_hostname();
int			ft_get_dir(t_data *data, char **env);
int			refresh_terminal_entry(t_data *data);
int			terminal_entry_info(t_data *data, char **env);

/*------VARIABLES------*/
int			save_existing_var(t_var **list, char **equality, t_data *data);
int			save_var_info(t_data *data, char **equality, t_var **list);
int			save_variables(t_data *data, int i);
int			delete_head_var(t_var *vars, t_var *temp_var, t_var **list);
int			delete_middle_var(t_var *vars, t_var *temp_var);
int			delete_var(t_data *data, char *var_to_del, t_var **list);
int			refresh_mysignal_var(t_data *data);
int			refresh_home_var(t_data *data);
int			create_preset_vars(t_data *data);
void		modify_exp_and_env(t_data *data, char *var, char *new_cont);

/*------VARIABLES UTILS------*/
t_var		*ft_varnew(char *var, char *content);
int			ft_varsize(t_var *var);
t_var		*ft_varlast(t_var *var);
void		ft_varadd_front(t_var **lst, t_var *new);
void		ft_varadd_middle(t_var **lst, t_var *new);
void		ft_varadd_back(t_var **var, t_var *new);
void		ft_vardelone(t_var *var);
void		ft_varsclear(t_var **var);
void		print_vars(t_var *list);
int			save_new_var(t_var **list, char **equality, t_data *data);

/*------ENV------*/
t_var		*save_env(char **env);
int			print_env(t_data *data);
void		modify_env(t_data *data, char *var, char *new_cont);
char		*return_content_var(t_var *var_list, char *text);
t_var		*find_env_el(t_data *data, char *name);
//void	change_env_el_content(t_data *data, char *var, char *new_cont);
//void	add_new_env_el(t_data *data, char *var, char *content);

/*------CD------*/
int			change_dir(t_data *data, t_command *full_com);

/*------UNSET------*/
int			unset_var(t_data *data, t_command *full_com);

/*------EXPORT------*/
int			save_export_el(t_data *data, char *var, char *cont);
void		modify_export(t_data *data, char *var, char *new_cont);
int			export_var(t_data *data, t_command *full_com, t_var **list, int i);
int			export(t_data *data, t_command *full_com, t_var **list, int i);
int			export_list(t_data *data);
int			print_export(t_data *data);

/*------ECHO------*/
void		fill_new_var(t_data *d, char *str, int i, char *dst);
int			tot_size(t_data *d, char *str, int single_q);
char		*expand_var(t_data *data, char *text);

/*------REFORMAT------*/
char		*ft_reformat_input(char *input, t_data *data);
int			ft_count_sep_char_util(char *input, int i);
int			ft_count_sep_char(char *input);
char		*ft_paste_char(char *output, char *added, int pos, int size);

/*------CHECK IF VAR------*/
bool		ft_charcomp(const char *str1, const char *str2);
bool		ft_isalnum_bool(int c);
bool		ft_isspecial(const char *str);
bool		ft_starts_with_number(const char *str);
bool		check_if_we_save_variables(t_data *data, t_input_var *info);
char		**ft_minishell_split(char const *s, char c);

/*------TOKEN DETECTION------*/
int			ft_check_token(t_data *data, t_input_var *info);

/*------INIT------*/
t_data		*data_init(char **env);
int			init_input_struct(t_data *data);

int			open_input(t_data *data);
int			ft_open_out(char *file, t_data *data, bool trunc);

/*------CLEANUP------*/
void		delete_commands(t_data *data);
void		data_cleanup(t_data *data);
void		total_cleanup(t_data *data);

/*------PIPES------*/
/* Access */
int			ft_file_exists(char *file);
int			ft_read_permission(char *file);
int			ft_write_permission(char *file);
int			ft_infile_perm(char *file, t_command *commands, t_data *data);
int			ft_outfile_perm(char *file, t_command *commands, t_data *data);

/* Command path */
char		*find_command_path(char **envp, char *command, int i, t_data *data);
char		*ft_return_accessible_path(char **available_paths, char *command);

/* Aid */
void		ft_free_char_pp(char **stack);
int			ft_char_pp_len(char **stack);
void		print_char_pp(char **stack);
int			ft_open_infile(char *file, t_command *command);
int			ft_open_outfile(char *file, t_command *command);
int			ft_file_permissions(t_command *command);
void		close_all_fds(t_command *command);
char		*ft_create_file_name(t_data *data);
int			**open_pipes(t_data *data);
void		close_pipes(int	**pipe_fd, t_data *data);

/* Clean up */
void		ft_cleanup(char *in_file, t_data *data);
void		ft_infiles_cleanup(t_command *commands);

/* Exec commands */
int			father_process(int **pipe_fd, int i, t_command *com, t_data *data);
void		exec(t_command *command, t_data *data);
int			pipe_commands(t_command *com, t_data *data, int **pipe_fd, int i);
int			restore_original_in_out(t_data *data);
int			pipe_exec_coms(t_data *data, int i);
int			exec_commands(t_data *data);
int			refresh_content_com(t_command *com, t_data *data, int i);
int			refresh_name_com(t_command *com, t_data *data);

/* Errors exec commands */
bool		ft_handle_arg_n(char **command, int n_arg, t_data *data);
bool		ft_check_for_flags(char **command, t_data *data);
bool		ft_command_args_errors(char **command, t_data *data);
int			return_builtin_exit_code(char **command);

bool		ft_compare_eof_ind(char *str, char *eof, t_data *data);

/*------SIGNALS------*/
int			signal_handle(void);
int			ft_control_d(t_data *data);
int			minishell(t_data *data);

/*------FILES------*/
int			create_temp_file(t_command *com, t_data *data);
int			fill_extra_info(t_data *data, int i, t_command *com);

/*------EXIT CODES------*/
int			exit_codes(int exit_code, t_data *data);
int			exit_codes_main(int exit_code, t_data *data);

int			ft_reformat_slash(t_data *data, t_input_var *info);

#endif