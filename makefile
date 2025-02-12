CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -framework Cocoa -framework OpenGL -framework IOKit
SRCS = fdf_shit.c parse_map.c get_next_line/get_next_line_bonus.c get_next_line/get_next_line_utils_bonus.c
OBJS = $(SRCS:.c=.o)
NAME = fdf
LIBFT_DIR = ./libft
FT_PRINTF_DIR = ./ft_printf
LIBFT = $(LIBFT_DIR)/libft.a
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a
MLX42 = ./MLX42/build/libmlx42.a
LIBGLFW3 = ./MLX42/libglfw3.a

all: $(LIBFT) $(FT_PRINTF) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(FT_PRINTF):
	$(MAKE) -C $(FT_PRINTF_DIR)

$(NAME): $(OBJS) $(LIBFT) $(FT_PRINTF) $(MLX42) $(LIBGLFW3)
	$(CC) $(CFLAGS) $(MLX_FLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(FT_PRINTF) $(MLX42) $(LIBGLFW3)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(FT_PRINTF_DIR) clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(FT_PRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re