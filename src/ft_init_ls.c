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

static bool	read_options(char *arg)
{
	t_ls_vars	*ls_v;
	bool		*arr[6];
	bool		was_flag;
	char		*s;

	ls_v = *persist_ls();
	arr[0] = &ls_v->option_l;
	arr[1] = &ls_v->option_a;
	arr[2] = &ls_v->option_r;
	arr[3] = &ls_v->option_t;
	arr[4] = &ls_v->option_R;
	arr[5] = &ls_v->option_f;
	s = "lartRf";
	was_flag = false;
	while (arg && arg[0] && ft_strchr(s, arg[0]))
	{
		*arr[ft_strchr(s, arg[0]) - s] = true;
		arg++;
		was_flag = true;
	}
	if (ft_strncmp(arg, "-color=auto", 12) == 0)
		return ((ls_v->color = true));
	if (!was_flag)
		return (false);
	return (true);
}

void	init_ls_vars(int argc, char **argv)
{
	t_ls_vars		*ls_v;
	int				i;
	int				j;
	t_list			*n_entry;
	t_ls_entry		*e;

	ls_v = *persist_ls();
	if (!ls_v)
	{
		*persist_ls() = ft_calloc(1, sizeof(t_ls_vars));
		ls_v = *persist_ls();
	}
	i = 1;
	j = 0;
	ls_v->arg_entries = ft_calloc(argc, sizeof(t_ls_entry *));
	while (i < argc)
	{
		if (argv[i] && argv[i][0] == '-' && read_options(argv[i] + 1))
			;
		else
		{
			ls_v->arg_entries[j] = new_entry();
			if (!ls_v->arg_entries[j])
				continue ;
			ls_v->arg_entries[j]->path = ft_strdup(argv[i]);
			j++;
		}
		i++;
	}
	if (j > 1 || ls_v->option_R)
		ls_v->path = true;
	ls_v->pwd = get_value("PWD");
	if (ls_v->arg_entries[0])
		return ;
	ls_v->arg_entries[0] = new_entry();
	ls_v->arg_entries[0]->path = ft_strdup(".");
}
