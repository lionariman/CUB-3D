#ifndef CUB_H
# define CUB_H

// # include "minilibx_mms/mlx.h"
# include "minilibx_opengl/mlx.h"
# include "libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

# define screenWidth 640
# define screenHeight 480
# define SCALE 8

typedef struct	s_textures
{
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	char		*sp_path;
}				t_textures;

typedef struct	s_flags
{
	int			r_flag;
	int			no_flag;
	int			so_flag;
	int			we_flag;
	int			ea_flag;
	int			s_flag;
	int			f_flag;
	int			c_flag;
}				t_flags;

typedef struct	s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef	struct	s_res
{
	int			x;
	int			y;
	int			res_flag;
}				t_res;

typedef struct	s_wndw
{
	void		*mlx;
	void		*win;
	void		*img;
	void		*addr;
	int			line_len;
	int			bppixel;
	int			endian;
}				t_wndw;

typedef	struct	s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct	s_plr
{
	float		x;
	float		y;
	float		dir;
	float		start;
	float		end;
}				t_plr;

typedef struct	s_plane
{
	float		x;
	float		y;
}				t_plane;

typedef	struct	s_all
{
	t_wndw		win;
	t_plr		plr;
	t_point		point;
	t_plane		plane;
	t_textures	txtrs;
	t_flags		flags;
	t_color		color;
	t_res		res;
	char		**map;
	float		f_color;
	float		c_color;
}				t_all;

void	free_maker(char **line);
int		parser(char *str, t_all *all);
int		read_map(char *str, t_list **head);
int		store_map(t_list **head, t_all *all, int size);

#endif