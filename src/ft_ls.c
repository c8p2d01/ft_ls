#include "../inc/ls.h"

void	debug_ls(void)
{
	t_ls_vars	*ls_v;
	t_list		*l;

	ls_v = *persist_ls();
	ft_printf("ls status\n");
	ft_printf("option l is %s\n", ls_v->option_l ? "active" : "off");
	ft_printf("option a is %s\n", ls_v->option_a ? "active" : "off");
	ft_printf("option r is %s\n", ls_v->option_r ? "active" : "off");
	ft_printf("option t is %s\n", ls_v->option_t ? "active" : "off");
	ft_printf("option R is %s\n", ls_v->option_R ? "active" : "off");
	l = ls_v->dirs;
	while (l)
	{
		ft_printf("list contents of directory >%s<\n", (char *)l->content);
		l = l->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	setup_env(env);

	init_ls_vars(argc, argv);

	debug_ls();

	clear_env();
}