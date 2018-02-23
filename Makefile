# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbailleu <tbailleu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/08 08:32:57 by tbailleu          #+#    #+#              #
#    Updated: 2018/01/29 16:23:15 by tbailleu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
SRCS_DIR = ./srcs/
INCLUDES_DIR = ./includes ./libft/includes
LIBS = ./libft/libft.a -lmlx
FUNCTIONS = main fdf_map fdf_matrices fdf_draw fdf_hook

FLAGS = -Ofast -Wall -Werror -Wextra -flto -march=native -O3#-g -ggdb -fsanitize=address -fno-omit-frame-pointer -fsanitize=undefined 
FRAMEWORKS = -framework OpenGL -framework AppKit
BINS = $(patsubst %,$(SRCS_DIR)%.o,$(FUNCTIONS))
INCLUDE = $(patsubst %,-I %,$(INCLUDES_DIR))

$(NAME): lib $(BINS)
	@clang $(FLAGS) -o $(NAME) $(BINS) $(LIBS) $(FRAMEWORKS) $(INCLUDES)
	@echo '\033[0;32mMake $(NAME): OK 😃';

lib:
	@make -C libft/

%.o: %.c
	@clang $(FLAGS) -o $@ -c $< $(INCLUDES)

all: $(NAME)

clean:
	@make -C libft/ clean
	@/bin/rm -rf $(BINS)

fclean: clean
	@make -C libft/ fclean
	@find . -type f -name $(NAME) -delete

re: fclean all

rec: all clean

norm:
	$(eval NORM_FILE = $(shell find . -type f -name "*.c" -o -type f -name "*.h"))
	$(eval NORM_ERRNB = $(shell norminette $(NORM_FILE) | grep -c -E '^(Error|Warning)'))
	@if [ $(NORM_ERRNB) -eq 0 ]; then\
		echo '\033[0;32mNorme: OK 😃';\
	else\
		echo '\033[0;31m'$(NORM_ERRNB) 'Error found 😱\033[1;34m';\
		norminette $(NORM_FILE) | grep -B 1 -E '^(Error|Warning)';\
	fi

.PHONY: all clean fclean re norm rec
