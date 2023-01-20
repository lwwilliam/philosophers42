# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/15 10:16:27 by lwilliam          #+#    #+#              #
#    Updated: 2023/01/20 14:33:14 by lwilliam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = philo.c utils.c utils2.c thread.c

CFLAGS = -Wall -Wextra -Werror

OBJS = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	gcc $(CFLAGS) -fsanitize=thread -o $(NAME) $(OBJS) -lpthread

clean :
	rm -f *.o

fclean : clean
	rm -f $(NAME)

re : fclean all