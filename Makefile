# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: keuclide <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/21 13:54:22 by keuclide          #+#    #+#              #
#    Updated: 2021/01/24 22:48:35 by keuclide         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub.a
INCL = cub.h
LIBA = ./libft/libft.a
SRCS =	main.c \
		parser.c
OBJS = $(SRCS:.c=.o)

.c.o:
	gcc -Imlx -I $(INCL) -c $< -o $@

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

all: $(NAME)

mlx:
	gcc $(SRCS) $(LIBA) -lmlx -framework OpenGL -framework AppKit

gmlx:
	gcc -g $(SRCS) $(LIBA) -lmlx -framework OpenGL -framework AppKit

clean:
	rm -rf $(OBJS)
fclean: clean
	rm -rf $(NAME)

#---------make-lib---------
lib:
	make bonus -C libft/
	cp $(LIBA) $(NAME)
lclean:
	make clean -C libft/
lfclean:
	make fclean -C libft/
#--------------------------

re: clean all

.PHONY: all re clean fclean .c.o
