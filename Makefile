# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: muribe-l <muribe-l@student.42urduliz.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/12 15:45:23 by muribe-l          #+#    #+#              #
#    Updated: 2024/08/12 15:45:24 by muribe-l         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
ODIR = src/obj
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
		src/main.c

OBJS = $(patsubst src/%.c,$(ODIR)/%.o,$(SRC))

all: $(NAME)

$(ODIR):
		mkdir -p $(ODIR)

$(ODIR)/%.o: src/%.c | $(ODIR)
		$(CC) -I includes/. $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
		@make -C $(LIBFT_LIB)
		@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LIBFT_FLAGS) -o $(NAME)

clean:
		$(RM) src/*/*.o

fclean:	clean
		$(RM) $(NAME)
		@make -C $(LIBFT_LIB) fclean

re:		fclean all

.PHONY: bonus all clean fclean re
