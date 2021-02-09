#ifndef CUB_H
# define CUB_H

# include "minilibx_opengl/mlx.h"
# include "libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

# define SCALE 8

// # define COLOR
// # define COLOR
// # define COLOR
// # define COLOR
// # define COLOR
// # define COLOR

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
	int			right;
	int			left;
	int			forw;
	int			backw;
	int			movl;
	int			movr;
	int			shift;
	int			closew;
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
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
}				t_plr;

typedef struct	s_ray
{
	double		dir_x;
	double		dir_y;
}				t_ray;

typedef struct	s_deltad
{
	double		dx;
	double		dy;
}				t_deltad;

typedef struct	s_sided
{
	double		dx;
	double		dy;
}				t_sided;

typedef struct	s_plane
{
	double		x;
	double		y;
}				t_plane;

typedef struct	s_step
{
	int			x;
	int			y;
}				t_step;

typedef struct	s_sp
{
	double		x;
	double		y;
}				t_sp;


typedef	struct	s_all
{
	t_wndw		win;
	t_wndw		tx[5];
	t_plr		plr;
	t_plane		plane;
	t_textures	txtrs;
	t_flags		flags;
	t_color		color;
	t_res		res;
	t_ray		ray;
	t_deltad	delta;
	t_sided		side;
	t_step		step;
	t_sp		sp[500];
	t_point		p;
	int			rgb;
	char		**map;
	double		cam_x;
	double		p_wall_d;
	double		wall_x;
	double		zstep;
	double		tex_pos;
	double		mspeed;
	double		rspeed;
	//------sprite------
	double		inv_d;
	double		trans_x;
	double		trans_y;
	int			spscr_x;
	int			spscr_y;
	int			start_x;
	int			start_y;
	int			end_x;
	int			end_y;
	int			sph;
	int			spw;
	int			st;
	int			d;
	//------------------
	int			tex_x;
	int			tex_y;
	int			l_height;
	int			draw_start;
	int			draw_end;
	int			map_x;
	int			map_y;
	int			hit;
	int			sd;
	int			w;
	int			h;
}				t_all;

void	free_maker(char **line);
int		skipspaces(char *line);
int		print_error(char *str);
char	**splitset(const char *s, const char *set);

int		parser(char *str, t_all *all);

int		read_map(int fd, char *line, t_all *all);

int		raycast(t_all *all);

#endif