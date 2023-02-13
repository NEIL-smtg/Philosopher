NAME		=	philosopher
MAN_FILES	=	main utils init pl_start
MAN_DIR		=	philo/
MOBJS_DIR	=	man_objs/
MAN_SRCS	=	$(addprefix $(MAN_DIR), $(addsuffix .c, $(MAN_FILES)))
MAN_OBJS	=	$(addprefix $(MOBJS_DIR), $(addsuffix .o, $(MAN_FILES)))
GCC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra
FSAN		=	-fsanitize=address -g3
RED			:=	$(shell tput -Txterm setaf 1)
RM			=	-rm -rf

all:
	@mkdir -p $(MOBJS_DIR)
	@make $(NAME)
	@echo "$(RED)philo ready HEHHE..."

$(MOBJS_DIR)%.o : $(MAN_DIR)%.c
	@$(GCC) -c $< -o $@

$(NAME): $(MAN_OBJS)
	@$(GCC) $(CFLAGS) $(MAN_OBJS) -pthread -o $(NAME)

clean:
	@$(RM) $(MOBJS_DIR)

fclean:
	@make clean
	@$(RM) $(NAME)

re:
	@make fclean
	@make all

norm:
	@norminette -R CheckForbiddenSourceHeader $(MAN_SRCS)