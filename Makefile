################################################################################
##                               Présentation                                 ##
################################################################################

COLOR_NORM		=	\033[0m
COLOR_RED		=	\033[31m
COLOR_PURPLE	=	\033[35m

################################################################################
##                               SRCS                                         ##
################################################################################
MK = Makefile

# Headers
DIR_HDS				=	includes

RELATIVE_HDS		=	includes.hpp		\
						Server.hpp			\
						Parse.hpp			\
						Channel.hpp

# Code
DIR_GLOBAL						=	srcs
SRC_GLOBAL						=	main.cpp				\
									Server.cpp				\
									Channel.cpp				\
									Parse.cpp				\
									parsing.cpp


################################################################################
##                       Compilation Environnement                            ##
################################################################################
NAME	=	ircserv
CC		=	c++
CFLAGS	=	-Wall -Werror -Wextra -std=c++98 -g3 -ggdb -fsanitize=address

# Sources

# All dirs
DIRS_SRC			=	$(DIR_GLOBAL)

DIR_OBJ				=	obj

# All srcs
SRCS		=	$(addprefix $(DIR_GLOBAL)/, $(SRC_GLOBAL))

# All hpp
HDS			=	$(addprefix $(DIR_HDS)/, $(RELATIVE_HDS))
# All objs
OBJS		=	$(addprefix $(DIR_OBJ)/, $(SRCS:.cpp=.o))

DEPENDS		=	$(HDS) $(MK)

################################################################################
##                                 Règles                                     ##
################################################################################
all		:	$(NAME)

define src2obj
$(DIR_OBJ)/$(1)/%.o:	$(1)/%.cpp $(2)
	@mkdir -p $(DIR_OBJ)/$(1)
	@printf "\r\033[K\tCompilation of $(COLOR_PURPLE)$$< ==> $$@\$(COLOR_NORM)"
	@$(CC) $(CFLAGS) -c -o $$@ $$< $(INC_INC)
endef

$(foreach dir,$(DIRS_SRC),$(eval $(call src2obj,$(dir), $(DEPENDS))))

$(NAME)	: $(DEPENDS) $(OBJS)
	@printf "\n\tCompilation of $(COLOR_PURPLE)$(NAME)\$(COLOR_NORM)\n"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	@printf "\tDelete $(COLOR_RED)$(DIR_OBJ)/$(COLOR_NORM) of $(NAME)\n"
	@rm -rf $(DIR_OBJ)

fclean:	clean
	@printf "\tDelete $(COLOR_RED)$(NAME)$(COLOR_NORM)\n"
	@rm -rf $(NAME)

re:	fclean all
