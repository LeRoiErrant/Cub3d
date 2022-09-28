# **************************************************************************** #
#							PROJECT'S DIRECTORY								   #
# **************************************************************************** #

NAME = cub3d
INCL_DIR	= ./includes
SRC_DIR		= ./src
PARS_DI		= parser
UTILS_DIR	= utils
LIB_DIR		= libft
MLX_DIR		= mlx
TEST_FILE	= ./config/test.cub

# **************************************************************************** #
#						COMPILATION AND LINK FLAGS							   #
# **************************************************************************** #

CC			= cc
CFLAGS		= -O3 -Wall -Wextra -Werror -g -fsanitize=address
LIB_FLAGS	= -L ${INCL_DIR}/$(LIB_DIR) -lft
MLX_FLAGS	= -L ${INCL_DIR}/$(MLX_DIR) -lmlx -framework OpenGL -framework Appkit

# **************************************************************************** #
#								SOURCE FILES								   #
# **************************************************************************** #

DIRS = src
SRC	=	$(foreach dir, $(DIRS), $(wildcard $(dir)/*.c))

OBJS = $(SRC:.c=.o)

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

# **************************************************************************** #
#							MAKEFILE RULES									   #
# **************************************************************************** #

export NOW := $(shell date '+%F_%H:%M:%S')

all: ${NAME}

${NAME}: compil_libs compile ${OBJS} ${OBJS_UTILS} c_done
	@printf "$(YE) Linking...$(RC)\n\n"
	@${CC} ${CFLAGS} ${OBJS} ${OBJS_UTILS} ${LIB_FLAGS} ${MLX_FLAGS} -o ${NAME}
	@printf "$(GR) => Success !$(RC)\n\n" 
	@printf "$(GR)#***********************************#\n"
	@printf "#                                   #\n"
	@printf "#  $(UNDL)Usage:$(RC)$(GR)                           #\n"
	@printf "#  $(REVR)./$(NAME) ./config/<filename>.cub$(RC)$(GR)  #\n"
	@printf "#                                   #\n"
	@printf "#***********************************#$(RC)\n"

bonus: compil_libs compile ${OBJS_BONUS} ${OBJS_UTILS} c_done
	@printf "$(YE) Linking...$(RC)\n\n"
	@${CC} ${CFLAGS} ${LIB_FLAGS} ${OBJS_BONUS} ${OBJS_UTILS} -o ${NAME}
	@printf "$(GR) => Success !$(RC)\n\n" 
	@printf "$(GR)#*************************************************#\n"
	@printf "#                                                 #\n"
	@printf "#  $(UNDL)Usage:$(RC)$(GR)                           #\n"
	@printf "#  $(REVR)TBD$(RC)$(GR)                              #\n"
	@printf "#                                                 #\n"
	@printf "#*************************************************#$(RC)\n"

.c.o:
	@${CC} ${CFLAGS} -o $@ -c $<
	@printf "$(GR)$(REVR) $(RC)"

compil_libs:
	@$(MAKE) all -C $(INCL_DIR)/libft
	@$(MAKE) all -sC $(INCL_DIR)/mlx

compile:
	@echo "\n$(GR)[X] Compiling ${NAME}$(RC)\n"

c_done:
	@echo "$(GR) => 100%$(RC)\n"

clean:
	@printf "\n$(YE)Cleaning...\n"
	@rm -f ${OBJS}
	@rm -f ${OBJS_UTILS}
	@rm -f ${OBJS_BONUS}
	@$(MAKE) clean -C $(INCL_DIR)/libft
	@$(MAKE) clean -C $(INCL_DIR)/mlx
	@printf "\n$(GR)=> Cleaning complete!$(RC)\n\n"

fclean: clean
	@printf "$(YE)Delete ${NAME}...\n"
	@$(MAKE) fclean -C $(INCL_DIR)/libft
	@rm -f ${NAME}
	@printf "\n$(GR)=> ${NAME} deleted!$(RC)\n\n"

git:
	git add .
	git commit -m "Upload by $(LOGNAME) $(NOW)"
	git push

launch: all
	./$(NAME)

re: fclean all

vg: all
	@valgrind --leak-check=full --track-origins=yes ./${NAME} $(TEST_FILE)

test: all
	./${NAME} $(TEST_FILE)

.PHONY: all bonus clean fclean launch re
