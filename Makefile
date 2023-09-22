RED=\033[1;31m
GREEN=\033[1;32m
YELLOW=\033[1;33m
BLUE=\033[1;34m
MAGENTA=\033[1;35m
CYAN=\033[1;36m
END=\033[0m

CC = gcc

ifdef DEBUG
CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address
else
CFLAGS = -Wall -Werror -Wextra
endif
NAME = cub3D
LIBFT = libft/libft.a
MLX = MLX42/build/libmlx42.a -ldl -lglfw -pthread -lm


DIR_S = srcs
DIR_I = incs
DIR_O = obj

INCS = -I $(DIR_I) -I libft/$(DIR_I) -I MLX42/include 

MAP_PARSER = 	parser.c \
				error.c \
				validate_map.c \
				parse_types.c \
				parse_util.c \
				free.c \
				init.c

MINIMAP =		minimap.c

SRCS =		main.c \
			$(addprefix map_parser/, $(MAP_PARSER))\
				$(addprefix minimap/, $(MINIMAP))


LIBMLX	:= ./MLX42
OBJS =  ${SRCS:%.c=${DIR_O}/%.o}

all: libmlx ${NAME}

${MLX}:
	@cmake MLX42 -B MLX42/build
	@make -C MLX42/build -j4

${NAME}: ${MLX} ${OBJS} ${DIR_I}/${NAME}.h
	@make -s -C libft
	@echo "${BLUE}Compiling ${NAME}${END}"
	${CC} ${CFLAGS} ${FW_FLAGS} ${OBJS} ${LIBFT} ${MLX} -o ${NAME} 
	@echo "${GREEN}Done!${END}"

${OBJS}: ${DIR_O}/%.o: ${DIR_S}/%.c
	@mkdir -p ${@D}
	@echo "${BLUE}Compiling $<${END}"
	@${CC} ${CFLAGS} ${INCS} -c $< -o $@

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

run: all
	./cub3D maps/default.cub

run2: all
	./cub3D maps/defaultswitched.cub

clean:
	@make clean -s -C libft 
	@echo "${RED}Removing MLX42${END}"
	@rm -rf MLX42/build
	@echo "${RED}Removing objs${END}"
	@rm -rf obj
	@echo "${GREEN}Done!${END}"

fclean: clean
	@echo "${RED}Removing ${NAME}${END}"
	@rm -rf ${NAME}
	@echo "${GREEN}Done!${END}"

re: fclean all

.PHONY: all clean fclean re

#.DEFAULT_GOAL:=run