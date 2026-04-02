 #include "../inc/ls.h"

void	ft_lstinsert(t_list	*head, t_list *new)
{
	if (head->next)
	{
		head->next->prev = new;
		new->next = head->next;
	}
	new->prev = head;
	head->next = new;
}

//void	list_contents(t_ls_entrys *current, DIR *d)
//{
//	struct dirent	*dirr;
//	struct stat		fileStat;
//	t_list		*lstnode;

//	(void)current;
//	while ((dirr = readdir(d)) != NULL)
//	{
//		lstat(dirr->d_name, &fileStat);

//		printf("%hhu\t%s\n", dirr->d_type, dirr->d_name);
//		if (S_ISDIR(fileStat.st_mode))
//		{
//			lstnode = ft_lstnew(new_dir(dirr->d_name, current->name));
//			ft_lstadd_back(&current->contents, lstnode);
//			expand_dirs(lstnode);
//		}
//	}
//}

//void	expand_dirs(t_list *begin)
//{
//	t_ls_vars		*ls_v;
//	t_list			*curr;
//	DIR				*d;

//	ls_v = *persist_ls();
//	curr = begin;
//	if (!curr)
//		curr = ls_v->root_content;
//	while (curr)
//	{
//		sleep(1);
//		printf("DEBUG %s\n", ((t_ls_entrys *)curr->content)->name);
//		d = opendir(((t_ls_entrys *)curr->content)->name);
//		curr->content = ft_lstnew(curr->content);
//		if (d)
//		{
//			list_contents(curr->content, d);
//		}
//		// adding error for early error printing
//		curr = curr->next;
//	}
//}

char	*connect_path(char *path, char *dir)
{
	int		len;
	char	*res;


	if (!path)
		return (ft_strdup(dir));
	len = ft_strlen(dir) + ft_strlen(path) + 1;
	if (ft_strlen(path) && path[ft_strlen(path) - 1] != '/')
		len ++;
	res = ft_calloc(len, sizeof(char));
	ft_strlcat(res, path, len);
	if (ft_strlen(path) && path[ft_strlen(path) - 1] != '/')
		*(res + ft_strlen(res)) = '/';
	if (dir)
		ft_strlcat(res, dir, len);
	
	FILE *fi = fopen("CON_PATHS", "w");
	fprintf(fi, "%s\n", res);
	return (res);
}

// void	expand_dirs(t_ls_entry *root)
// {
// 	DIR			*d;
// 	char		*path;
// 	t_ls_entry	*inner;

// 	struct dirent	*dirr;
// 	struct stat		fileStat;

// 	path = connect_path(root);
// 	d = opendir(path);
// 	while (d && (dirr = readdir(d)) != NULL)
// 	{
// 		stat(dirr->d_name, &fileStat);
// 		if (dirr->d_type == DT_DIR)
// 		{
// 			if (!(!ft_strncmp(dirr->d_name, ".", 2) || !ft_strncmp(dirr->d_name, "..", 3)))
// 			{
// 				inner = new_dir(dirr->d_name, path);
// 				ft_lstadd_back(&root->contents, ft_lstnew(inner));
// 				expand_dirs(inner);
// 			}
// 		}
// 	}
// }

int	ls_read(t_ls_entry *entry)
{
	DIR			*d;
	int			i;
	struct dirent	*_dirent;

	struct stat		fileStat;
	struct passwd	*user;
	struct group 	*grp;

	d = opendir(entry->path);
	i = 0;
	while (d && (_dirent = readdir(d)) != NULL)
		i++;
	entry->sub_entries = ft_malloc((i + 1) * sizeof(t_ls_entry*));
	if (!entry->sub_entries)
		return (1);
	closedir(d);
	i = 0;
	d = opendir(entry->path);
	while (d && (_dirent = readdir(d)) != NULL)
	{
		if (lstat(connect_path(entry->path, _dirent->d_name), &fileStat) == -1)
		{
			perror("ls");
			continue;
		}
		user = getpwuid(fileStat.st_uid);
		grp = getgrgid(fileStat.st_gid);

		entry->sub_entries[i] = new_entry();
		if (!entry->sub_entries[i])
			return (1);
		entry->sub_entries[i]->perms = ft_strsmerge(10,
			ft_asprintf("%c", S_ISDIR(fileStat.st_mode) ? 'd' : S_ISLNK(fileStat.st_mode) ? 'l' : '-'),
			ft_asprintf("%c", S_IRWXU & fileStat.st_mode ? 'r' : '-'),
			ft_asprintf("%c", S_IWUSR & fileStat.st_mode ? 'w' : '-'),
			ft_asprintf("%c", S_IXUSR & fileStat.st_mode ? 'x' : '-'),
			ft_asprintf("%c", S_IRWXG & fileStat.st_mode ? 'r' : '-'),
			ft_asprintf("%c", S_IWGRP & fileStat.st_mode ? 'w' : '-'),
			ft_asprintf("%c", S_IXGRP & fileStat.st_mode ? 'x' : '-'),
			ft_asprintf("%c", S_IRWXO & fileStat.st_mode ? 'r' : '-'),
			ft_asprintf("%c", S_IWOTH & fileStat.st_mode ? 'w' : '-'),
			ft_asprintf("%c", S_IXOTH & fileStat.st_mode ? 'x' : '-'));
		entry->sub_entries[i]->links = ft_asprintf("%ld", fileStat.st_nlink);
		entry->sub_entries[i]->user = ft_strdup(user->pw_name);
		entry->sub_entries[i]->group = ft_strdup(grp ? grp->gr_name : "");
		entry->sub_entries[i]->size = fileStat.st_size;
		if (entry->sub_entries[i]->perms[0] != 'd')
			entry->total += fileStat.st_blocks;
		if (ft_log(fileStat.st_size, 10) > entry->sizebuffer)
			entry->sizebuffer = ft_log(fileStat.st_size, 10);
		ft_memcpy(entry->sub_entries[i]->time, &fileStat.st_mtime, sizeof(time_t));
		entry->sub_entries[i]->name = ft_strdup(_dirent->d_name);
		if (S_ISDIR(fileStat.st_mode))
		{
			entry->sub_entries[i]->path = connect_path(entry->path, entry->sub_entries[i]->name);
		}
		else
			entry->sub_entries[i]->path = NULL;
		i++;
	}
	closedir(d);
	entry->sub_entries[i] = NULL;
	ls_sort(entry);
}

bool	flagged_min(int a, int b)
{
	bool reversed;
	t_ls_vars	*ls_v;
	ls_v = *persist_ls();

	reversed = ls_v->option_r;
	if (reversed && a < b)
		return (true);
	if (!reversed && a > b)
		return (true);
	return (false);
}

int	find_next_entry(t_ls_entry **set, int set_size)
{
	int			i;
	t_ls_vars	*ls_v;
	int			r;

	ls_v = *persist_ls();
	i = -1;
	r = -1;
	while (++i < set_size)
	{
		if (!set[i] || r == i)
			continue ;
		if (r < 0)
			r = i;
		if (ls_v->option_f)
			return (r);
		if (ls_v->option_t && flagged_min(*set[r]->time, *set[i]->time))
			r = i;
		else if (flagged_min(ft_strncmp(set[r]->name, set[i]->name, ft_strlen(set[i]->name)), 0))
			r = i;
	}
	return (r);
}

int	ls_sort(t_ls_entry *entry)
{
	int			i;
	int			l;
	int			n;
	t_ls_entry	**ordered;

	i = 0;
	while (entry->sub_entries[i])
		i++;
	ordered = ft_calloc((i + 1), sizeof(t_ls_entry));
	if (!ordered)
		return (1);
	l = 0;
	while (l < i)
	{
		n = find_next_entry(entry->sub_entries, i);
		ordered[l] = entry->sub_entries[n];
		entry->sub_entries[n] = NULL;
		l++;
	}
	ordered[l] = NULL;
	ft_free(entry->sub_entries);
	entry->sub_entries = ordered;
}

int	ls_recurse(t_ls_entry *entry)
{
	t_ls_vars	*ls_v;
	int			i;

	ls_v = *persist_ls();
	if (!ls_v->option_R)
		return (0);
	i = 0;
	while (entry->sub_entries[i])
	{
		if (entry->sub_entries[i]->perms[0] == 'd')
		{
			if (entry->sub_entries[i]->path &&
				ft_strncmp(entry->sub_entries[i]->name, ".", 2) != 0 && 
				ft_strncmp(entry->sub_entries[i]->name, "..", 3) != 0)
			{
				ls_read(entry->sub_entries[i]);
				ls_recurse(entry->sub_entries[i]);
			}
		}
		i++;
	}
}

int	print_flagged(t_ls_entry *entry)
{
	t_ls_vars	*ls_v;
	t_ls_entry	*sub;
	char		*format;
	int			printed;

	ls_v = *persist_ls();
	printed = 0;
	if (ls_v->path && entry->path)
		ft_printf("%s:\n", entry->path);
	if (ls_v->option_l)
		ft_printf("total %li\n", entry->total);
	for (int i = 0; entry && entry->sub_entries[i]; i++)
	{
		sub = entry->sub_entries[i];
		if ((!ls_v->option_a && sub->name[0] == '.') && !ls_v->option_f)
			continue ;
		format = ft_asprintf("%s %s %s %s %%%lild %.16s ", sub->perms, sub->links, sub->user, sub->group, entry->sizebuffer, ctime(sub->time), sub->name);
		if (ls_v->option_l)
			ft_printf(format, sub->size);
		ft_free(format);
		printed = ft_printf("%s%s", sub->name, ls_v->option_l ? "\n" : "  ");
	}
	if (printed)
		ft_printf("\n");
	for (int i = 0; ls_v->option_R && entry && entry->sub_entries[i]; i++)
	{
		sub = entry->sub_entries[i];
		if  ((!ls_v->option_a && sub->name[0] == '.') && !ls_v->option_f)
			continue ;
		if (sub->perms[0] == 'd' && sub->path)
		{
			ft_printf("\n");
			print_flagged(sub);
		}
	}
}
