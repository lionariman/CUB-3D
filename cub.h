#ifndef CUB_H
# define CUB_H

# include "minilibx_opengl/mlx.h"
# include "libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

# define SCALE 8

typedef	struct	s_spl
{
	char		**mem;
	int			f;
	int			j;
}				t_spl;

typedef struct	s_textures
{
	char		*path_no;
	char		*path_we;
	char		*path_ea;
	char		*path_so;
	char		*path_sp;
}				t_textures;

typedef struct	s_flags
{
	int			r_flag;
	int			f_flag;
	int			c_flag;
	int			p_flag;
	int			s_flag;
}				t_flags;

typedef struct	s_color
{
	int			f;
	int			c;
}				t_color;

typedef	struct	s_res
{
	int			x;
	int			y;
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
	float		posX;
	float		posY;
	float		dirX;
	float		dirY;
}				t_plr;

typedef struct	s_ray
{
	float		dirX;
	float		dirY;
}				t_ray;

typedef struct	s_distd
{
	float		dX;
	float		dY;
}				t_distd;

typedef struct	s_sided
{
	float		dX;
	float		dY;
}				t_sided;

typedef struct	s_plane
{
	float		x;
	float		y;
}				t_plane;

typedef struct	s_step
{
	float		x;
	float		y;
}				t_step;

typedef	struct	s_all
{
	t_wndw		win;
	t_plr		plr;
	t_plane		plane;
	t_textures	txtrs;
	t_flags		flags;
	t_color		color;
	t_res		res;
	t_ray		ray;
	t_distd		delta;
	t_sided		side;
	t_step		step;
	t_point		p;
	char		**map;
	int			mapX;
	int			mapY;
	float		camX;
	int			hit;
	int			sd;
}				t_all;

void	free_maker(char **line);
int		skipspaces(char *line);
int		print_error(char *str);
char	**splitset(const char *s, const char *set);

int		parser(char *str, t_all *all);

int		read_map(int fd, char *line, t_all *all);

int		raycast(t_all *all);

#endif