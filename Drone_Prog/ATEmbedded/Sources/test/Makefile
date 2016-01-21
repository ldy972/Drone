CC = gcc
CFLAGS = -W -Wall
LIBS = -lm
EXEC = test_udp test_AT_commands2 test_navdata test_simu

SRCDIR = ../core
BUILDDIR = ../../Build
COREDIR =  $(BUILDDIR)/core
OBJDIR =  $(BUILDDIR)/test
EXECDIR = $(BUILDDIR)/Test_Exec
TEST_EXEC =  $(patsubst %,$(EXECDIR)/%,$(EXEC))

CORE =  $(filter-out $(COREDIR)/howard.o, $(wildcard $(COREDIR)/*.o))
SRC = $(wildcard *.c)
OBJS = $(patsubst %.c,$(OBJDIR)/%.o,$(SRC))

ifdef DEBUG
    CFLAGS += -DDEBUG
endif

ifdef EMBED
    CFLAGS += -DEMBED
endif

all : init $(TEST_EXEC)

init :
ifeq ($(wildcard $(BUILDDIR)),)
	@mkdir $(BUILDDIR)
endif
ifeq ($(wildcard $(OBJDIR)),)
	@mkdir $(OBJDIR)
endif
ifeq ($(wildcard $(EXECDIR)),)
	@mkdir $(EXECDIR)
endif
	$(MAKE) -C $(SRCDIR)

$(TEST_EXEC) : $(EXECDIR)/% : $(OBJDIR)/%.o $(CORE)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

$(OBJDIR)/%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

.PHONY: mrproper	

clean :
	rm -rf $(OBJDIR)

mrproper : clean
	rm -rf $(EXECDIR)
	rm -rf $(COREDIR)

print-%  : ; @echo $* = $($*)
