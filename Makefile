# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: keuclide <keuclide@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/21 13:54:22 by keuclide          #+#    #+#              #
#    Updated: 2021/02/14 16:35:18 by keuclide         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub.a
INCL = header/
LIBA = ./libft/libft.a
FLGS = -Wall -Wextra -Werror
VPATH = parser engine movement utils bitmap
SRCS =	main.c \
		cub.c \
		map.c \
		parser.c \
		raycast.c \
		wallcast.c \
		spritecast.c \
		splitset.c \
		movement.c \
		sputils.c \
		bitmap.c \
		plrdir.c \
		rotate.c \
		check.c \
		utils.c \
		wasd.c \
		init.c \
		skp.c \
		pix.c

OBJS = $(SRCS:.c=.o)

.c.o:
	gcc $(FLGS) -Imlx -I $(INCL) -c $< -o $@

$(NAME): $(OBJS)
	make -C minilibx/
	make bonus -C libft/
	cp $(LIBA) $(NAME)
#	cp minilibx/libmlx.dylib ./
	ar rc $(NAME) $(OBJS)
	gcc $(FLGS) $(NAME) $(LIBA) -lmlx -framework OpenGL -framework AppKit -o cub3D
	ranlib $(NAME)

all: $(NAME)

clean:
	make clean -C libft/
	rm -rf $(OBJS)
fclean: clean
	make fclean -C libft/
	make clean -C minilibx/
	rm -rf $(NAME)
	rm -rf cub3D
#	rm -rf libmlx.dylib
re: clean all

.PHONY: all re clean fclean .c.o shit