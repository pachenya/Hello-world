#Makefile
TGT = namasu
OBJS = tmp.o
LIBS = -lncurses

.SUFFIXES: .cpp .o

$(TGT): $(OBJS)
	g++ -o $(TGT) $(LIBS) $^

.cpp.o:
	g++ -c $<

.PHONY: clean
clean:
	$(RM) $(TGT) $(OBJS)
