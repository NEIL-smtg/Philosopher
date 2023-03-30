NAME		=	phil
BONUS_NAME	=	phil_bonus
FILES		=	main init routine utils routine_utils
B_FILES		=	main init routine utils routine_utils
MAN_DIR		=	philo/
BONUS_DIR	=	philo_bonus/
OBJS_DIR	=	objs/
B_OBJS_DIR	=	bonus_objs/
SRCS		=	$(addprefix $(MAN_DIR), $(addsuffix .c, $(FILES)))
OBJS		=	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))
B_SRCS		=	$(addprefix $(BONUS_DIR), $(addsuffix .c, $(B_FILES)))
B_OBJS		=	$(addprefix $(B_OBJS_DIR), $(addsuffix .o, $(B_FILES)))
CC			=	gcc
FLAGS		=	-Wall -Werror -Wextra
FSAN		=	-fsanitize=address -g3
PTHREAD		=	-pthread
RM			=	rm -rf

all:
	mkdir -p $(OBJS_DIR)
	make $(NAME)

$(OBJS_DIR)%.o:$(MAN_DIR)%.c
	$(CC) $(FLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $(FSAN) $(PTHREAD) -o $(NAME) $(OBJS)

bonus:
	mkdir -p $(B_OBJS_DIR)
	make $(BONUS_NAME)

$(B_OBJS_DIR)%.o:$(BONUS_DIR)%.c
	$(CC) $(FLAGS) -c $< -o $@

$(BONUS_NAME): $(B_OBJS)
	$(CC) $(FLAGS) $(FSAN) -o $(BONUS_NAME) $(B_OBJS)

clean:
	$(RM) $(OBJS_DIR) $(B_OBJS_DIR)

fclean:
	make clean
	$(RM) $(NAME) $(BONUS_NAME)

re:
	make fclean
	make all

be:
	make fclean
	make bonus

norm:
	@norminette -R CheckForbiddenSourceHeader $(MAN_DIR)
	@norminette -R CheckForbiddenSourceHeader $(BONUS_DIR)