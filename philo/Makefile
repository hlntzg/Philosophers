# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/08 13:22:47 by hutzig            #+#    #+#              #
#    Updated: 2024/10/09 15:03:54 by hutzig           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

DIR_SRC = ./sources
DIR_OBJ = $(DIR_SRC)/objects

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
RM = rm -rf

SOURCES = main.c \
	utils.c \
	ft_atoi.c \

SRC = $(addprefix $(DIR_SRC)/,$(SOURCES))

OBJECTS = $(patsubst %.c,$(DIR_OBJ)/%.o,$(notdir $(SOURCES)))

HEADER = -I ./include

all: $(NAME)

$(NAME): $(OBJECTS)
	@$(CC) $(OBJECTS) $(HEADER) -o $@
	@echo "philo program has been generated"

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c | $(DIR_OBJ)
	@$(CC) $(CFLAGS) $(HEADER) -c $< -o $@
	@echo "Compiling: $<"

$(DIR_OBJ):
	@mkdir -p $(DIR_OBJ)

clean:
	@$(RM) $(DIR_OBJ)
	@echo "philo objects have been removed"

fclean: clean
	@$(RM) $(NAME)
	@echo "philo executable file has been removed"

re: fclean all

.PHONY: all clean fclean re
