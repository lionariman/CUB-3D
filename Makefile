# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: keuclide <keuclide@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/21 13:54:22 by keuclide          #+#    #+#              #
#    Updated: 2021/02/17 10:36:01 by keuclide         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub.a
INCL = header/
LIBA = ./libft/libft.a
DMLX = libmlx.dylib
OMLX = libmlx.a
FLGS = -Wall -Wextra -Werror
FRMK = -framework OpenGL -framework AppKit

VPATH = parser engine movement tools bitmap

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
		qsort.c \
		check.c \
		utils.c \
		wasd.c \
		init.c \
		skp.c \
		pix.c

OBJS = $(SRCS:.c=.o)

.c.o:
	gcc $(FLGS) -I $(INCL) -c $<

$(NAME): $(OBJS)
	make -C miniogl
	make -C minilibx
	make bonus -C libft
	cp $(LIBA) $(NAME)
	cp miniogl/$(OMLX) .
	cp minilibx/$(DMLX) .
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)
	gcc $(FLGS) $(NAME) $(OMLX) $(DMLX) $(FRMK) -o cub3D

all: $(NAME)

dbgr:
	gcc -g $(NAME) $(OMLX) $(DMLX) $(FRMK)

clean:
	make clean -C libft/
	rm -rf $(NAME)
	rm -rf $(OBJS)

fclean: clean
	make fclean -C libft/
	make clean -C miniogl/
	make clean -C minilibx/
	rm -rf $(OMLX)
	rm -rf $(DMLX)
	rm -rf cub3D
	
re: clean all

.PHONY: all re clean fclean .c.o