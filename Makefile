#------------[MANDATORY]
NAME		= cube3D
CC			= cc
RM			= rm -rf
MKDIR		= mkdir -p
HEADER		= -I ./include -I $(LIBFT_HEADER) -I $(MLX_HEADER)

OBJ_DIR		= objs
SRC_DIR		= srcs

#------------[FLAGS]
CFLAGS		= $(DEBUG_FLAGS) $(W_FLAGS)
DEBUG_FLAGS	= -g3
W_FLAGS		= #-Wall -Wextra -Werror # -Ofast

#------------[LIBRARY]
LIB			= $(LIBFT_FILE) $(MLX_FILE)

LIBFT_DIR	= lib/KML
LIBFT_FILE	= $(LIBFT_DIR)/kml.a
LIBFT_HEADER= $(LIBFT_DIR)/include

MLX_DIR		= lib/MLX42
MLX_FILE	= $(MLX_DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm
MLX_HEADER	= $(MLX_DIR)/include/MLX42


#------------[OBJECT_AND_SOURCE]
SRC			= $(addprefix $(SRC_DIR)/, $(FILE))
OBJ			=	$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))


#------------[ROOT_FILES]
FILE		= $(UTIL) $(MINIMAP)

#------------[SUBFILES]
MAIN			= $(addprefix $(MAIN_PATH)/, $(addsuffix .c, $(MAIN_FILE)))
MAIN_PATH		= main
MAIN_FILE		= cube hook parser_queue

UTIL			= $(addprefix $(UTIL_PATH)/, $(addsuffix .c, $(UTIL_FILE)))
UTIL_PATH		= util
UTIL_FILE		= get_game in walloc

MINIMAP				= $(addprefix $(MINIMAP_PATH)/, $(addsuffix .c, $(MINIMAP_FILE)))
MINIMAP_PATH		= minimap
MINIMAP_FILE		= main get_t temp_addmap texture
#------------[PROCESS]
all: lib $(NAME)

$(NAME): $(OBJ) ./include/cube.h
		@$(CC) $(CFLAGS) $(OBJ) $(LIB) $(HEADER) -o $@
		@printf "\033[38;5;46m\033[1m⟪ Complete ⟫\033[0m\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c Makefile
	@$(MKDIR) $(dir $@)
	@printf "\033[38;5;226;1m"
	$(CC) $(CFLAGS) -c $< -o $@ $(HEADER)
	@printf "\033[0m"

lib:
	@make -C $(LIBFT_DIR)
	@cmake $(MLX_DIR) -B $(MLX_DIR)/build && make -C $(MLX_DIR)/build -j4

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)
	@rm -rf $(MLX_DIR)/build

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

nix:
	@nix develop --command zsh
.PHONY: all clean fclean re lib
