/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 04:45:55 by cdahlhof          #+#    #+#             */
/*   Updated: 2025/08/10 06:09:38 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H

#include <sys/types.h>
#include <dirent.h>

# include "../ft_libft/inc/libft.h"

typedef struct	s_ls_vars {
	t_list			*dirs;
	bool			option_l;
	bool			option_a;
	bool			option_r;
	bool			option_t;
	bool			option_R;
	unsigned char	return_value;
}	t_ls_vars;

t_ls_vars **persist_ls(void);

void	init_ls_vars(int argc, char **argv);

#endif