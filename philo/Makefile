# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/15 10:16:27 by lwilliam          #+#    #+#              #
#    Updated: 2022/12/27 11:54:07 by lwilliam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = philo.c utils.c thread.c

CFLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(SRC)
	gcc $(CFLAGS) $(SRC) -o $(NAME) -lpthread #-fsanitize=address

clean :
	rm -f *.o

fclean : clean
	rm -f $(NAME)

re : fclean all