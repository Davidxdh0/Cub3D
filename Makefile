RED=\033[1;31m
GREEN=\033[1;32m
YELLOW=\033[1;33m
BLUE=\033[1;34m
MAGENTA=\033[1;35m
CYAN=\033[1;36m
END=\033[0m

CC = gcc
CFLAGS = -Wall -Werror -Wextra 
NAME = cub3D
LIBFT = libft/libft.a
MLX = MLX42/build/libmlx42.a

DIR_S = srcs
DIR_I = incs
DIR_O = obj

INCS = -I $(DIR_I) -IMLX42/include -I libft/$(DIR_I) 

MAP_PARSER	= 	parser.c \
				validate_map.c \
				parse_types.c \
				parse_util.c \
				file_handling.c \
				new_map_variables.c \
				doors.c

GRAPIHCS	=	bresenham.c \
				minimap.c \
				raycasting.c \
				textures.c

PLAYER		=	keys.c \
				keys2.c \
				movement.c \
				mouse.c \
				player.c

SRCS =		main.c error.c free.c init.c \
			$(addprefix map_parser/, $(MAP_PARSER)) \
			$(addprefix graphics/, $(GRAPIHCS)) \
			$(addprefix player/, $(PLAYER))

OBJS =  ${SRCS:%.c=${DIR_O}/%.o}

ifeq ($(OS), Windows_NT)
	FW_FLAGS := -lglfw3 -lopengl32 -lgdi32
	NAME := so_long.exe
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S), Linux)
		FW_FLAGS := -ldl -Wl,--no-as-needed -lglfw -pthread -lm
	else ifeq ($(UNAME_S), Darwin)
		FW_FLAGS := -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit
	else
		$(error OS: $(OS) is not supported!)
	endif
endif

ifdef DEBUG
CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address
endif

all: ${NAME}

${MLX}:
	@cmake MLX42 -B MLX42/build
	@make -C MLX42/build -j4

${NAME}: ${MLX} ${OBJS} ${DIR_I}/${NAME}.h
	@echo "${BLUE}Compiling libft ${END}"
	@make -s -C libft
	@echo "${BLUE}Compiling ${NAME}${END}"
	@${CC} ${CFLAGS} ${FW_FLAGS} ${OBJS} ${LIBFT} ${MLX} -o ${NAME} 
	@echo "${GREEN}Done!${END}"

${OBJS}: ${DIR_O}/%.o: ${DIR_S}/%.c
	@mkdir -p ${@D}
	@echo "${BLUE}Compiling $<${END}"
	@${CC} ${CFLAGS} ${INCS} -c $< -o $@

debug: fclean
	@make DEBUG=1

test: all
	./testinvalidmaps.sh

run: all
	./cub3D maps/valid/runcub3drun.cub

clean:
	@echo "${RED}Removing objs${END}"
	@rm -rf obj
	@echo "${GREEN}Done!${END}"

fclean: clean
	@make clean -s -C libft 
	@echo "${RED}Removing MLX42${END}"
	@rm -rf MLX42/build
	@echo "${RED}Removing ${NAME}${END}"
	@rm -rf ${NAME}
	@echo "${GREEN}Done!${END}"

re: fclean all

.PHONY: all clean fclean re