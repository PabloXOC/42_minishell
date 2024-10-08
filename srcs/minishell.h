/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 14:09:10 by paxoc01           #+#    #+#             */
/*   Updated: 2024/10/09 01:35:02 by paxoc01          ###   ########.fr       */
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
# include <termios.h>
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

typedef enum e_cases	t_cases;
typedef struct s_var	t_var;
typedef struct s_data	t_data;
typedef struct s_spec	t_spec;
typedef struct s_v		t_v;
extern int				g_exit_status;

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
	AMBIG_REDIRECT
}		t_cases;

typedef struct s_var
{
	char			*var;
	char			*content;
	t_var			*next;
}					t_var;

typedef struct s_info
{
	char		*init_input;
	char		**init_input_split;
	char		*first_line;
	char		*first_line_ref;
	char		**first_line_split;
	char		*search_eof;
	char		*terminal_input;
	char		*final_text;
	char		*final_text_last;
	char		**list_eof;
	int			n_eof;
	char		*first_line_and_final_text;
	char		**text_input;
	char		*first_line_vars;
	bool		*real_eof;
	bool		invalid_token;
	bool		incomplete_input;
	t_spec		*spec;
	t_data		*data;
}				t_info;

typedef struct s_spec
{
	t_info		*input_info;
	t_command	*command_list;
	char		*next_eof;
	int			jj;
	int			n_eof;
	bool		no_commands;
	t_data		*data;
}				t_spec;

typedef struct s_v
{
	int			stdin_cpy;
	int			stdout_cpy;
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
	int			pointer;
	int			input_index;
	int			n_eof_saved;
	int			size_tot;
	int			pos;
	char		quote;
	pid_t		fork_id;
	t_data		*data;
	bool		write_error;

	int			s_q;
	int			d_q;
	int			len;
}				t_v;

typedef struct s_data
{
	char		*user;
	char		*dir;
	char		*entry;
	char		**env;
	t_var		*env_lst;

	t_spec		**spec;
	int			n_semicolons;
	bool		exit;
	bool		control_d_g;
	t_info		*input_info_g;

	t_var		*var;
	t_var		*var_export;
	int			kk;
	bool		fatal_error;
	int			sc_n;
	t_v			*v;
	char		*echo_path;
}				t_data;

typedef enum e_command_code
{
	//ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
}	t_command_code;

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
	EXIT_131 = 131,
}			t_exit_code;

/*------PROTOYPES-------*/
int		main(int argc, char **argv, char **env);
int		minishell(t_data *data);
int		minishell1(t_data *data);
int		minishell_2(t_data *data, t_spec *spec, t_info *info, int ret);

/*------CD-------*/
int		change_dir(t_data *data, t_command *full_com);
int		old_dir(t_data *data, t_command *full_com);
int		home_dir(t_data *data, t_command *full_com);
void	modify_dir_env(t_data *data);

/*------CHECK_IF_SAVE_INPUT-------*/
bool	ft_charcomp(const char *str1, const char *str2);
bool	ft_isalnum_bool(int c);
bool	ft_isspecial(const char *str);
bool	ft_starts_with_number(const char *str);
bool	check_if_we_save_variables(t_info *info);

/*------CLEANUP_UTILS_1-------*/
void	close_all_fds(t_command *command);
void	ft_free_commands(t_data *data, t_command *com);
void	ft_free_specific(t_data *data, t_spec **specific);
void	ft_dataclear(t_data *data);

/*------CLEANUP_UTILS_2-------*/
void	ft_free_input_info2(t_info *info);
void	ft_free_input_info(t_info *info);

/*------CLEANUP-------*/
void	data_cleanup(t_data *data);
void	total_cleanup(t_data *data);

/*------COMMANDS-------*/
int		write_in_command(t_data *data, t_spec *spec, t_info *info, int ret);

/*------COMMANDS2-------*/
int		find_command(t_data *data, t_command *full_com);
int		save_pipelines(t_data *data, t_info *info, t_spec *spec);
void	print_commands(t_data *data);

/*------ECHO-------*/
void	fill_new_var(t_data *d, char *str, int i, char *dst);
int		tot_size(t_data *d, char *str, int s_q, int d_q);
int		change_echo_path(t_command *full_com, t_data *data);

/*------ECHO2-------*/
char	*ft_fillout_var(t_data *d, char *str, int s_q, int d_q);
char	*expand_var(t_data *data, char *text);

/*------ENV-------*/
char	*return_content_var(t_var *var_list, char *text);
void	modify_env(t_data *data, char *var, char *new_cont);
int		print_env(t_data *data);
int		save_env2(char **env, t_var **head, char **el);
t_var	*save_env(char **env);

/*------ENV2-------*/
t_var	*find_env_el(t_data *data, char *name);

/*------EXIT_CODES-------*/
int		exit_codes(int exit_code, t_data *data);
int		exit_codes_main(int exit_code, t_data *data);

/*------EXPAND_SQUIGGLE-------*/
int		expand_squiggle(t_data *data, char ***array, int i);
int		expand_squiggle2(t_data *data, char ***array, int i);

/*------EXPORT-------*/
char	**new_equality(char **equality, t_data *data);
int		export_var(t_data *data, t_command *full_com, t_var **list, int i);
int		export(t_data *data, t_command *full_com, t_var **list, int i);
int		print_export(t_data *data);

/*------EXPORT2-------*/
int		fill_export_list(t_data *data, char *var, char *cont);
int		save_export_el(t_data *data, char *var, char *cont);
void	modify_export(t_data *data, char *var, char *new_cont);
bool	ft_export_isspecial(const char *str);
bool	check_if_we_save_export_var(char *var);

/*------FILES-------*/
int		fill_input_info2(t_data *data, t_info *info, t_command *com, int i);
int		fill_input_info(t_data *data, t_info *info, int i, t_command *com);
int		fill_output_info2(t_data *data, t_info *info, t_command *com, int i);
int		fill_output_info(t_data *data, t_info *info, int i, t_command *com);
int		fill_output_info(t_data *data, t_info *info, int i, t_command *com);

/*------FILES2-------*/
int		create_temp_file(t_command *com, t_data *data);

int		fill_extra_info(t_data *data, t_info *info, int i, t_command *com);

/*------FT_MINISHELL_SPLIT-------*/
char	**ft_minishell_split(char const *s, char c);
int		identify_amb(char *str, t_data *data);

/*------FT_SPLIT_VAR-------*/
char	**ft_split_var(char const *s, char c);

/*------INIT-------*/
int		export_list(t_data *data);
void	ft_reset_vars2(t_data *d);
void	ft_reset_vars(t_data *data);
int		data_init2(t_data *data);
t_data	*data_init(char **env);

/*------INIT2-------*/
int		init_input_struct(t_data *data);

/*------INPUT-------*/
int		ft_copy_until_eof(t_data *data, int i, int j);
int		ft_individual_eof(t_data *data, int i);
int		recieve_complete_input_2(t_data *data);
int		recieve_complete_input(t_data *data);

/*------INPUT2-------*/
char	*init_terminal_input(t_data *data, char *input, int i);
int		first_line_complete_2(t_data *data, int i, int d_q, int s_q);
int		first_line_complete(char *input, t_data *data, int d_q, int s_q);
char	*ft_join_input(char *s1, char *s2);
int		ft_eofsize_total(t_data *data, int i, int j);

/*------INPUT3-------*/
int		ft_control_d_quote(t_data *data);
int		ft_ask_user_for_more_input(t_data *data);
int		ft_combine_fl_ft_2(t_data *data, int i, char **str);
int		ft_combine_fl_ft(t_data *data, int i);

/*------INPUT4-------*/
void	ft_save_until_eof_2(t_data *data, int k, int len, int i);
int		ft_save_until_eof(t_data *data);
int		ft_len_to_eof(t_data *data, int i, int k);
int		found_end_first_line(t_data *data, int i, char *input);

/*------MORE_REFORMATS-------*/
int		ft_count_size_array(char **array);
char	**ft_new_array(t_data *d, char **old_a, char **temp_a, int w_count);
int		ft_expand_first_word(t_data *data, t_command *com);
int		reformat_final(t_data *data, t_spec *spec);

/*------PIPE_ACCESS_FILES-------*/

int		ft_write_permission(char *file);
int		ft_infile_perm(char *file, t_command *commands, t_data *data, int ret);
int		ft_infile_perm2(t_data *data, t_command *commands, char *file);
int		ft_outfile_perm(char *file, t_command *commands, t_data *data);

/*------PIPES_AID-------*/
int		ft_char_pp_len(char **stack);
int		ft_open_infile(char *file, t_command *commands);
int		ft_open_outfile(char *file, t_command *commands);
int		ft_file_exists(char *file);
int		ft_read_permission(char *file);

/*------PIPES_AID2-------*/
char	*ft_create_file_name(t_data *data);
int		**open_pipes(t_data *data);
void	close_pipes(int	**pipe_fd, t_data *data);

/*------PIPES_CLEANUP-------*/
void	ft_infiles_cleanup(t_command *commands);

/*------PIPES_COMMAND_PATH-------*/
char	*ft_return_accessible_path(char **available_paths, char *command);
char	*find_command_path(char *command, t_data *data);

/*------PIPES_ERRORS_COMS-------*/
bool	ft_handle_arg_n(char **command, int n_arg, t_data *data);
bool	ft_check_for_flags(char **command, t_data *data);
bool	ft_command_args_errors(char **command, t_data *data);
int		return_builtin_exit_code(char **command);

/*------PIPES_EXEC_COMS-------*/
int		father_process(int **pipe_fd, int i, t_command *com, t_data *data);
void	exec(t_command *command, t_data *data);
int		pipe_commands(t_command *com, t_data *data, int **pipe_fd, int i);
int		restore_original_in_out(t_data *data);

/*------PIPES_EXEC_COMS2-------*/
int		pipe_exec_coms(t_data *data, int i);
int		exec_commands(t_data *data);

/*------REFORMAT-------*/
char	*ft_reformat_input(char *input, t_data *data);

/*------REFORMAT2-------*/
int		ft_count_sep_char_util(char *input, int i);
int		ft_count_sep_char(char *input, int i, int count);
char	*ft_paste_char(char *output, char *added, int pos, int size);
char	*ft_fill_new_string2(char *input, char *output, t_data *d);

/*------REMOVE_SLASH-------*/
int		ft_size_new(t_data *d, char *old_str, int s_q, int d_q);
int		ft_paste_new_var(t_data *d, char **new_str, char *old_str, int i);
void	ft_make_new_string(t_data *d, char *old_str, char **new_str);
int		ft_reformat_vars(t_data *data, t_info *info, int count, int i);

/*------REMOVE_SLASH2-------*/
void	ft_count_vars(t_data *d, char *str, int i);
int		len_old_var(char *str, int i);

/*------REMOVES_QUOTE_VAR-------*/

int		ft_calc_size(t_data *d, char *old_str, int len);
int		ft_remove_quotes_bar(char ***list, t_data *data);
int		ft_assemble(char **list, t_data *data, char ***new_list, int i);

/*------REMOVES_QUOTE_VAR2-------*/
int		ft_handle_s_quote(t_data *d, char *old_str, int len);
int		ft_handle_d_quote(t_data *d, char *old_str, int len);
int		ft_paste_s_quote(t_data *d, char *old_str, char **str, int i);
int		ft_paste_d_quote(t_data *d, char *old_str, char **str, int i);

/*------SEMICOLON1-------*/
int		ft_complete_specific(t_data *data, int i);
int		ft_assign_eof(t_spec *spec);
void	ft_count_eof(t_spec *spec, int s_q, int d_q);
int		ft_break_semicolons(t_data *data, int i);

/*------SEMICOLON2-------*/
int		ft_pos_semicolon(int n_semi, char *str, int j);
int		ft_size_semicolon(int pos, char *str);
int		ft_copy_text(t_data *data, int size, int start, int semi_pos);
int		ft_split_semicolon(t_data *data, int i);

/*------SEMICOLON3-------*/
int		ft_count_semicolons(t_data *data, int s_q, int d_q);
void	ft_set_to_null(t_spec *spec, t_data *data);
void	ft_set_to_null_2(t_info *i_v, t_data *data, int i);

/*------SIGNAL_HANDLE-------*/
int		signal_handle(void);
void	catch_sigquit(int signum);

/*------TERMINAL_APPERANCE-------*/
int		get_user(t_data *data, char **env);
int		ft_get_dir(t_data *data, char **env);
int		refresh_terminal_entry(t_data *data);
int		terminal_entry_info(t_data *data, char **env);

/*------TERMINAL_INPUT_UTIL-------*/
int		ft_eofsize(char *str, int i, bool single_q, bool double_q);
void	ft_write_eof(char *str, char **eof, int size, int i);
char	*ft_find_eof(char *str, int i, t_data *data);
bool	ft_compare_eof(char *str, char *eof, t_data *data);
bool	ft_compare_eof_ind(char *str, char *eof);

/*------TERMINAL_INPUT_UTIL2-------*/
int		ft_control_d_heredoc(t_info *info_g, int i);

/*------TERMINAL_INPUT-------*/
int		ft_malloc_eof(t_data *data, t_info *info, int i);
int		ft_add_text(t_data *data, t_info *info_g, int i);
int		ft_get_ter_input(t_data *d, t_info *info_g, int i, char *f_line);
int		ft_terminal_input_util(t_data *data, int s_q, int d_q, char *f_line);
int		ft_terminal_input(t_data *data, int s_q, int d_q);

/*------TOKEN_DETECTION_UTIL-------*/
bool	ft_check_next(char **array, char *str, int i);
bool	ft_check_both2(char **array, char *str, int i);
bool	ft_check_both(char **array, char *str, int i);

/*------TOKEN_DETECTION-------*/
int		ft_check_token(t_data *data, t_info *info);

/*------TOKEN_DETECTION2-------*/
int		ft_check_token2(t_data *data, t_info *info);

/*------UNSET-------*/
int		unset_var(t_data *data, t_command *full_com);

/*------UTILS-------*/
bool	ft_empty(char *input);
bool	ft_there_is_equal(char *input);
bool	ft_samestr(const char *s1, const char *s2);
int		ft_count_words(char **argv);
void	print_char_pp(char **stack);

/*------UTILS2-------*/
void	ft_free_char_pp(char **stack);
bool	ft_quote_switch(char *str, int i, bool single_q, bool double_q);
int		ft_control_d(t_data *data);

/*------VARIABLES_UTILS-------*/
t_var	*ft_varnew(char *var, char *content);
int		ft_varsize(t_var *var);
t_var	*ft_varlast(t_var *var);
void	ft_varadd_front(t_var **lst, t_var *new);
void	ft_varadd_middle(t_var **lst, t_var *new);

/*------VARIABLES_UTILS2-------*/
void	ft_varadd_back(t_var **var, t_var *new);
void	ft_vardelone(t_var *var);
void	ft_varsclear(t_var **var);
int		save_new_var(t_var **list, char **equality, t_data *data);
void	print_vars(t_var *list);

/*------VARIABLES-------*/
int		save_var_info(t_data *data, char **equality, t_var **list);
int		ft_search_for_equal(char *str);
int		save_variables(t_data *data, t_info *info, int i);
int		delete_head_var(t_var *vars, t_var *temp_var, t_var **list);
int		delete_middle_var(t_var *vars, t_var *temp_var);

/*------VARIABLES2-------*/
int		delete_var(char *var_to_del, t_var **list);
int		refresh_mysignal_var(t_data *data);
int		refresh_home_var(t_data *data);
int		create_preset_vars(t_data *data);
void	modify_exp_and_env(t_data *data, char *var, char *new_cont);

/*------VARIABLES3-------*/
int		save_existing_var(t_var **list, char **equality, t_data *data);

/*------WRITE-------*/
int		ext_error_i(t_cases case_code, t_data *data);
int		error_i(t_cases case_code, t_data *data);
char	*error_c(t_cases case_code, t_data *data, t_spec *spec);

/*------PROTOYPES-------*/

#endif