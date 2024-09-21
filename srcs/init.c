/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:42:44 by pximenez          #+#    #+#             */
/*   Updated: 2024/09/21 14:28:55 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_list(t_data *data)
{
	t_var	*env_list;
	char	**equality;

	env_list = data->env_lst;
	while (env_list != NULL)
	{
		if (save_export_el(data, env_list->var, env_list->content) != SUCCESS)
			return (MALLOC_ERROR);
		equality = (char **) malloc (3 * sizeof(char *));
		if (equality == NULL)
			return (error_i(MALLOC_ERROR, data));
		equality[2] = NULL;
		equality[0] = ft_strdup(env_list->var);
		equality[1] = ft_strdup(env_list->content);
		if (equality[0] == NULL || equality[1] == NULL)
		{
			ft_free_char_pp(equality);
			return (error_i(MALLOC_ERROR, data));
		}
		save_var_info(data, equality, &data->var);
		env_list = env_list->next;
	}
	return (SUCCESS);
}

void	ft_reset_vars2(t_data *d)
{
	d->v->s_q = 0;
	d->v->d_q = 0;
	d->v->len = 0;
}

void	ft_reset_vars(t_data *data)
{
	data->v->stdin_cpy = STDIN_FILENO;
	data->v->stdout_cpy = STDOUT_FILENO;
	data->v->i = 0;
	data->v->i_ter = 0;
	data->v->j = -1;
	data->v->k = 0;
	data->v->ii = 0;
	data->v->kk = 1;
	data->v->iii = 0;
	data->v->jjj = 0;
	data->v->size_var = 0;
	data->v->jj = 0;
	data->v->kkk = 0;
	data->v->idx_com = 0;
	data->v->pointer = 0;
	data->v->input_index = 0;
	data->v->n_eof_saved = 0;
	data->v->size_tot = 0;
	data->v->quote = 0;
	data->v->fork_id = 0;
	data->v->data = data;
	data->v->write_error = false;
	ft_reset_vars2(data);
}

int	data_init2(t_data *data)
{
	data->kk = 0;
	data->fatal_error = false;
	data->sc_n = 0;
	data->v = NULL;
	data->v = (t_v *) malloc (sizeof (t_v));
	if (data->v == NULL)
		return (error_i(MALLOC_ERROR, data));
	ft_reset_vars(data);
	return (SUCCESS);
}

t_data	*data_init(char **env)
{
	t_data	*data;

	data = (t_data *) malloc (sizeof (t_data));
	if (data == NULL)
		return ((t_data *) error_c(MALLOC_ERROR, data, NULL));
	data->user = NULL;
	data->dir = NULL;
	data->entry = NULL;
	data->env = env;
	data->env_lst = save_env(env);
	if (data->env_lst == NULL)
		return ((t_data *) error_c(MALLOC_ERROR, data, NULL));
	data->var_export = NULL;
	data->var = NULL;
	if (export_list(data) == MALLOC_ERROR)
		return (NULL);
	data->spec = NULL;
	data->n_semicolons = 0;
	data->exit = false;
	data->control_d_g = false;
	data->input_info_g = NULL;
	if (data_init2(data) == MALLOC_ERROR)
		return ((t_data *) error_c(MALLOC_ERROR, data, NULL));
	return (data);
}
