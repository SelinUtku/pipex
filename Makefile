# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/09 20:49:06 by sutku             #+#    #+#              #
#    Updated: 2023/04/21 06:34:08 by sutku            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

PIP_SRC		=	pipex_utils.c parse.c pipes_func.c child_process.c \
				find_paths.c pipex_utils2.c
PIP_OBJ		=	$(PIP_SRC:.c=.o)

PIP_MAIN		=	main.c
PIP_MAIN_OBJ	= 	$(PIP_MAIN:.c=.o)

BONUS_SRC	=	pipex_bonus/child_process_b.c pipex_bonus/here_doc_b.c \
				pipex_bonus/main_bonus.c pipex_bonus/pipex_utils_b.c
BONUS_OBJ	=	$(BONUS_SRC:.c=.o)

GNL_SRC		=	gnl/get_next_line_utils.c gnl/get_next_line.c
GNL_OBJ		=	$(GNL_SRC:.c=.o)

LIBFT		=	libft/
LIBFT_LIB	=	libft/libft.a

PRINTF		=	ftprintf/
PRINTF_LIB	=	ftprintf/libftprintf.a

CC		= 	cc
RM		=   rm -f
CFLAGS	=	-Wall -Werror -Wextra

NAME	=	pipex

DEF_COLOR = \033[0;39m
RED = \033[0;91m
GREEN = \033[0;32m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

all: $(NAME)

$(NAME): $(PIP_OBJ) $(PIP_MAIN_OBJ) $(LIBFT_LIB) $(PRINTF_LIB) $(GNL_OBJ)
	$(CC) $(CFLAGS) $(PIP_OBJ) $(PIP_MAIN_OBJ) $(LIBFT_LIB) $(PRINTF_LIB) $(GNL_OBJ) -o $(NAME)
	echo "$(CYAN)Pipex compiled successfully$(DEF_COLOR)"

	$(PIP_OBJ) $(BONUS_OBJ) $(GNL_OBJ) $(PRINTF_LIB) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(PIP_OBJ) $(BONUS_OBJ) $(GNL_OBJ) $(PRINTF_LIB) $(LIBFT_LIB) -o $(NAME)
	echo "$(CYAN)Pipex_Bonus compiled successfully$(DEF_COLOR)"

$(LIBFT_LIB):
	make bonus -C $(LIBFT) && make clean -C $(LIBFT)
	echo "$(GREEN)Libft compiled successfully$(DEF_COLOR)"

$(PRINTF_LIB):
	make -C $(PRINTF) && make clean -C $(PRINTF)
	echo "$(BLUE)Printf compiled successfully$(DEF_COLOR)"

clean:
	$(RM) $(PIP_OBJ) $(PIP_MAIN_OBJ)
	$(RM) $(BONUS_OBJ)
	$(RM) $(LIBFT_LIB) $(PRINTF_LIB) $(GNL_OBJ)
	echo "$(MAGENTA)Object-Files are cleaned$(DEF_COLOR)"

fclean: clean
	$(RM) $(NAME)
	echo "$(MAGENTA)Programs / Libraries are cleaned!"

bonus: $(PIP_OBJ) $(BONUS_OBJ) $(GNL_OBJ) $(PRINTF_LIB) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(PIP_OBJ) $(BONUS_OBJ) $(GNL_OBJ) $(PRINTF_LIB) $(LIBFT_LIB) -o $(NAME)
	echo "$(CYAN)Pipex_Bonus compiled successfully$(DEF_COLOR)"
	
re: fclean all

.PHONY: all clean fclean re bonus