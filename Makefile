NAME = philosophers

SRCS = main.c
OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Werror -Wextra -g #-lpthread

BRANCH ?= $(shell bash -c 'read -p "Branch: " branch; echo $$branch')
COMMIT ?= $(shell bash -c 'read -p "Commit: " commit; echo $$commit')
PATH_SUBMODULE ?= $(shell bash -c 'read -p "Adress of the submodule: " path_submodule; echo $$path_submodule')
NAME_SUBMODULE ?= $(shell bash -c 'read -p "Name of the submodule: " name_submodule; echo $$name_submodule')

all: $(NAME)

$(NAME): $(OBJS)
	@gcc $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	@$(MAKE) -C  Libft fclean
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

add:
	@git add *.c *.h Makefile to_do.txt
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