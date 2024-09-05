# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: muribe-l <muribe-l@student.42urduliz.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/12 15:45:23 by muribe-l          #+#    #+#              #
#    Updated: 2024/09/05 12:02:40 by muribe-l         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
ODIR = obj
LIBFT_LIB = src/libft/
LIBFT_FLAGS = -L src/libft/ -lft
CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=leak
LDFLAGS = -lreadline -L /opt/homebrew/opt/readline/lib
RM		= rm -f

SRC =	src/mod_split.c \
		src/first_check.c \
		src/utils.c \
		src/fake_glob.c \
		src/expand.c \
		src/execution.c \
		src/here_doc.c \
		src/get_cmd.c \
		src/get_path.c \
		src/get_file.c \
		src/michel.c \
		src/main.c \
		src/builtins/builtins.c \
		src/builtins/cd.c \
		src/builtins/echo.c \
		src/builtins/env.c \
		src/builtins/exit.c \
		src/builtins/export.c \
		src/builtins/pwd.c \
		src/builtins/unset.c

OBJS = $(patsubst src/%.c,$(ODIR)/%.o,$(SRC))

all: $(NAME)

$(ODIR):
		mkdir -p $(ODIR)
		find src -type d -exec mkdir -p $(ODIR)/{} \;

$(ODIR)/%.o: src/%.c | $(ODIR)
	mkdir -p $(dir $@)
	$(CC) -I includes/. $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
		@make -C $(LIBFT_LIB)
		@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LIBFT_FLAGS) -o $(NAME)

clean:
		$(RM) $(ODIR)/*/*.o

fclean:	clean
		$(RM) $(NAME)
		@make -C $(LIBFT_LIB) fclean

re:		fclean all

.PHONY: bonus all clean fclean re
