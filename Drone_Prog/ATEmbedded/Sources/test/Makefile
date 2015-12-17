CC = gcc
CFLAGS = -W -Wall
EXEC = test_udp test_AT_commands2 test_navdata

SRCDIR = ../core
BUILDDIR = ../../Build
COREDIR =  $(BUILDDIR)/core
OBJDIR =  $(BUILDDIR)/test
EXECDIR = $(BUILDDIR)/Test_Exec
TEST_EXEC =  $(patsubst %,$(EXECDIR)/%,$(EXEC))

CORE =  $(filter-out $(COREDIR)/controller.o, $(wildcard $(COREDIR)/*.o))
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
	$(CC) $(CFLAGS) $^ -o $@

$(OBJDIR)/%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: mrproper	

clean :
	rm -rf $(OBJDIR)

mrproper : clean
	rm -rf $(EXECDIR)

print-%  : ; @echo $* = $($*)
