#Makefile
TGT = namasu
OBJS = in.o tmp.o hanabi.o vanee.o
INCS = in.h hanabi.h 
LIBS = -lncurses

.SUFFIXES: .cpp .o

$(TGT): $(OBJS)
	g++ -o $(TGT) $(LIBS) $^

.cpp.o:
	g++ -c $<

.PHONY: clean
clean:
	$(RM) $(TGT) $(OBJS)
