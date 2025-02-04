SHELL = /bin/sh

NAME = philo
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -pthread
AR = ar rcs
RM = rm -f
ECHO = echo

SRCS = init.c\
		parsing.c\
		routine.c\
		utils.c\
		main.c

OBJS = $(SRCS:.c=.o)
CURRENT = 0

# Couleurs
DEF_COLOR	=	\033[0m
RED			=	\033[0;91m
GREEN		=	\033[1;92m
YELLOW		=	\033[1;93m
BLUE		=	\033[0;94m
WHITE		=	\033[0;97m
PURPLE		=	\033[0;95m

all: $(NAME)

$(NAME) : $(OBJS)
		@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
		$(eval CURRENT=$(shell echo $$(($(CURRENT)+1))))
		@$(CC) $(CFLAGS) -c $< -o $@ || { $(ECHO) "$(RED)Error: Compilation failed for $<!$(DEF_COLOR)"; exit 1; }
		@sleep 0.00001

clean:
	@$(RM) $(OBJS)
	@$(ECHO) "$(BLUE)cleaning push_swap!$(DEF_COLOR)"

fclean: clean
	@$(RM) $(NAME)
	@$(ECHO) "$(BLUE)Full clean completed!$(DEF_COLOR)"

re: fclean all

.PHONY: all clean fclean re