# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/05 18:30:54 by mmardi            #+#    #+#              #
#    Updated: 2022/10/23 13:51:28 by ntanjaou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = CUB3D

CFLAGS = -Wall -Wextra -Werror

FILES = main.c get_next_line.c get_next_line_utils.c

OBJ = $(FILES:.c=.o)

HEADER =  raycast.h

all: $(NAME)
$(NAME) : $(HEADER) $(OBJ)
	@$(CC) $(CFLAGS) $(FILES)  -lmlx -framework OpenGL -framework AppKit  -o  $(NAME)

clean:
	@rm -rf $(OBJ)
fclean: clean
	@rm -rf $(OBJ) $(NAME)
re: fclean all