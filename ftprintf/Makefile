# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/28 22:44:05 by sutku             #+#    #+#              #
#    Updated: 2023/01/24 18:26:54 by sutku            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

SRCS			=	pf_putstr_fd.c ft_decimal.c ft_hexadecimal.c \
					ft_pointer.c ft_printf.c ft_putchar.c ft_uns_decimal.c \

OBJS			= $(SRCS:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -I.

NAME			= libftprintf.a

all:			$(NAME)

$(NAME):		$(OBJS)
				ar rcs $(NAME) $(OBJS)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re