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
#include <pwd.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <grp.h>
#include <time.h>

# include "../ft_libft/inc/libft.h"

/**
 * name -> name ?_?
 * path -> prior found directories, if none were given itll be a ./
 * contents -> the contents of the directory
 */
typedef struct	s_ls_dir {
	char	*name;
	char	*path;
	t_list	*contents;
}	t_ls_dir;

/**
 * root content -> paths given by function arguments
 * directories -> all directories and subdirectories (if applicable)
 * errors -> arguments that were unable to be traced (non directory or missing permission etc)
 */
typedef struct	s_ls_vars {
	char			*pwd;
	t_list			*root_content;
	t_list			*errors;
	bool			option_l;
	bool			option_a;
	bool			option_r;
	bool			option_t;
	bool			option_R;
	unsigned char	return_value;
}	t_ls_vars;

t_ls_vars **persist_ls(void);

void		init_ls_vars(int argc, char **argv);
t_ls_dir	*new_dir(char *name, char *path);
void		expand_dirs(t_ls_dir *root);

#endif