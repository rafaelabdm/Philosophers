# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rabustam <rabustam@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/14 17:47:18 by rabustam          #+#    #+#              #
#    Updated: 2023/02/16 15:24:03 by rabustam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PHILOSOPHERS	= philosophers

SRC		= main.c philo_utils.c error.c

OBJ		= main.o philo_utils.o error.o

FLAGS	= -Wall -Werror -Wextra -g

THFLAG	= -pthread

CC		= cc $(FLAGS) $(THFLAG)

all:	$(PHILOSOPHERS)

.c.o: $(SRC)
		cc -Wall -Wextra -Werror -c -o $@ $<


$(PHILOSOPHERS) : $(OBJ)
	$(CC) $(OBJ) -o $@

clean :
		rm -f *.o
	
fclean: clean
		rm -f $(PHILOSOPHERS)

re: fclean all

.PHONY:	all clean fclean re