# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: slavoie <slavoie@student.42quebec.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/06 14:56:01 by slavoie           #+#    #+#              #
#    Updated: 2022/09/06 14:56:03 by slavoie          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = main.c state.c end.c ft_yo_its_wrong.c utils.c print.c init.c
OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Werror -Wextra -g #-lpthread

CC = @gcc

GREEN = \033[1;32m

BRANCH ?= $(shell bash -c 'read -p "Branch: " branch; echo $$branch')
COMMIT ?= $(shell bash -c 'read -p "Commit: " commit; echo $$commit')
PATH_SUBMODULE ?= $(shell bash -c 'read -p "Adress of the submodule: " path_submodule; echo $$path_submodule')
NAME_SUBMODULE ?= $(shell bash -c 'read -p "Name of the submodule: " name_submodule; echo $$name_submodule')

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)Everything is top shape tiguidou 🐥"

clean:
	@echo "Cleaning 🌪 🔥🌊"
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

add:
	@git add *.c *.h Makefile
	@git status

norm:
	@norminette *.c *.h

update:
	@git fetch
	@git pull origin $(BRANCH)

sub:
	@git submodule update --init --recursive

add_sub:
	git submodule add $(PATH_SUBMODULE)

del_sub:
	vim .gitmodules
	git add .gitmodules
	vim .git/config
	git rm --cached $(NAME_SUBMODULE)
	rm -rf .git/modules/$(NAME_SUBMODULE)
	git commit -m "Removed submodule"
	rm -rf $(NAME_SUBMODULE)


	
init:
	git init
	git remote add origin https://github.com/Steven1659139/Philosophers.git

stat: add
	git branch

com: stat
		git commit -m $(COMMIT)
p: com
	git push origin $(BRANCH)
merge:
	git checkout master
	git fetch
	git pull
	git merge $(BRANCH)
go:
	git checkout $(BRANCH)