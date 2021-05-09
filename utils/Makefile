# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaeekim <jaeekim@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/14 14:17:26 by jaeekim           #+#    #+#              #
#    Updated: 2020/10/26 15:19:59 by jaeekim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
AR		= ar rcs

SRCS	= ft_split.c\
ft_strdup.c\
ft_strjoin.c\
ft_strlcat.c\
ft_strlcpy.c\
ft_strlen.c\
ft_isdigit.c\
get_next_line.c\
ft_isspace.c\
ft_bzero.c

OBJS = $(SRCS:.c=.o)

RM = rm -f

.PHONY:		all clean fclean re bonus

.c.o:
		$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS)
			$(AR) $(NAME) $(OBJS)

clean:
			$(RM) $(OBJS)

all:		$(NAME)

fclean:		clean
			$(RM) $(NAME)

re:			fclean  all

lib:	all clean