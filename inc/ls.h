/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 04:45:55 by cdahlhof          #+#    #+#             */
/*   Updated: 2026/04/01 21:45:59 by cdahlhof         ###   ########.fr       */
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
typedef struct	s_ls_entry {
	char				*path;
	struct s_ls_entry	**sub_entries;
	char				*perms;
	char				*links;
	char				*user;
	char				*group;
	__off_t				size;
	size_t				total;
	__time_t			*time;
	char				*name;
	size_t				sizebuffer;
}	t_ls_entry;

/**
 * root content -> paths given by function arguments
 * directories -> all directories and subdirectories (if applicable)
 * errors -> arguments that were unable to be traced (non directory or missing permission etc)
 */
typedef struct	s_ls_vars {
	char				*pwd;
	struct s_ls_entry	**arg_entries;;
	t_list				*errors;
	bool				option_l;
	bool				option_a;
	bool				option_r;
	bool				option_t;
	bool				option_R;
	bool				option_f;
	bool				color;
	bool				path;
	unsigned char	return_value;
}	t_ls_vars;

#define MAX(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

#define MIN(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _b : _a; })

t_ls_vars **persist_ls(void);

void		init_ls_vars(int argc, char **argv);
t_ls_entry	*new_entry();
void		expand_dirs(t_ls_entry *root);
void			ls_read(t_ls_entry *entry);
bool		flagged_min(int a, int b);
void			ls_sort(t_ls_entry *entry);
void			ls_recurse(t_ls_entry *entry);
void			print_flagged(t_ls_entry *entry);

#endif