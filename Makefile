# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: crocha-s <crocha-s@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/08 11:07:37 by gcollet           #+#    #+#              #
#    Updated: 2023/06/19 17:14:18 by crocha-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROG	= pipex


SRCS 	= pipex.c utils.c
OBJS 	= ${SRCS:.c=.o}
MAIN	= pipex.c

INCLUDE	= -I .

CC 		= cc
RM		= rm -f
CFLAGS 	= -Wall -Wextra -Werror -g
MAKE 	= make -C
LIBFT_PATH = ../ft_libft
LIBFT = -L ${LIBFT_PATH} -lft

.c.o:		%.o : %.c
					${CC} ${CFLAGS} ${INCLUDE} -c $< -o $(<:.c=.o)

${PROG}:	${OBJS}
					${MAKE} ${LIBFT_PATH} all
					${CC} ${OBJS} ${LIBFT} -o ${PROG}

all: 		${PROG}
					
clean:
					${MAKE} ${LIBFT_PATH} clean
					${RM} ${OBJS}

fclean: 	clean
					${MAKE} ${LIBFT_PATH} fclean
					${RM} ${PROG}
					
re:			fclean all

.PHONY: all clean fclean re