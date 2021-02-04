#include <fcntl.h>
#include <stdio.h>
#include <math.h>
#include "libft/libft.h"
#include "minilibx_opengl/mlx.h"

typedef struct  s_ld
{
    double      pos_x;
    double      pos_y;
    double      dir_x;
    double      dir_y;
    double      plane_x;
    double      plane_y;
    double      camera_x;
    double      ray_dir_x;
    double      ray_dir_y;
	int			width;
	int			height;
    int			x;
	int			y;
    int			map_x;
	int			map_y;
    double      side_dist_x;
    double      side_dist_y;
    double      delta_dist_x;
    double      delta_dist_y;
    double      perp_wall_dist;
    int         step_x;
    int         step_y;
    int         hit;
    int         side;
    int         line_height;
    int         draw_start;
    int         draw_end;
	void		*mlx;
	void		*win;
	void		*img;
	void		*addr;
	int			line_l;
	int			bpp;
	int			en;
	int			forward;
	int			backward;
	int			right;
	int			left;
	int			close_win;
	double		moveSpeed;
	double		rotSpeed;
}               t_ld;

#define map_width 24
#define map_height 24
#define w 640
#define h 480

char worldmap[map_width][map_height] = {
  "111111111111111111111111",
  "100000000000000000000001",
  "100000000000000000000001",
  "100000000000000000000001",
  "100000222220000303030001",
  "100000200020000000005001",
  "100000200020000300030001",
  "100000200020000000000001",
  "100000220220000303030001",
  "100000000000000000000001",
  "100000000000000000000001",
  "100000000000000000000001",
  "111111111111111111000001",
  "100000000000000000000001",
  "100000000000000000000001",
  "100000000000000000000001",
  "144444444000000000000001",
  "140400004000000000000001",
  "140000004000000000000001",
  "140400004000000000000001",
  "140444444000000000000001",
  "140000000000000000000001",
  "144444444000000000000001",
  "111111111111111111111111"
};

void	my_pixel_put(t_ld *ld, int x, int y, int color)
{
    char    *dst;

    dst = ld->addr + (y * ld->line_l + x * (ld->bpp / 8));
    *(unsigned int *)dst = color;
}

void	move_f(t_ld *l)
{
	if (worldmap[(int)l->pos_x + (int)l->dir_x * (int)l->moveSpeed][(int)l->pos_y] != '1')
		l->pos_x += l->dir_x * l->moveSpeed;
	// (worldmap[(int)l->pos_x + (int)l->dir_x * (int)l->moveSpeed][(int)l->pos_y] != 2))
	if (worldmap[(int)l->pos_x][(int)l->pos_y + (int)l->dir_y * (int)l->moveSpeed] != '1')
		l->pos_y += l->dir_y * l->moveSpeed;
	// (worldmap[(int)l->pos_x][(int)l->pos_y + (int)l->dir_y * (int)l->moveSpeed] != 2)) ?
}

void	move_b(t_ld *l)
{
	((worldmap[(int)l->pos_x - (int)l->dir_x * (int)l->moveSpeed][(int)l->pos_y] != 1) ||
	(worldmap[(int)l->pos_x - (int)l->dir_x * (int)l->moveSpeed][(int)l->pos_y] != 2)) ?
	(l->pos_x -= l->dir_x * l->moveSpeed) : 0;
	((worldmap[(int)l->pos_x][(int)l->pos_y - (int)l->dir_y * (int)l->moveSpeed] != 1) ||
	(worldmap[(int)l->pos_x][(int)l->pos_y - (int)l->dir_y * (int)l->moveSpeed] != 2)) ?
	(l->pos_y -= l->dir_y * l->moveSpeed) : 0;
}

void	rotate_r(t_ld *l)
{
	double oldd = l->dir_x;
	double oldp = l->plane_x;
	l->dir_x = l->dir_x * cos(-l->rotSpeed) - l->dir_y * sin(-l->rotSpeed);
	l->dir_y = oldd * sin(-l->rotSpeed) + l->dir_y * cos(-l->rotSpeed);
	l->plane_x = l->plane_x * cos(-l->rotSpeed) - l->plane_y * sin(-l->rotSpeed);
	l->plane_y = oldp * sin(-l->rotSpeed) + l->plane_y * cos(-l->rotSpeed);
}

void	rotate_l(t_ld *l)
{
	double oldd = l->dir_x;
	double oldp = l->plane_x;
	l->dir_x = l->dir_x * cos(l->rotSpeed) - l->dir_y * sin(l->rotSpeed);
	l->dir_y = oldd * sin(l->rotSpeed) + l->dir_y * cos(l->rotSpeed);
	l->plane_x = l->plane_x * cos(l->rotSpeed) - l->plane_y * sin(l->rotSpeed);
	l->plane_y = oldp * sin(l->rotSpeed) + l->plane_y * cos(l->rotSpeed);
}

int 	close_w(void)
{
	printf("you have closed the game\n");
	exit(0);
	return (0);
}

int		movement(t_ld *l)
{
	l->forward == 1 ? move_f(l) : 0;
	l->backward == 1 ? move_b(l) : 0;
	l->right == 1 ? rotate_r(l) : 0;
	l->left == 1 ? rotate_l(l) : 0;
	l->close_win == 1 ? close_w() : 0;
	return (0);
}

int		pressed(int k, t_ld *l)
{
	k == 2 ? l->right = 1 : 0;
	k == 0 ? l->left = 1 : 0;
	k == 13 ? l->forward = 1 : 0;
	k == 1 ? l->backward = 1 : 0;
	k == 53 ? l->close_win = 1 : 0;
	return (0);
}

int		unpressed(int k, t_ld *l)
{
	k == 2 ? l->right = 0 : 0;
	k == 0 ? l->left = 0 : 0;
	k == 13 ? l->forward = 0 : 0;
	k == 1 ? l->backward = 0 : 0;
	return (0);
}

int		cube(t_ld *ld)
{
	ld->img = mlx_new_image(ld->mlx, w, h);
    ld->addr = mlx_get_data_addr(ld->img, &ld->bpp, &ld->line_l, &ld->en);
	movement(ld);
	ld->x = 0;
    while (ld->x < w)
    {
        ld->camera_x = 2 * ld->x / (double)w - 1;
        ld->ray_dir_x = ld->dir_x + ld->plane_x * ld->camera_x;
        ld->ray_dir_y = ld->dir_y + ld->plane_y * ld->camera_x;
        ld->map_x = (int)ld->pos_x;
        ld->map_y = (int)ld->pos_y;

        ld->delta_dist_x = fabs(1 / ld->ray_dir_x);
        ld->delta_dist_y = fabs(1 / ld->ray_dir_y);

        ld->hit = 0;
        if (ld->ray_dir_x < 0)
        {
            ld->step_x = -1;
            ld->side_dist_x = (ld->pos_x - ld->map_x) * ld->delta_dist_x;
        }
        else
        {
            ld->step_x = 1;
            ld->side_dist_x = (ld->map_x + 1.0 - ld->pos_x) * ld->delta_dist_x;
        }
        if (ld->ray_dir_y < 0)
        {
            ld->step_y = -1;
            ld->side_dist_y = (ld->pos_y - ld->map_y) * ld->delta_dist_y;
        }
        else
        {
            ld->step_y = 1;
            ld->side_dist_y = (ld->map_y + 1.0 - ld->pos_y) * ld->delta_dist_y;
        }
        while (ld->hit == 0)
        {
            if (ld->side_dist_x < ld->side_dist_y)
            {
                ld->side_dist_x += ld->delta_dist_x;
                ld->map_x += ld->step_x;
                ld->side = 0;
            }
            else
            {
                ld->side_dist_y += ld->delta_dist_y;
                ld->map_y += ld->step_y;
                ld->side = 1;
            }
            if (worldmap[ld->map_y][ld->map_x] == '1')
                ld->hit = 1;
        }
        if (ld->side == 0)
            ld->perp_wall_dist = (ld->map_x - ld->pos_x + (1 - ld->step_x) / 2) / ld->ray_dir_x;
        else
            ld->perp_wall_dist = (ld->map_y - ld->pos_y + (1 - ld->step_y) / 2) / ld->ray_dir_y;
        ld->line_height = (int)(h / ld->perp_wall_dist);
        ld->draw_start = -ld->line_height / 2 + h / 2;
        if (ld->draw_start < 0)
            ld->draw_start = 0;
        ld->draw_end = ld->line_height / 2 + h / 2;
        if (ld->draw_end >= h)
            ld->draw_end = h - 1;
        while (ld->draw_start < ld->draw_end)
        {
            my_pixel_put(ld, ld->x, ld->draw_start, 0x00FFFF);
            ld->draw_start++;
        }
        ld->x++;
    }
	mlx_put_image_to_window(ld->mlx, ld->win, ld->img, 0, 0);
	mlx_destroy_image(ld->mlx, ld->img);
	return (0);
}

int main(void)
{
    t_ld ld;
	ld.pos_x = 5;
	ld.pos_y = 5;
	ld.dir_x = 1;
	ld.dir_y = 0;
	ld.plane_x = 0;
	ld.plane_y = 0.66;
	ld.moveSpeed = 0.1;
	ld.rotSpeed = 0.1;

    ld.mlx = mlx_init();
	ld.win = mlx_new_window(ld.mlx, w, h, "maze");

	mlx_hook(ld.win, 2, 0, pressed, &ld);
	mlx_hook(ld.win, 3, 0, unpressed, &ld);
	mlx_hook(ld.win, 17, 0, close_w, &ld);
	mlx_loop_hook(ld.mlx, cube, &ld);
    mlx_loop(ld.mlx);
}