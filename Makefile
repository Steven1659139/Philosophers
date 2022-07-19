NAME = philosophers

SRCS = thread.c
OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Werror -Wextra -g -lpthread

BRANCH ?= $(shell bash -c 'read -p "Branch: " branch; echo $$branch')
COMMIT ?= $(shell bash -c 'read -p "Commit: " commit; echo $$commit')
ANSWER ?= $(shell bash -c 'read -p "Is OK ? " answer; echo $$answer')

all: $(NAME)

$(NAME): sub $(OBJS)
	# @$(MAKE) -C ./Libft
	@gcc $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	@$(MAKE) -C  Libft fclean
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

add:
	@$(MAKE) -C Libft add
	@git add *.c *.h Makefile
	@git status

norm:
	@norminette *.c *.h

update:
	@git fetch
	@git pull origin $(BRANCH)

sub:
	@git submodule update --init --recursive

init:
	git init
	git remote add origin https://github.com/Steven1659139/Philosophers.git
	git submodule add https://github.com/Steven1659139/Libft.git

stat: add
	git branch

com: stat
		git commit -m $(COMMIT)
p: com
	@$(MAKE) -C Libft push
	git push origin $(BRANCH)
merge:
	git checkout master
	git fetch
	git pull
	git merge $(BRANCH)
go:
	git checkout $(BRANCH)