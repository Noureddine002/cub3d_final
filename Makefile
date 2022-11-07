NAME = cub3d

NAME_BONUS = cub3d_bonus

HEADER = mandatory/header.h

HEADER_BONUS = bonus/header.h

SRC =	mandatory/main.c \
		mandatory/map_functions.c \
		mandatory/player_functions.c \
		mandatory/back_up_functs2.c \
		mandatory/split.c \
		mandatory/mouvement.c \
		mandatory/rays.c \
		mandatory/casting_rays.c \
		mandatory/casting_rays_utils.c \
		mandatory/build3dWalls.c \
		mandatory/get_texturse_buff.c\
		mandatory/get_texturse_buff_utils.c \
		mandatory/map_parsing/check_extension.c \
		mandatory/map_parsing/helpfunctions.c\
		mandatory/map_parsing/helpfunctions2.c\
		mandatory/map_parsing/get_map.c \
		mandatory/map_parsing/get_final_map.c \
		mandatory/map_parsing/check_map_elements.c \
		mandatory/map_parsing/map_validation.c \
		mandatory/map_parsing/map_validation2.c \
		mandatory/map_parsing/get_struct_info.c \

SRC_BONUS = bonus/main.c \
			bonus/map_functions.c \
			bonus/player_functions.c \
			bonus/back_up_functs.c \
			bonus/back_up_functs2.c \
			bonus/split.c \
			bonus/mouvement.c \
			bonus/rays.c \
			bonus/casting_rays.c \
			bonus/casting_rays_utils.c \
			bonus/build3dWalls.c \
			bonus/get_texturse_buff.c\
			bonus/get_texturse_buff_utils.c \
			bonus/map_parsing/check_extension.c \
			bonus/map_parsing/helpfunctions.c\
			bonus/map_parsing/helpfunctions2.c\
			bonus/map_parsing/get_map.c \
			bonus/map_parsing/get_final_map.c \
			bonus/map_parsing/check_map_elements.c \
			bonus/map_parsing/map_validation.c \
			bonus/map_parsing/map_validation2.c \
			bonus/map_parsing/get_struct_info.c \

OBJ = ${SRC:.c=.o}

OBJ_BONUS = ${SRC_BONUS:.c=.o}

CFLAGS = -Wall -Wextra -Werror -Ofast

CC = gcc

all : $(NAME)

bonus : $(NAME_BONUS)

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS)  -g -Ofast -c $< -o $@

%.o : %.c $(HEADER_BONUS)
	$(CC) $(CFLAGS)  -g -c $< -o $@

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -lmlx -framework OpenGL -framework AppKit $(OBJ)  -Ofast -g -o $(NAME) 

$(NAME_BONUS) : $(OBJ_BONUS)
	$(CC) $(CFLAGS) -lmlx -framework OpenGL -framework AppKit $(OBJ_BONUS) -g -o $(NAME_BONUS) 

clean :
	rm -f $(OBJ)
	rm -f $(OBJ_BONUS)

fclean : clean 
	rm -rf $(NAME)
	rm -rf $(NAME_BONUS)

re : fclean all

re_bonus : fclean bonus