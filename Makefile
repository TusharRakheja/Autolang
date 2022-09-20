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
	"$(LNK)" /OUT:auto.exe /LIBPATH:"$(LIB)" /LIBPATH:"$(LIB2)" /LIBPATH:"$(LIB3)" $(OBJS)
	
AbstractMap.obj :
	"$(CXX)" /c .\Files\Source_Files\AbstractMap.cpp /I "$(INCLUDE)" /I "$(LIB)" /I "$(UCRT)" $(OPTIONS)

AbstractSet.obj : 
	"$(CXX)" /c .\Files\Source_Files\AbstractSet.cpp /I "$(INCLUDE)" /I "$(LIB)" /I "$(UCRT)" $(OPTIONS) 
	
Set.obj : 
	"$(CXX)" /c .\Files\Source_Files\Set.cpp /I "$(INCLUDE)" /I "$(LIB)" /I "$(UCRT)" $(OPTIONS)  

Tuple.obj :
	"$(CXX)" /c .\Files\Source_Files\Tuple.cpp /I "$(INCLUDE)" /I "$(LIB)" /I "$(UCRT)" $(OPTIONS)  

Map.obj :
	"$(CXX)" /c .\Files\Source_Files\Map.cpp /I "$(INCLUDE)" /I "$(LIB)" /I "$(UCRT)" $(OPTIONS)  

Auto.obj :
	"$(CXX)" /c .\Files\Source_Files\Auto.cpp /I "$(INCLUDE)" /I "$(LIB)" /I "$(UCRT)" $(OPTIONS)  

ProgramVars.obj :
	"$(CXX)" /c .\Files\Source_Files\ProgramVars.cpp /I "$(INCLUDE)" /I "$(LIB)" /I "$(UCRT)" $(OPTIONS)  

ExpressionTree.obj : 
	"$(CXX)" /c .\Files\Source_Files\ExpressionTree.cpp /I "$(INCLUDE)" /I "$(LIB)" /I "$(UCRT)" $(OPTIONS) 

Interpreter.obj :
	echo "$(INCLUDE)"
	"$(CXX)" /c .\Files\Source_Files\Interpreter.cpp /I "$(INCLUDE)" /I "$(LIB)" /I "$(UCRT)" $(OPTIONS)

clean : 
	del $(OBJS) auto.exe
