# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/01 19:50:49 by jberredj          #+#    #+#              #
#    Updated: 2021/05/17 14:55:28 by jberredj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub.out
CC			=	clang
OPTI		=	-O3
CFLAGS		=	-Wall -Wextra -Werror $(OPTI)
OS			=	$(shell uname)
DEBUG		=	
HEADERS		=	-I includes/

LIBS		=	libmlx.a libft.a

MAIN		=	main.c exit.c

RENDER		=	bmp_output.c color_utils.c render.c wall_render.c

PARSER		=	parser.c

MLX			=	mlx_utils2.c mlx_utils.c keyboard.c mouse.c window.c

GAME_ENGINE =	map.c player.c ray.c raycaster.c game_loop.c

SRCS	=	$(PARSER) $(MAIN) $(RENDER) $(MLX) $(GAME_ENGINE)
OBJS	=	$(SRCS:.c=.o)

MODULE	=	main render parser mlx game_engine

DEBUG_SRCS =

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
debug: all

main: objs
	$(CC) $(CFLAGS) $(HEADERS) -c $(addprefix srcs/, $(MAIN)) -D $(OS) $(DEBUG)
	mv *.o objs

parser: objs
	$(CC) $(CFLAGS) $(HEADERS) -c $(addprefix srcs/parser/, $(PARSER)) -D $(OS) $(DEBUG)
	mv *.o objs

render: objs
	$(CC) $(CFLAGS) $(HEADERS) -c $(addprefix srcs/render/, $(RENDER)) -D $(OS) $(DEBUG)
	mv *.o objs

mlx: objs
	$(CC) $(CFLAGS) $(HEADERS) -c $(addprefix srcs/mlx/, $(MLX)) -D $(OS) $(DEBUG)
	mv *.o objs

game_engine: objs
	$(CC) $(CFLAGS) $(HEADERS) -c $(addprefix srcs/game_engine/, $(GAME_ENGINE)) -D $(OS) $(DEBUG)
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