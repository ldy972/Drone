# Project Howard - ATEmbedded core makefile
# Kévin Salaün - v0.1 - 03/12/2015
# Builds ATEmbedded core .o files

CFLAGS = -W -Wall -pthread -D_REENTRANT
LIBS = -lm

BUILDDIR = ../../Build
OBJDIR = $(BUILDDIR)/core
EXECDIR =  $(BUILDDIR)
EXEC = $(EXECDIR)/howard
SRC = $(filter-out ,$(wildcard *.c))
OBJS = $(patsubst %.c,$(OBJDIR)/%.o,$(SRC))

ifdef DEBUG
    CFLAGS += -g
endif

ifdef PRINT_DEBUG
    CFLAGS += -DDEBUG
endif

ifdef FULL_SIMU
    CFLAGS += -DFULL_SIMU
endif

ifdef POWER_SIMU
    CFLAGS += -DPOWER_SIMU
endif

ifdef EMBED
    CC = arm-linux-gnueabi-gcc
    CFLAGS += -DEMBED
    EXEC = $(EXECDIR)/howard.elf  
    OBJS = $(patsubst %.c,$(OBJDIR)/%.so,$(SRC))
else
    CC = gcc
    EXEC = $(EXECDIR)/howard
endif

all : init $(EXEC)

# Create build directories when needed
init :
ifeq ($(wildcard $(BUILDDIR)),)
	@mkdir $(BUILDDIR)
endif
ifeq ($(wildcard $(OBJDIR)),)
	@mkdir $(OBJDIR)
endif

## Rules for non embedded compilation
$(EXECDIR)/% : $(OBJDIR)/%.o $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

# Create each .o if the corresponding .c or .h file has been edited
$(OBJDIR)/%.o : %.c $(wildcard %.h) shared.h
	$(CC) $(CFLAGS) -c $< -o $@

## Rules for embedded compilation
$(EXECDIR)/%.elf : $(OBJDIR)/%.so $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

# Create each .so if the corresponding .c or .h file has been edited
$(OBJDIR)/%.so : %.c $(wildcard %.h) shared.h
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS : $(OBJDIR)/%.o $(OBJDIR)/%.so

clean :
	rm -rf $(OBJS)

mrproper : clean
	rm -rf $(OBJDIR)
	rm -rf $(EXEC)

# For debug purposes : Prints a variable
print-% : ; @echo $* = $($*)
