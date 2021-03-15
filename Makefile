# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/01 19:50:49 by jberredj          #+#    #+#              #
#    Updated: 2021/03/11 12:02:37 by jberredj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub.out
CC		=	clang
OPTI	=	#-O3
CFLAGS	=	#-Wall -Wextra -Werror $(OPTI)
OS		=	$(shell uname)
DEBUG	=	
HEADERS	=	-I includes/

LIBS	=	libmlx.a libft.a

MAIN	=	main.c

SRCS	=	$(PARSER) $(MAIN) $(OBJECTS)
OBJS	=	$(SRCS:.c=.o)

MODULE	=	main

DEBUG_SRCS =	keyboard.c

$(NAME): $(LIBS) $(MODULE) compile

all: $(NAME)

libmlx.a:
	make -C libs/minilibx-linux/
	cp libs/minilibx-linux/libmlx.a .
	cp libs/minilibx-linux/mlx.h includes/

libft.a:
	make -C libs/libft 
	cp libs/libft/libft.a .

no_opti: OPTI =
no_opti: debug

debug: MODULE += debug_func
debug: SRCS += $(DEBUG_SRCS)
debug: DEBUG = -D DEBUG
debug: CFLAGS += -g #-fsanitize=address 
debug: debug_func all

main: objs
	$(CC) $(CFLAGS) $(HEADERS) -c $(addprefix srcs/, $(MAIN)) -D $(OS) $(DEBUG)
	mv *.o objs

debug_func: objs
	$(CC) $(CFLAGS) $(HEADERS) -c $(addprefix srcs/_debug/, $(DEBUG_SRCS)) $(DEBUG)
	mv *.o objs

compile:
	$(CC) $(CFLAGS) $(HEADERS) $(addprefix objs/, $(OBJS)) $(LIBS) -lXext -lX11 -lm -lbsd -o $(NAME) 

objs:
	mkdir -p objs/

clean:
	rm -rf objs
	rm -rf *.o;

fclean: clean
	rm -rf $(NAME)
	rm -rf $(LIBS)

re: fclean all