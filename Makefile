################################################################################
##                         Compilation environnement                          ##
################################################################################

NAME	=	ircserv
CC		=	c++
CFLAGS	=	-Wall -Werror -Wextra -std=c++98 -g3 -ggdb -fsanitize=address

################################################################################
##                               SRCS                                         ##
################################################################################
MK = Makefile

# Headers
DIR_HDS				=	includes

RELATIVE_HDS		=	includes.hpp			\
						runtime.hpp				\
						Server.hpp				\
						define.hpp				\
						commands.hpp			\
						channel/ChannelMode.hpp	\
						channel/Channel.hpp		\
						mode/utils.hpp			\
						user/UserMode.hpp		\
						user/User.hpp			\
						log/log.hpp				\
						bot/bot.hpp				\
						Parsing.hpp				\
						reply.hpp				\
						utils/string.hpp		\
						utils/compare.hpp


# Code
DIR_GLOBAL		=	srcs
SRC_GLOBAL		=	main.cpp		\
					Parsing.cpp		\
					Server.cpp

DIR_USER		=	$(DIR_GLOBAL)/user
SRC_USER		=	UserMode.cpp User.cpp

DIR_BOT			=	$(DIR_GLOBAL)/bot
SRC_BOT			=	bot.cpp

DIR_LOG			=	$(DIR_GLOBAL)/log
SRC_LOG			=	log.cpp

DIR_CHANNEL		=	$(DIR_GLOBAL)/channel
SRC_CHANNEL		=	ChannelMode.cpp Channel.cpp

DIR_MOD			=	$(DIR_GLOBAL)/mode
SRC_MOD			=	utils.cpp

DIR_UTILS		=	$(DIR_GLOBAL)/utils
SRC_UTILS		=	string.cpp compare.cpp

DIR_COMMANDS	=	$(DIR_GLOBAL)/commands
SRC_COMMANDS	=	initCmd.cpp			\
					PASS.cpp			\
					NICK.cpp			\
					INFO.cpp			\
					USER.cpp			\
					PRIVMSG.cpp			\
					HELP.cpp			\
					VERSION.cpp			\
					CAP.cpp				\
					KICK.cpp			\
					PART.cpp			\
					LUSERS.cpp			\
					TIME.cpp			\
					QUIT.cpp			\
					PING.cpp			\
					PONG.cpp			\
					TOPIC.cpp			\
					NAMES.cpp			\
					MODE.cpp			\
					NOTICE.cpp			\
					KILL.cpp			\
					OPER.cpp			\
					INVITE.cpp			\
					JOIN.cpp			

################################################################################
##                         Binaries Architecture                              ##
################################################################################

# All dirs
DIRS_SRC	=	${DIR_BOT} $(DIR_MOD) $(DIR_COMMANDS) $(DIR_UTILS) $(DIR_USER) \
				$(DIR_LOG) $(DIR_CHANNEL) $(DIR_GLOBAL)

# Directory of all binaries (objects)
DIR_OBJ		=	obj

# All srcs
SRCS		=	$(addprefix $(DIR_GLOBAL)/, $(SRC_GLOBAL))		\
				$(addprefix $(DIR_USER)/, $(SRC_USER))			\
				$(addprefix $(DIR_BOT)/, $(SRC_BOT))			\
				$(addprefix $(DIR_MOD)/, $(SRC_MOD))			\
				$(addprefix $(DIR_UTILS)/, $(SRC_UTILS))		\
				$(addprefix $(DIR_LOG)/, $(SRC_LOG))			\
				$(addprefix $(DIR_COMMANDS)/, $(SRC_COMMANDS))	\
				$(addprefix $(DIR_CHANNEL)/, $(SRC_CHANNEL))

# All hpp
HDS			=	$(addprefix $(DIR_HDS)/, $(RELATIVE_HDS))

# All objs location
OBJS		=	$(addprefix $(DIR_OBJ)/, $(SRCS:.cpp=.o))

# Global dependencies
DEPENDS		=	$(HDS) $(MK)

################################################################################
##                               Presentation                                 ##
################################################################################

COLOR_NORM		=	\033[0m
COLOR_RED		=	\033[31m
COLOR_PURPLE	=	\033[35m

################################################################################
##                                  Rules                                     ##
################################################################################

# Default rule
all		:	$(NAME)

# Rule function to create .o with .cpp
# @param $(1) the directory of the source
# @param $(2) the dependence of the source
define src2obj
$(DIR_OBJ)/$(1)/%.o:	$(1)/%.cpp $(2)
	@mkdir -p $(DIR_OBJ)/$(1)
	@printf "\r\033[K\tCompilation of $(COLOR_PURPLE)$$< ==> $$@\$(COLOR_NORM)"
	@$(CC) $(CFLAGS) -c -o $$@ $$< $(INC_INC)
endef

# Construct all rules for each directory .cpp => .o
$(foreach dir,$(DIRS_SRC),$(eval $(call src2obj,$(dir), $(DEPENDS))))

# NAME rule to construct the executable
$(NAME)	: $(DEPENDS) $(OBJS)
	@printf "\n\tCompilation of $(COLOR_PURPLE)$(NAME)\$(COLOR_NORM)\n"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

# Remove all objects (.o)
clean:
	@printf "\tDelete $(COLOR_RED)$(DIR_OBJ)/$(COLOR_NORM) of $(NAME)\n"
	@rm -rf $(DIR_OBJ)

# Remove all objects (.o) and the executable
fclean:	clean
	@printf "\tDelete $(COLOR_RED)$(NAME)$(COLOR_NORM)\n"
	@rm -rf $(NAME)

# Delete all binaries and recompile
re:	fclean all
