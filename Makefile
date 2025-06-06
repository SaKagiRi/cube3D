#------------[MANDATORY]
NAME		= cube3D
CC			= cc
#------------[FLAGS]
CFLAGS		= $(DEBUG_FLAGS) $(W_FLAGS)
DEBUG_FLAGS	= -g3
W_FLAGS		= -Wall -Wextra -Werror -Ofast
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
FILE		= $(MAIN) $(UTIL) $(PARSER) $(DISPLAY)
HEADER		= -I ./include -I $(LIBFT_HEADER) -I $(MLX_HEADER)
LIB			= $(LIBFT_FILE) $(MLX_FILE)
#------------[SUBFILES]
INC_FILE	= cube map game
INC			= $(addprefix include/, $(addsuffix .h, $(INC_FILE)))
#------------[MAIN]
MAIN			= $(addprefix $(MAIN_PATH)/, $(addsuffix .c, $(MAIN_FILE)))
MAIN_PATH		= main
MAIN_FILE		= cube hook
#------------[UTIL]
UTIL			= $(addprefix $(UTIL_PATH)/, $(addsuffix .c, $(UTIL_FILE)))
UTIL_PATH		= util
UTIL_FILE		= get_game in walloc # dalloc
#------------[PARSER]
PARSER			= $(addprefix $(PARSER_PATH)/parser_, $(addsuffix .c, $(PARSER_FILE)))
PARSER_PATH		= parser
PARSER_FILE		= queue tile player
#------------[DISPLAY]
DISPLAY				= $(addprefix $(DISPLAY_PATH)/, $(addsuffix .c, $(DISPLAY_FILE)))
DISPLAY_PATH		= mlx
DISPLAY_FILE		= mlxinit texture cohen drawline print_map key_bind
#------------[PROCESS]
all: lib $(NAME)
$(NAME): $(OBJ)
		@$(CC) $(CFLAGS) $(OBJ) $(LIB) $(HEADER) -o $@
		@printf "\033[38;5;46m\033[1m⟪ Complete ⟫\033[0m\n"
%.o: %.c Makefile $(INC)
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
