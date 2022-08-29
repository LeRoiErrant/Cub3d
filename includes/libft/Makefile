# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/26 11:47:13 by 0xNino            #+#    #+#              #
#    Updated: 2022/04/20 15:37:58 by 0xNino           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a
DIRS	=	additional dlst gnl libc lst math printf sort utils
SRCS	=	$(foreach dir, $(DIRS), $(wildcard $(dir)/*.c))
OBJS	=	$(SRCS:.c=.o)

CC			= gcc
RM			= rm -f
CFLAGS		= -Wall -Wextra -Werror -I.

all:		$(NAME)

$(NAME):	compile $(OBJS) c_done
			@ar rcs $(NAME) $(OBJS)
			@printf "\n$(GR) => Success !$(RC)\n\n" 

.c.o:
			@${CC} ${CFLAGS} -o $@ -c $<
			@printf "$(GR)$(REVR) $(RC)"

compile:
			@echo "\n$(GR)[X] Compiling ${NAME}$(RC)\n"

c_done:
			@echo "$(GR) => 100%$(RC)\n"

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

launch:		all
			./$(NAME)

re:			fclean $(NAME)

.PHONY:		all clean fclean launch re

# **************************************************************************** #
#								COLORS										   #
# **************************************************************************** #

BOLD = \033[1m
ITAL = \033[3m
UNDL = \033[4m
BLNK = \033[5m
REVR = \033[7m
GR = \033[32;1m
RE = \033[31;1m
YE = \033[33;1m
CY = \033[36;1m
RC = \033[0m