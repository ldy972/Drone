# Project Howard - ATEmbedded core makefile
# Kévin Salaün - v0.1 - 03/12/2015
# Builds ATEmbedded core .o files

CFLAGS = -W -Wall

BUILDDIR = ../../Build
OBJDIR = $(BUILDDIR)/core
SRC = $(wildcard *.c)
OBJS = $(patsubst %.c,$(OBJDIR)/%.o,$(SRC))

ifdef DEBUG
    CFLAGS += -DDEBUG
endif

ifdef EMBED
    CC = arm-linux-gnueabi-gcc
    CFLAGS += -DEMBED
else
    CC = gcc
endif

all : init $(OBJS)

# Create build directories when needed
init :
ifeq ($(wildcard $(BUILDDIR)),)
	@mkdir $(BUILDDIR)
endif
ifeq ($(wildcard $(OBJDIR)),)
	@mkdir $(OBJDIR)
endif

# Create each .o if the corresponding .c or .h file has been edited
$(OBJDIR)/%.o : %.c $(wildcard %.h) debug.h navdata_structs.h
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -rf $(OBJS)

mrproper : clean
	rm -rf $(OBJDIR)

# For debug purposes : Prints a variable
print-% : ; @echo $* = $($*)
