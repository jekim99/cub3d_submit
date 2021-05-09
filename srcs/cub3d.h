/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeekim <jaeekim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 21:54:48 by jaeekim           #+#    #+#             */
/*   Updated: 2021/05/09 14:55:54 by jaeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define TEXWIDTH 64
# define TEXHEIGHT 64

# ifndef KEY
#  define KEY
#  define K_W 13
#  define K_A 0
#  define K_S 1
#  define K_D 2
#  define K_AR_L 123
#  define K_AR_R 124
#  define K_ESC 53
#  define M_CLK_L 1
# endif

# ifndef IDENTIFIER
#  define IDENTIFIER
#  define I_R 1
#  define I_NO 2
#  define I_SO 3
#  define I_WE 4
#  define I_EA 5
#  define I_S 6
#  define I_F 7
#  define I_C 8
# endif

# ifndef HOOKS
#  define HOOKS
#  define KEY_PRESS 2
#  define KEY_RELEASE 3
#  define DESTROY_NOTIFY 17
# endif

# include "../utils/libft.h"
# include "../minilibx_mms/mlx.h"
# include <math.h>

/*
** map parsing struct
*/
typedef struct	s_map
{
	int		mapstart;
	int		mapend;
	int		maprowmax;
	int		mapcol;
	char	*mapsave;
}				t_map;

typedef struct	s_cub
{
	int		screenwidth;
	int		screenheight;
	char	*texture[5];
	int		floor;
	int		ceiling;

	int		cnt;
	int		save[8];
	t_map	map;
}				t_cub;

typedef struct	s_map_pass
{
	int		i;
	int		j;
	int		maprowmax;
	char	mapsave;
}				t_map_pass;

/*
** argument struct
*/
typedef struct	s_file
{
	char	*filename;
	int		bmp_flag;
	t_cub	cub;
}				t_file;

/*
** raycasting struct
*/
typedef struct	s_img
{
	void	*img;
	int		*data;

	int		size_l;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
}				t_img;

typedef struct	s_spi
{
	double	x;
	double	y;
	int		spritedist;
}				t_spi;

typedef struct	s_info
{
	int		width;
	int		height;
	int		color[2];

	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	movespeed;
	double	rotspeed;

	void	*mlx;
	void	*win;

	t_img	img;

	int		numsprite;
	t_spi	*spi;
	double	*zbuff;

	int		**buff;
	int		texture[5][TEXWIDTH * TEXHEIGHT];
	int		**worldmap;

}				t_info;

/*
** raycasting calc struct
*/

typedef struct	s_wall
{
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	int		map_x;
	int		map_y;
	double	sidedistx;
	double	sidedisty;
	double	deldistx;
	double	deldisty;
	double	pwalldist;
	int		stepx;
	int		stepy;
	int		hit;
	int		side;
	int		lineh;
	int		dstart;
	int		dend;

	int		texnum;
	double	wallx;
	int		tex_x;
	double	steptex;
	double	texpos;
	int		tex_y;
}				t_wall;

typedef struct	s_sprite
{
	double	sp_x;
	double	sp_y;
	double	invdet;
	double	trx;
	double	try;
	int		spritescreenx;
	int		sph;
	int		drawstarty;
	int		drawendy;
	int		spw;
	int		drawstartx;
	int		drawendx;
	int		tex_x;
	int		tex_y;
}				t_sprite;

int				file_check(char *s);
int				flag_check(char *s);
int				arg_check(int argc, char **argv, t_file *file);

t_map			initialization_map(void);
t_cub			initialization_cub(void);
void			skip_space(char *str, int *i);
int				check_str_remain(char *str);
int				error_parse_map(int i);
int				check_split(char *str, char c);

t_cub			get_file(char *argv);

int				check_configuration(char *str, t_cub *cub);
int				check_identifier(char *str);
int				check_map_start(char *str);
int				check_doup_conf(int identifier, t_cub *cub);
int				parse_configuration(int i, char *str, t_cub *cub);

int				r_to_resolution(char *str, t_cub *cub);
char			*tex_to_path(char *str);
int				rgb_to_hex(char *str);
int				rgb_calc(char *split);

int				save_map(char *str, t_cub *cub);

void			set_game(t_cub *cub, t_info *info);

void			load_texture(t_info *info, int *texture,
							char *path, t_img *img);
void			load_texture_array(t_cub *cub, t_info *info);
void			info_initialization(t_cub *cub, t_info *info);

int				**make_map(t_map map, t_info *info);
void			set_player(char c, int i, int j, t_info *info);

int				inside_check(t_map map, int **worldmap);
int				col_check(t_map map, int **worldmap);
int				row_check(t_map map, int **worldmap);
int				map_config_check(t_map map, int **worldmap, t_info *info);
int				map_valid_check(t_map map, t_info *info);

t_spi			*make_sprite_info(t_map map, t_info *info);

void			render_screen(t_info *info);
void			render_draw(t_info *info);
int				render_main_loop(t_info *info);
void			render_calc(t_info *info);

void			floor_casting(t_info *info);

void			wall_calc(int x, t_wall *wall, t_info *info);
void			wall_set_step(t_wall *wall, t_info *info);
void			wall_dda(t_wall *wall, t_info *info);
void			wall_dist(t_wall *wall, t_info *info);
void			wall_texture(t_wall *wall, t_info *info);
void			wall_texture_cast(t_wall *wall, t_info *info, int x);
void			wall_casting(t_info *info);

void			sort_sprites(t_spi *spi, int numsprite);

void			sprite_calc(t_sprite *sp, t_info *info, int i);
void			sprite_vert_loop(t_sprite *sp, t_info *info);
void			sprite_casting(t_info *info);

void			game_interaction(t_info *info);

int				key_press(int key, t_info *info);
void			key_press_ws(int key, t_info *info);
void			key_press_ad(int key, t_info *info);
void			key_press_rotate(int key, t_info *info);
int				key_release(int key);
int				button_click(void);

int				save_bitmap(t_info *info);
void			bitmap_int_shift(unsigned char *s, int value);
void			save_bitmap_header(t_info *info, int fd, int p);
void			save_bitmap_data(t_info *info, int fd, int p);

#endif
