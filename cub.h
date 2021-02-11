#ifndef CUB_H
# define CUB_H

# include "minilibx_opengl/mlx.h"
# include "libft/libft.h"
# include <unistd.h>
# include <stdio.h> // delete!
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
	double		d;
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
	double		inv_d;
	double		trans_x;
	double		trans_y;
	int			spscr_x;
	int			start_x;
	int			start_y;
	int			end_x;
	int			end_y;
	int			sph;
	int			spw;
	int			st;
	int			d;
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

/*
** parser and map checker
*/

int		parser(char *str, t_all *all);
int		read_map(int fd, char *line, t_all *all);

/*
** calling ray, wall and sprite casters
*/

int		cub(t_all *all);

/*
** ray casting
*/

void	ray_pos_dir(t_all *l, int x);
void	step_side_dist(t_all *l);
void	dda_performance(t_all *l);
void	wall_building(t_all *l);

/*
** wall casting
*/

void	tex_coordinates(t_all *l);
void	wall_dye(t_all *l, int x, int i);

/*
** sprite casting
*/

void	trans_sprite(t_all *l, t_sp *sp, int i);
void	lowest_highest_pix(t_all *l);
void	sprite_dye(t_all *l, double *z_buf);
void	find_sprites(t_all *l, t_sp *sp);
void	sort_sprites(t_all *l, t_sp *sp);

/*
** utils
*/

char	**splitset(const char *s, const char *set);
int		check_arg(char *s, char c);
void	free_maker(char **line);
int		skipspaces(char *line);
int		print_error(char *str);
int		num_of_words(char **words);
int		digs(char *word);

/*
** w,a,s,d, right, left and close buttons
*/

void	move_forw(t_all *l);
void	move_back(t_all *l);
void	move_left(t_all *l);
void	move_right(t_all *l);
void	rot_left(t_all *l);
void	rot_right(t_all *l);
int 	close_w(void);

/*
** movement
*/

void	movement(t_all *l);
int		key_press(int k, t_all *l);
int		key_release(int k, t_all *l);

/*
** my minilibx functions
*/

void	pixel_put(t_wndw *data, int x, int y, int color);
int		pixget(t_wndw *tx, int x, int y);

#endif