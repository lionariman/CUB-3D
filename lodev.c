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
}               t_ld;

#define map_width 24
#define map_height 24
#define w 640
#define h 480

void	cube(t_ld *ld);

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
  "100000000000000000000001",
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

void	rotate(t_ld *ld, float c)
{
	float	dist;

	ld->dir_x = ld->dir_x * cos(c * 5) - ld->dir_y * sin(c * 5);
	ld->dir_y = ld->dir_y * cos(c * 5) - ld->dir_x * sin(c * 5);
	dist = hypot(ld->dir_x, ld->dir_y);
	ld->dir_x /= dist;
	ld->dir_y /= dist;
}

int		key_press(int key, t_ld *ld)
{
	// mlx_clear_window(ld->mlx, ld->win);
	if (key == 123)
		rotate(ld, -1);
	if (key == 124)
		rotate(ld, -1);
	if (key == 53)
		exit(0);
	cube(ld);
	printf("click\n");
	return (0);
}

void	cube(t_ld *ld)
{
	ld->pos_x = 12;
	ld->pos_y = 16;
    ld->dir_x = 1;
	ld->dir_y = 0;
    ld->plane_x = 0;
	ld->plane_y = 0.66;
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
            if (worldmap[ld->map_x][ld->map_y] == '1')
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
            my_pixel_put(ld, ld->x, ld->draw_start, 0xFFFFFF);
            ld->draw_start++;
        }
        ld->x++;
    }
}

int main(void)
{
    t_ld ld;

    ld.mlx = mlx_init();
	ld.win = mlx_new_window(ld.mlx, w, h, "maze");
	ld.img = mlx_new_image(ld.mlx, w, h);
    ld.addr = mlx_get_data_addr(ld.img, &ld.bpp, &ld.line_l, &ld.en);
    cube(&ld);
    mlx_put_image_to_window(ld.mlx, ld.win, ld.img, 0, 0);
    mlx_destroy_image(ld.mlx, ld.img);
	mlx_key_hook(ld.win, key_press, &ld);
    mlx_loop(ld.mlx);
}