COREDIR = core
TESTDIR = test

.PHONY = local embedded tests simu power-simu embedded-simu

all : local embedded

local :
	$(MAKE) -C $(COREDIR)

embedded :
	$(MAKE) -C $(COREDIR) EMBED=1

simu :
	$(MAKE) -C $(COREDIR) FULL_SIMU=1

power-simu :
	$(MAKE) -C $(COREDIR) POWER_SIMU=1

embedded-simu :
	$(MAKE) -C $(COREDIR) EMBED=1 POWER_SIMU=1

tests :
	$(MAKE) -C $(TESTDIR)

clean :
	$(MAKE) -C $(COREDIR) clean
	$(MAKE) -C $(COREDIR) clean EMBED=1
	$(MAKE) -C $(TESTDIR) clean

mrproper : clean
	$(MAKE) -C $(COREDIR) mrproper
	$(MAKE) -C $(COREDIR) mrproper EMBED=1
	$(MAKE) -C $(TESTDIR) mrproper

