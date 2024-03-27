/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffauth-p <ffauth-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:14:43 by pximenez          #+#    #+#             */
/*   Updated: 2024/03/27 12:50:53 by ffauth-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
/*-------INCLUDES-------*/
# include "../libft/ft_printf.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <editline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>


# define TRUE 1
# define FALSE 0

/*------PROTOYPES-------*/
int				main(int argc, char **argv);

#endif