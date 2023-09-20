NAME		= 	cub3D
CC 			= 	gcc

CFLAGS 		= 	-Wall -Wextra -Werror
VPATH 		= 	src

SRC_FILES 	=	main.c \
				exit.c

# object files
OBJ_DIR = obj
OBJ_FILES = $(SRC_FILES:%.c=$(OBJ_DIR)/%.o)

# Libft
LIBFT = libft.a

# Default build
all: $(OBJ_DIR) $(LIBFT) $(NAME)

# obj dir
${OBJ_DIR}	:
				mkdir -p ${OBJ_DIR}

# Libft
$(LIBFT)	:
				make -C libft
# Build 
${NAME}		: 	${OBJ_FILES} 
				$(CC) $(CFLAGS) $^ libft/$(LIBFT) -o $(NAME) -o $@	
				
$(OBJ_FILES): 	$(OBJ_DIR)/%.o : %.c
				$(CC) $(CFLAGS) -c $< -o $@

clean		:
				rm -rf ${OBJ_DIR}
				make fclean -C libft/

fclean		:	clean
				rm -rf ${NAME}
				rm -rf gnl

re 			: 	fclean all

.PHONY 		: 	clean fclean all 