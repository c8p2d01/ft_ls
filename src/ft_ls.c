#include "../inc/ls.h"

void	rec_print_dir(t_ls_dir *root)
{
	t_list			*node;
	DIR				*d;
	struct dirent	*dirr;
	struct stat		fileStat;
	struct passwd	*user;
	struct group 	*grp;

	printf ("%s%s:\n", root->path ? root->path : "", root->name);
	d = opendir(root->path);
	while (d && (dirr = readdir(d)) != NULL)
	{
		stat(dirr->d_name, &fileStat);
		user = getpwuid(fileStat.st_uid);
		grp = getgrgid(fileStat.st_gid);
		printf("%c", S_ISDIR(fileStat.st_mode) ? 'd' : S_ISLNK(fileStat.st_mode) ? 'l' : '-');
		printf("%c", S_IRWXU & fileStat.st_mode ? 'r' : '-');
		printf("%c", S_IWUSR & fileStat.st_mode ? 'w' : '-');
		printf("%c", S_IXUSR & fileStat.st_mode ? 'x' : '-');
		printf("%c", S_IRWXG & fileStat.st_mode ? 'r' : '-');
		printf("%c", S_IWGRP & fileStat.st_mode ? 'w' : '-');
		printf("%c", S_IXGRP & fileStat.st_mode ? 'x' : '-');
		printf("%c", S_IRWXO & fileStat.st_mode ? 'r' : '-');
		printf("%c", S_IWOTH & fileStat.st_mode ? 'w' : '-');
		printf("%c", S_IXOTH & fileStat.st_mode ? 'x' : '-');
		printf(" %ld", fileStat.st_nlink);
		printf(" %s", user->pw_name);
		printf(" %s", grp ? grp->gr_name : "");
		printf(" %5ld", fileStat.st_size);
		printf(" %.12s", ctime(&fileStat.st_mtime) + 4);
		printf(" %s\n", dirr->d_name);
	}
	node = root->contents;
	while (node)
	{
		rec_print_dir(node->content);
		node = node->next;
	}
}

void	debug_ls(void)
{
	t_ls_vars	*ls_v;

	ls_v = *persist_ls();
	//ft_printf("ls status\n");
	//ft_printf("option l is %s\n", ls_v->option_l ? "active" : "off");
	//ft_printf("option a is %s\n", ls_v->option_a ? "active" : "off");
	//ft_printf("option r is %s\n", ls_v->option_r ? "active" : "off");
	//ft_printf("option t is %s\n", ls_v->option_t ? "active" : "off");
	//ft_printf("option R is %s\n", ls_v->option_R ? "active" : "off");
	rec_print_dir(ls_v->root_content->content);
}

int	main(int argc, char **argv, char **env)
{
	t_ls_vars	*ls_v;

	setup_env(env);

	init_ls_vars(argc, argv);

	ls_v = *persist_ls();

	// wenn kein arg path gegeben, also nur im . lsst wird - nur denn muss ./ als path prefix noch gefuegt werden

	//expand_dirs(ls_v->root_content->content);

	debug_ls();

	clear_env();
}