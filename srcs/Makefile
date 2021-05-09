# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaeekim <jaeekim@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/08 23:55:42 by jaeekim           #+#    #+#              #
#    Updated: 2021/05/09 16:03:57 by jaeekim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D

CC		= gcc
CFLAGS 	= -Wall -Wextra -Werror
LIB		= -L. -lmlx -L../utils -lft -framework Metal -framework Metalkit
MLX		= libmlx.dylib

SRCS	= arg_check.c\
cub3d.c\
game_interaction_key.c\
game_interaction.c\
parse_map_config_check.c\
parse_map_config.c\
parse_map_file.c\
parse_map_utils.c\
render_screen_floor.c\
render_screen_sprite.c\
render_screen_wall_calc.c\
render_screen_wall.c\
render_screen.c\
save_bitmap.c\
set_game_init.c\
set_game_map_check.c\
set_game_map.c\
set_game_sprite.c

OBJS	= $(SRCS:.c=.o)

RM		= rm -f

.PHONY:		all clean fclean re bonus libft minilibx

all:		libft minilibx $(NAME)

libft:
			make -C ../utils lib

minilibx:
			make -C ../minilibx_mms
			cp ../minilibx_mms/$(MLX) .

.c.o:
		$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):	$(MLX) $(OBJS)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIB) 

clean:
			$(RM) $(OBJS)
			make -C ../utils clean
			make -C ../minilibx_mms clean

fclean:		clean
			$(RM) $(NAME) $(MLX)
			$(RM) ../utils/libft.a

re:			fclean  all