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

//void	list_contents(t_ls_dirs *current, DIR *d)
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
//		printf("DEBUG %s\n", ((t_ls_dirs *)curr->content)->name);
//		d = opendir(((t_ls_dirs *)curr->content)->name);
//		curr->content = ft_lstnew(curr->content);
//		if (d)
//		{
//			list_contents(curr->content, d);
//		}
//		// adding error for early error printing
//		curr = curr->next;
//	}
//}

char	*connect_path(t_ls_dir *dir)
{
	int		len;
	char	*res;


	if (!dir->path)
		return (ft_strdup(dir->name));
	len = ft_strlen(dir->name) + ft_strlen(dir->path) + 2;
	if (ft_strlen(dir->path) && dir->path[ft_strlen(dir->path) - 1] != '/')
		len ++;
	res = ft_calloc(len, sizeof(char));
	ft_strlcpy(res + ft_strlen(res), dir->path, ft_strlen(dir->path) + 1);
	if (ft_strlen(dir->path) && dir->path[ft_strlen(dir->path) - 1] != '/')
		*(res + ft_strlen(res)) = '/';
	ft_strlcpy(res + ft_strlen(res), dir->name, ft_strlen(dir->name) + 1);
	return (res);
}

void	expand_dirs(t_ls_dir *root)
{
	DIR			*d;
	char		*path;
	t_ls_dir	*inner;

	struct dirent	*dirr;
	struct stat		fileStat;

	path = connect_path(root);
	d = opendir(path);
	while (d && (dirr = readdir(d)) != NULL)
	{
		stat(dirr->d_name, &fileStat);
		if (dirr->d_type == DT_DIR)
		{
			if (!(!ft_strncmp(dirr->d_name, ".", 2) || !ft_strncmp(dirr->d_name, "..", 3)))
			{
				inner = new_dir(dirr->d_name, path);
				ft_lstadd_back(&root->contents, ft_lstnew(inner));
				expand_dirs(inner);
			}
		}
	}
}




