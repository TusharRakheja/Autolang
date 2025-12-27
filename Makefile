# Makes the interpreter for Autolang Version 2.

# MACROS

CXX = g++
LNK = g++
OBJS = Interpreter.o Auto.o ExpressionTree.o Map.o Set.o Tuple.o AbstractMap.o AbstractSet.o ProgramVars.o
OPTIONS = -w
# TARGETS

.PHONY : all

all : auto

auto : $(OBJS)
	$(LNK) -o auto $(OBJS)

AbstractMap.o :
	$(CXX) -c ./Files/Source_Files/AbstractMap.cpp $(OPTIONS)

AbstractSet.o :
	$(CXX) -c ./Files/Source_Files/AbstractSet.cpp $(OPTIONS)

Set.o :
	$(CXX) -c ./Files/Source_Files/Set.cpp $(OPTIONS)

Tuple.o :
	$(CXX) -c ./Files/Source_Files/Tuple.cpp $(OPTIONS)

Map.o :
	$(CXX) -c ./Files/Source_Files/Map.cpp $(OPTIONS)

Auto.o :
	$(CXX) -c ./Files/Source_Files/Auto.cpp $(OPTIONS)

ProgramVars.o :
	$(CXX) -c ./Files/Source_Files/ProgramVars.cpp $(OPTIONS)

ExpressionTree.o :
	$(CXX) -c ./Files/Source_Files/ExpressionTree.cpp $(OPTIONS)

Interpreter.o :
	$(CXX) -c ./Files/Source_Files/Interpreter.cpp $(OPTIONS)

clobber:
	rm -f $(OBJS) auto

clean :
	rm -f $(OBJS)
