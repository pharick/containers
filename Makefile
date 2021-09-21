NAME_FT			= containers_ft
NAME_STD		= containers_std

CC				= clang++
RM				= rm -f

SRCS_FT			= main_ft.cpp
SRCS_STD		= main_std.cpp

OBJS_FT			= $(SRCS_FT:.cpp=.o)
OBJS_STD		= $(SRCS_STD:.cpp=.o)

DEPS_FT			= $(SRCS_FT:.cpp=.d)
DEPS_STD		= $(SRCS_STD:.cpp=.d)

CFLAGS			= -Wall -Wextra -Werror -std=c++98

all:			$(NAME_FT) $(NAME_STD)

%.o : %.cpp
				$(CC) $(CFLAGS) -Isrcs -c $< -o $@

%.d: %.cpp
				@set -e; $(RM) $@; \
				$(CC) -Isrcs -M $(CPPFLAGS) $< > $@.$$$$; \
				sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
				$(RM) $@.$$$$

$(NAME_FT):		$(OBJS_FT)
				$(CC) $(OBJS_FT) -o $(NAME_FT)

$(NAME_STD):	$(OBJS_STD)
				$(CC) $(OBJS_STD) -o $(NAME_STD)

clean:
				$(RM) $(OBJS_FT) $(OBJS_STD) $(DEPS_FT) $(DEPS_STD)

fclean:			clean
				$(RM) $(NAME_FT) $(NAME_STD)

re:				fclean all

include $(DEPS)

.PHONY: clean fclean re all test
