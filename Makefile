# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/25 01:50:16 by cmakario          #+#    #+#              #
#    Updated: 2024/03/03 18:39:05 by cmakario         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = gcc

CFLAGS = -Werror -Wall -Wextra 

RM = rm -rf

SRCS = 	pipex.c \
		utils.c

LIBFT_DIR = Libft

LIBFT = $(LIBFT_DIR)/libft.a

$(NAME): $(SRCS) $(LIBFT) 
	$(CC) $(CFLAGS) $(SRCS) $(LIBFT) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)


all : $(NAME)

fclean : clean
	$(RM) $(NAME)
	make fclean -C Libft

clean :
	$(RM) $(NAME)
	make clean -C Libft

re : fclean all

# bonus : clean
# 	make all -C libft
# 	gcc $(CFLAGS) $(SRCS_BONUS) -o $(NAME)





	