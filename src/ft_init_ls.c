/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_ls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 05:45:46 by cdahlhof          #+#    #+#             */
/*   Updated: 2025/08/10 06:36:28 by cdahlhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ls.h"

t_ls_vars **persist_ls(void)
{
	static	t_ls_vars *ls_vars;

	return (&ls_vars);
}

static void	read_options(char *arg)
{
	t_ls_vars	*ls_v;
	bool		*arr[5];
	char		*s;

	ls_v = *persist_ls();
	arr[0] = &ls_v->option_l;
	arr[1] = &ls_v->option_a;
	arr[2] = &ls_v->option_r;
	arr[3] = &ls_v->option_t;
	arr[4] = &ls_v->option_R;
	s = "lartR";
	while (arg && 0[arg] && ft_strchr(s, 0[arg]))
	{
		0[arr[ft_strchr(s, 0[arg]) - s]] = true;
		arg++;
	}
}

void	init_ls_vars(int argc, char **argv)
{
	t_ls_vars	*ls_v;
	int			i;
	t_list		*new_dir;

	ls_v = *persist_ls();
	if (!ls_v)
	{
		*persist_ls() = ft_calloc(1, sizeof(t_ls_vars));
		ls_v = *persist_ls();
	}
	i = 1;
	while (i < argc)
	{
		if (argv[i] && argv[i][0] == '-')
			read_options(argv[i] + 1);
		else
		{
			new_dir = ft_lstnew((void *)argv[i]);
			if (!new_dir)
				continue ;
			ft_lstadd_back(&(ls_v->dirs), new_dir);
		}
		i++;
	}
}
