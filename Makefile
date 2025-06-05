#------------[MANDATORY]
NAME		= cube3D
CC			= cc
#------------[FLAGS]
CFLAGS		= $(DEBUG_FLAGS) $(W_FLAGS)
DEBUG_FLAGS	= -g3
W_FLAGS		= -Wall -Wextra -Werror # -Ofast
#------------[LIBRARY]
LIBFT_DIR	= ./lib/KML
LIBFT_FILE	= $(LIBFT_DIR)/kml.a
LIBFT_HEADER= $(LIBFT_DIR)/include
MLX_DIR		= ./lib/MLX42
MLX_FILE	= $(MLX_DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm
MLX_HEADER	= $(MLX_DIR)/include/MLX42
#------------[OBJECT_AND_SOURCE]
SRC			= $(addprefix srcs/, $(FILE))
OBJ			= $(SRC:.c=.o)
#------------[ROOT_FILES]
FILE		= $(MAIN) $(UTIL)# TODO: add your module name
HEADER		= -I ./include -I $(LIBFT_HEADER) -I $(MLX_HEADER)
LIB			= $(LIBFT_FILE) $(MLX_FILE)
#------------[SUBFILES]
#------------[MAIN]
MAIN			= $(addprefix $(MAIN_PATH)/, $(addsuffix .c, $(MAIN_FILE)))
MAIN_PATH		= main
MAIN_FILE		= cube hook parser_queue parse_tile
#------------[UTIL]
UTIL			= $(addprefix $(UTIL_PATH)/, $(addsuffix .c, $(UTIL_FILE)))
UTIL_PATH		= util
UTIL_FILE		= get_game in walloc # dalloc
#TODO:
#------------[MODULE]
# MODULE_NAME	= $(addprefix $(MODULE_PATH)/, $(MODULE_FILE))
# MODULE_PATH	= module
# MODULE_FILE	= files.c
#	------------[SUB_MODULE]
#	SUB_MODULE_NAME		= $(addprefix $(SUB_MODULE_PATH)/, $(SUB_MODULE_FILE))
#	SUB_MODULE_PATH		= sub_module
#	SUB_MODULE_FILE		= files.c

#------------[PROCESS]
all: lib $(NAME)
$(NAME): $(OBJ) ./include/cube.h
		@$(CC) $(CFLAGS) $(OBJ) $(LIB) $(HEADER) -o $@
		@printf "\033[38;5;46m\033[1m⟪ Complete ⟫\033[0m\n"
%.o: %.c Makefile
	@printf "\033[38;5;226;1m"
	$(CC) $(CFLAGS) -c $< -o $@ $(HEADER)
	@printf "\033[1A\033[2K"
lib:
	@make -C $(LIBFT_DIR)
	@cmake $(MLX_DIR) -B $(MLX_DIR)/build && make -C $(MLX_DIR)/build -j4
clean:
	@rm -rf $(OBJ)
	@make clean -C $(LIBFT_DIR)
	@rm -rf $(MLX_DIR)/build
fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(LIBFT_DIR)
re: fclean all
nix:
	@nix develop --command zsh
.PHONY: all clean fclean re lib
