#       ___           ___           ___           ___           ___                       ___       ___     
#      /\__\         /\  \         /\__\         /\  \         /\  \          ___        /\__\     /\  \    
#     /::|  |       /::\  \       /:/  /        /::\  \       /::\  \        /\  \      /:/  /    /::\  \   
#    /:|:|  |      /:/\:\  \     /:/__/        /:/\:\  \     /:/\:\  \       \:\  \    /:/  /    /:/\:\  \  
#   /:/|:|__|__   /::\~\:\  \   /::\__\____   /::\~\:\  \   /::\~\:\  \      /::\__\  /:/  /    /::\~\:\  \ 
#  /:/ |::::\__\ /:/\:\ \:\__\ /:/\:::::\__\ /:/\:\ \:\__\ /:/\:\ \:\__\  __/:/\/__/ /:/__/    /:/\:\ \:\__\
#  \/__/~~/:/  / \/__\:\/:/  / \/_|:|~~|~    \:\~\:\ \/__/ \/__\:\ \/__/ /\/:/  /    \:\  \    \:\~\:\ \/__/
#        /:/  /       \::/  /     |:|  |      \:\ \:\__\        \:\__\   \::/__/      \:\  \    \:\ \:\__\  
#       /:/  /        /:/  /      |:|  |       \:\ \/__/         \/__/    \:\__\       \:\  \    \:\ \/__/  
#      /:/  /        /:/  /       |:|  |        \:\__\                     \/__/        \:\__\    \:\__\    
#      \/__/         \/__/         \|__|         \/__/                                   \/__/     \/__/    

CXX			=	c++
CXXFLAGS	=	-std=c++98 -MMD
CXXFLAGS	+=	-Wall -Wextra -Werror
CXXFLAGS	+=	-pedantic
NAME	=	ircserv
OBJDIR	=	obj
SRCDIR	=	src
INCDIR	=	include
SRCS	=	$(shell find $(SRCDIR) -name "*.cpp" -type f)
OBJS	=	$(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
DEPS	=	$(OBJS:%.o=%.d)
INCS	=	$(addprefix -I,$(INCDIR))

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o:$(SRCDIR)/%.cpp
	@mkdir -p $(dir $(@))
	$(CXX) $(CXXFLAGS) $(INCS) -o $(@) -c -g $(<)

$(NAME): $(OBJS)
	$(CXX) -o $(@) $(OBJS)

clean:
	$(RM) $(OBJS) $(DEPS)

fclean:	clean
	$(RM)r $(OBJDIR) $(NAME)

re: fclean all

run: all
	./$(NAME) 6667 pass

debug: all
	lldb ./$(NAME) 6667 pass

c:
	irssi -c localhost -p 6667 -w pass -n $(n)

proxy:
	python3 proxy/proxy.py testnet.ergo.chat 6667 5555

ergo:
	irssi -c localhost -p 5555 -n a

nc:
	nc 127.0.0.1 6667

-include $(DEPS)

.PHONY: all clean fclean re run proxy
