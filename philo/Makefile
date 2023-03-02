# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/14 17:47:18 by rabustam          #+#    #+#              #
#    Updated: 2023/03/02 15:48:10 by rabustam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo

SRC			= main.c philo_utils.c error.c threads.c time.c init.c

OBJ			= main.o philo_utils.o error.o threads.o time.o init.o

FLAGS		= -Wall -Werror -Wextra -g

THFLAG		= -pthread

HEL_GRIND	= valgrind --tool=helgrind

CC			= cc $(FLAGS) $(THFLAG)

all:	$(NAME)

.c.o: $(SRC)
		cc -Wall -Wextra -Werror -c -o $@ $<


$(NAME) : $(OBJ)
	$(CC) $(OBJ) -o $@

clean :
		rm -f *.o
	
fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY:	all clean fclean re