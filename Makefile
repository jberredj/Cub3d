# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/12 17:39:23 by jberredj          #+#    #+#              #
#    Updated: 2022/01/29 12:03:14 by ddiakova         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	cub3D

CC				=	clang
OPTI			=	-O3
CFLAGS			=	-Wall -Werror -Wextra $(OPTI)
LDFLAGS			=	-Llibft -Llibmlx -lXext -lX11 -lm -lbsd

SRC_DIR			= 	srcs
INC_DIR			=	includes
OBJ_DIR			=	objs/

LIBS			=	libft.a libmlx.a

###############################################################################
##								Source files								 ##
###############################################################################

CHECKER				=	loaded_values.c map_valid.c parsed_datas.c spawn_player.c
CHECKER_SRCS		=	$(addprefix srcs/checker/, $(CHECKER))
CHECKER_OBJS		=	$(addprefix objs/checker., $(subst /,., $(CHECKER:.c=.o)))

MAP					=	circle.c process.c square.c
FRAME				=	$(addprefix map/, $(MAP)) \
						player.c render.c wall_render.c wall_ceeling_color.c
RENDER				= 	$(addprefix frame/, $(FRAME))\
						color_utils.c blend_argb.c 
RENDER_SRCS			=	$(addprefix srcs/render/, $(RENDER))
RENDER_OBJS			=	$(addprefix objs/render.,\
						$(subst /,., $(RENDER:.c=.o)))

MAIN				=	main.c exit.c
MAIN_SRCS			=	$(addprefix srcs/, $(MAIN))
MAIN_OBJS			=	$(addprefix objs/, $(subst /,., $(MAIN:.c=.o)))

PARSER				=	create_map_from_raw.c get_cf_color.c get_texture.c \
						parser.c raw_map.c read_cub_file.c res_parser.c selector.c \
						utils.c
PARSER_SRCS			=	$(addprefix srcs/parser/, $(PARSER))
PARSER_OBJS			=	$(addprefix objs/parser., $(subst /,., $(PARSER:.c=.o)))

MLX_UTILS			=	mlx_utils2.c mlx_utils.c keyboard.c mouse.c window.c
MLX_UTILS_SRCS		=	$(addprefix srcs/mlx/, $(MLX_UTILS))
MLX_UTILS_OBJS		=	$(addprefix objs/mlx., $(subst /,., $(MLX_UTILS:.c=.o)))

RAYS				=	create.c free.c set.c utils.c
RAYCASTER			=	compute_rays.c raycaster.c
GAME_ENGINE			=	$(addprefix rays/, $(RAYS)) \
						$(addprefix raycaster/, $(RAYCASTER))\
						map.c player.c game_loop.c is_in_map.c
GAME_ENGINE_SRCS	=	$(addprefix srcs/game_engine/, $(GAME_ENGINE))
GAME_ENGINE_OBJS	=	$(addprefix objs/game_engine., $(subst /,., $(GAME_ENGINE:.c=.o)))

STRUCTS				=	t_coord.h t_flags.h t_game.h t_img.h t_map.h t_mouse.h \
						t_player.h t_ray.h t_window.h
HEADERS				=	$(addprefix structs/, $(STRUCTS))\
						color_utils.h error_code.h exit.h game_engine.h \
						keyboard.h map.h mlx_utils.h mlx.h mouse.h parser.h \
						player.h qwerty.h ray.h raycaster.h render.h \
						wall_render.h

SRCS				=	$(RENDER_SRCS) $(PARSER_SRCS) $(CHECKER_SRCS) $(MLX_UTILS_SRCS) $(GAME_ENGINE_SRCS) \
						$(MAIN_SRCS)
OBJS				=	$(RENDER_OBJS) $(PARSER_OBJS) $(CHECKER_OBJS) $(MLX_UTILS_OBJS) $(GAME_ENGINE_OBJS) \
						$(MAIN_OBJS)

MODULE				=	render parser checker mlx game_engine main

###############################################################################
##							Color output char								 ##
###############################################################################
BLUE			=\033[0;34m
NC				=\033[0m
LIGHT_PURPLE	=\033[1;35m
GREEN			=\033[0;32m
RED				=\033[0;31m

###############################################################################
## 							Mandatory recipes								 ##
###############################################################################

all: $(NAME)

$(NAME): $(OBJ_DIR) $(LIBS) $(OBJS)
	printf "$(BLUE)Linking $(LIGHT_PURPLE)$(NAME) $(BLUE)executable$(NC)\n"
	$(CC) $(CFLAGS) -I $(INC_DIR) $(OBJS) $(LIBS) $(LDFLAGS) -o $(NAME)
	printf "$(GREEN)Completed$(NC)\n"

clean:
	printf "$(RED)Removing objects files$(NC)\n"
	rm -rf objs
	rm -rf *.o;

fclean: clean
	printf "$(RED)Removing $(LIGHT_PURPLE)$(NAME) \
	$(RED)executable\nRemoving libraries$(NC)\n"	
	rm -rf $(NAME)
	rm -rf $(LIBS)

re: fclean all

###############################################################################
## 								Extra recipes								 ##
###############################################################################

define COMPILE
	find ./objs/ -type f -exec touch {} +
	$(foreach source,$?, \
	printf "$(YELLOW)[..]   $(NC) $(LIGHT_PURPLE)$(subst srcs/,,$(source))\
$(NC)\n"; \
	$(CC) -I $(INC_DIR) $(CFLAGS) -c $(source) -o \
$(addprefix $(OBJ_DIR), $(subst /,.,$(subst srcs/,,$(source:.c=.o)))) ; \
	if [ $$? -ne "0" ];\
	then \
		exit 1;\
	fi; \
	norminette $(source) > /dev/null ;\
	if [ $$? -ne "0" ];\
	then \
		printf "\033[F$(RED)[NORM]$(NC) $(LIGHT_PURPLE)\
$(subst srcs/,,$(source))$(NC)\n";\
	else \
		printf "\033[F$(GREEN)[OK]  $(NC) $(LIGHT_PURPLE)\
$(subst srcs/,,$(source))$(NC)\n";\
	fi;)
endef

bonus: CFLAGS += -D BONUS=1
bonus: all

game_engine: $(OBJ_DIR) $(GAME_ENGINE_OBJS)
$(GAME_ENGINE_OBJS): $(GAME_ENGINE_SRCS)
	printf "$(BLUE)Compiling $(LIGHT_PURPLE)game engine $(BLUE)functions$(NC)\n"
	$(COMPILE)

mlx: $(OBJ_DIR) $(MLX_UTILS_OBJS)
$(MLX_UTILS_OBJS): $(MLX_UTILS_SRCS)
	printf "$(BLUE)Compiling $(LIGHT_PURPLE)mlx $(BLUE)functions$(NC)\n"
	$(COMPILE)

parser: $(OBJ_DIR) $(PARSER_OBJS)
$(PARSER_OBJS): $(PARSER_SRCS)
	printf "$(BLUE)Compiling $(LIGHT_PURPLE)parser $(BLUE)functions$(NC)\n"
	$(COMPILE)

checker: $(OBJ_DIR) $(CHECKER_OBJS)
$(CHECKER_OBJS): $(CHECKER_SRCS)
	printf "$(BLUE)Compiling $(LIGHT_PURPLE)$(@^) $(BLUE)functions$(NC)\n"
	$(COMPILE)

render: $(OBJ_DIR) $(RENDER_OBJS)
$(RENDER_OBJS): $(RENDER_SRCS)
	printf "$(BLUE)Compiling $(LIGHT_PURPLE)render $(BLUE)functions$(NC)\n"
	$(COMPILE)

main: $(OBJ_DIR) $(MAIN_OBJS)
$(MAIN_OBJS): $(MAIN_SRCS)
	printf "$(BLUE)Compiling $(LIGHT_PURPLE)main $(BLUE)functions$(NC)\n"
	$(COMPILE)

ffclean: fclean
	make -C libs/libft fclean
	make -C libs/minilibx-linux clean

$(SRCS): $(addprefix $(INC_DIR)/, $(HEADERS))
 
libft.a:
	make -C libs/libft ft_io ft_string ft_to ft_ctype get_next_line lib
	cp libs/libft/libft.a .

libmlx.a:
	make -C libs/minilibx-linux
	cp libs/minilibx-linux/libmlx.a .

debug: CFLAGS = -g -D DEBUG 
debug: all

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

valgrind:
	valgrind  --trace-children=yes --suppressions=./ignoreliberror  --leak-check=full --show-leak-kinds=all ./$(NAME)

.SILENT:

commit_all_files: ffclean
	git add .
	git commit

###############################################################################
## 								Norm recipe									 ##
###############################################################################

norm:
	printf "$(BLUE)Checking norm$(NC)\n"
	norminette $(SRCS) $(addprefix $(INC_DIR)/, $(filter-out mlx.h, $(HEADERS))) \
	; if [ "$$?" -ne "0" ]; then printf "$(RED)NORM ERROR$(NC)\n"; \
	else printf "$(GREEN)NORM OK$(NC)\n";fi
