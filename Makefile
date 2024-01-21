# Makes the interpreter for Autolang Version 2.

# MACROS

CXX = cl.exe
LNK = link.exe
OBJS = Interpreter.obj Auto.obj ExpressionTree.obj Map.obj Set.obj Tuple.obj AbstractMap.obj AbstractSet.obj ProgramVars.obj
OPTIONS = /EHsc /W0
# TARGETS

.PHONY : all

all : auto

auto :  $(OBJS)
	"$(LNK)" /OUT:auto.exe $(OBJS)
	
AbstractMap.obj :
	"$(CXX)" /c .\Files\Source_Files\AbstractMap.cpp $(OPTIONS)

AbstractSet.obj : 
	"$(CXX)" /c .\Files\Source_Files\AbstractSet.cpp $(OPTIONS) 
	
Set.obj : 
	"$(CXX)" /c .\Files\Source_Files\Set.cpp $(OPTIONS)  

Tuple.obj :
	"$(CXX)" /c .\Files\Source_Files\Tuple.cpp $(OPTIONS)  

Map.obj :
	"$(CXX)" /c .\Files\Source_Files\Map.cpp $(OPTIONS)  

Auto.obj :
	"$(CXX)" /c .\Files\Source_Files\Auto.cpp $(OPTIONS)  

ProgramVars.obj :
	"$(CXX)" /c .\Files\Source_Files\ProgramVars.cpp $(OPTIONS)  

ExpressionTree.obj : 
	"$(CXX)" /c .\Files\Source_Files\ExpressionTree.cpp $(OPTIONS) 

Interpreter.obj :
	echo "$(INCLUDE)"
	"$(CXX)" /c .\Files\Source_Files\Interpreter.cpp $(OPTIONS)

clean : 
	del $(OBJS) auto.exe