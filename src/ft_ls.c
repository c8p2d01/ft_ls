#include "../inc/ls.h"

t_ls_entry	*new_entry()
{
	t_ls_entry	*res;
	__time_t	*t;

	res = ft_malloc(sizeof(t_ls_entry));
	t = ft_malloc(sizeof(__time_t));
	if (!res)
		return (NULL);
	*res = (t_ls_entry) {
		.path = NULL,
		.sub_entries = NULL,
		.perms = NULL,
		.links = 0,
		.user = NULL,
		.group = NULL,
		.size = 0,
		.time = t,
		.name = NULL,
	};
	return (res);
}

int	test_access()
{
	t_ls_vars		*ls_v;
	DIR				*d;
	struct dirent	*_dirent;
	int				c;
	char			*error;
	
	ls_v = *persist_ls();
	for (int i = 0; ls_v->arg_entries[i]; i++)
	{
		d = opendir(ls_v->arg_entries[i]->path);
		if (!d)
		{
			error = ft_asprintf("ft_ls: cannot access '%s'", ls_v->arg_entries[i]->path);
			perror(error);
			free(error);
			c = i + 1;
			while (ls_v->arg_entries[c])
			{
				ls_v->arg_entries[c - 1] = ls_v->arg_entries[c];
				c++;
			}
			ls_v->arg_entries[c - 1] = NULL;
			i--;
		}
	}
}

void	sort_input()
{
	t_ls_vars		*ls_v;
	t_ls_entry		*s;
	t_ls_entry		*t;
	
	ls_v = *persist_ls();
	for (int i = 0; ls_v->arg_entries[i]; i++)
	{
		s = ls_v->arg_entries[i + 1];
		if (!s)
			break;
		if (flagged_min(ft_strncmp(ls_v->arg_entries[i]->path, s->path, ft_strlen(s->path)), 0))
		{
			t = ls_v->arg_entries[i];
			ls_v->arg_entries[i] = s;
			ls_v->arg_entries[i + 1] = t;
			i = 0;
		}
		
	}
}

int	main(int argc, char **argv, char **env)
{
	(void) argc;
	(void) argv;
	(void) env;

	t_ls_vars	*ls_v;
	t_ls_entry	*input;
	int			r_val;

	setup_env(env);
	r_val = 0;
	init_ls_vars(argc, argv);
	r_val = test_access();
	sort_input();

	ls_v = *persist_ls();

	input = new_entry();
	input->sub_entries = ls_v->arg_entries;
	ls_sort(input);
	ls_v->arg_entries = input->sub_entries;

	// rec_print_dir(ls_v->root_content->content);

	for (int i = 0; ls_v->arg_entries[i]; i++)
	{;
		// printf("\e[48;5;21;210;21m%s\e[0m\n\n\n", ls_v->arg_entries[i]->path);
		ls_read(ls_v->arg_entries[i]);
		if (ls_v->option_R)
			ls_recurse(ls_v->arg_entries[i]);
	}
	for (int i = 0; ls_v->arg_entries[i]; i++)
		print_flagged(ls_v->arg_entries[i]);
	
	

	// wenn kein arg path gegeben, also nur im . lsst wird - nur denn muss ./ als path prefix noch gefuegt werden

	//expand_dirs(ls_v->root_content->content);

	// debug_ls();

	clear_env();

	// ft_clean_allocs();
	return (r_val);
}