# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: keuclide <keuclide@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/21 13:54:22 by keuclide          #+#    #+#              #
#    Updated: 2021/02/11 15:59:06 by keuclide         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub.a
INCL = cub.h
LIBA = ./libft/libft.a
SRCS =	main.c \
		cub.c \
		map.c \
		parser.c \
		raycast.c \
		wallcast.c \
		spritecast.c \
		splitset.c \
		movement.c \
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
	gcc -Imlx -I $(INCL) -c $< -o $@

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

all: $(NAME)

clean:
	rm -rf $(OBJS)
fclean: clean
	rm -rf $(NAME)

re: clean all

.PHONY: all re clean fclean .c.o shit

#---------make-shit---------
shit:
	make
	make mlx
	make clean
	make x
x:
	./a.out map.cub
#res:
#	./a.out map.cub --save
mlx:
	gcc $(SRCS) $(LIBA) -lmlx -framework OpenGL -framework AppKit
gmlx:
	gcc -g $(SRCS) $(LIBA) -lmlx -framework OpenGL -framework AppKit
exmlx:
	gcc lodev.c -lmlx -framework OpenGL -framework AppKit
#---------------------------

#---------make-lib----------
lib:
	make bonus -C libft/
	cp $(LIBA) $(NAME)
lclean:
	make clean -C libft/
lfclean:
	make fclean -C libft/
#---------------------------
