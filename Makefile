
# Compilation
CC= g++

# Warnings
ERR_FLAGS= -W -Wall -pedantic -g

# Flags
G_FLAGS= -lm

# Object files
C_FLAGS= $(G_FLAGS) -c

# Linkage
LD_FLAGS= $(G_FLAGS) -o

# Sources and objects
SRC= *.cpp
OBJ= $(SRC:.cpp=.o)

# Main
EXEC= main

# Documentation
DOC= documentation


all : $(EXEC)

$(EXEC) : $(OBJ)
	$(CC) $^ $(LD_FLAGS) $@

.PHONY: clean mrproper

clean : $(OBJ)
	rm -f $^

mrproper: clean
	rm -f $(EXEC)

%.o : %.cpp
	$(CC) $(C_FLAGS) $^

create : $(DOC)
	doxygen -g $<

update : $(DOC)
	doxygen $<

doc : create update


