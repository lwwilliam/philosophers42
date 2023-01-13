# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/15 10:16:27 by lwilliam          #+#    #+#              #
#    Updated: 2023/01/13 19:08:19 by lwilliam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = philo.c utils.c thread.c

CFLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(SRC)
	gcc $(CFLAGS) $(SRC) -o $(NAME) -lpthread -fsanitize=thread

clean :
	rm -f *.o

fclean : clean
	rm -f $(NAME)

re : fclean all