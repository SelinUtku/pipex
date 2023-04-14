# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/09 20:49:06 by sutku             #+#    #+#              #
#    Updated: 2023/04/12 23:43:04 by sutku            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

PIP_SRC		=	pipex.c pipex_utils.c parse.c
PIP_OBJ		=	$(PIP_SRC:.c=.o)

# BONUS_SRC	=	
# BONUS_OBJ	=	$(BONUS_SRC:.c=.o)

LIBFT		=	libft/
LIBFT_LIB	=	libft/libft.a

PRINTF		=	ftprintf/
PRINTF_LIB	=	ftprintf/libftprintf.a

CC		= 	cc
RM		=   rm -f
CFLAGS	=	#-Wall -Werror -Wextra

NAME	=	pipex

DEF_COLOR = \033[0;39m
RED = \033[0;91m
GREEN = \033[0;32m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

all:	$(NAME)

$(NAME): $(PIP_OBJ) $(LIBFT_LIB) $(PRINTF_LIB)
	$(CC) $(CFLAGS) $(PIP_OBJ) $(LIBFT_LIB) $(PRINTF_LIB) -o $(NAME)
	echo "$(CYAN)Pipex compiled successfully$(DEF_COLOR)"

# $(NAME_B): $(BONUS_OBJ) $(PS_OBJ) $(GNL_OBJ) $(PRINTF_LIB) $(LIBFT_LIB)
# 	$(CC) $(CFLAGS) $(BONUS_OBJ) $(PS_OBJ) $(GNL_OBJ) $(PRINTF_LIB) $(LIBFT_LIB) -o $(NAME_B)
# 	echo "Push_Swap_Bonus compiled successfully$(DEF_COLOR)"

$(LIBFT_LIB):
	make bonus -C $(LIBFT) && make clean -C $(LIBFT)
	echo "$(GREEN)Libft compiled successfully$(DEF_COLOR)"

$(PRINTF_LIB):
	make -C $(PRINTF) && make clean -C $(PRINTF)
	echo "$(BLUE)Printf compiled successfully$(DEF_COLOR)"

clean:
	$(RM) $(PIP_OBJ)
	# $(RM) $(BONUS_OBJ)
	$(RM) $(LIBFT_LIB) $(PRINTF_LIB)
	echo "$(MAGENTA)Object-Files are cleaned!"

fclean: clean
	$(RM) $(NAME) 
	# $(RM) $(NAME_B)
	echo "$(MAGENTA)Programs / Libraries are cleaned!"

# bonus: all #$(NAME_B)
	
re: fclean all 

.PHONY: all clean fclean re