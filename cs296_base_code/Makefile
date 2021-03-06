.SUFFIXES: .cpp .hpp

# Programs
SHELL 	= bash
CC     	= g++
LD	= ld
RM 	= rm
ECHO	= /bin/echo
CAT	= cat
PRINTF	= printf
SED	= sed
DOXYGEN = doxygen
######################################
# Project Name (generate executable with this name)
TARGET = cs296_23_exe
LIBTARGET= cs296_23_exelib

# installation directory
INSTALLATION_DIR = ../../CraneSimulation

# Project Paths
PROJECT_ROOT=.
#in below variable box2d software 
EXTERNAL_ROOT=$(PROJECT_ROOT)/external
#in below variable our project source files are stored
SRCDIR = $(PROJECT_ROOT)/src
# in below varibale objects files are stored
OBJDIR = $(PROJECT_ROOT)/myobjs
#in below variable executables are stored
BINDIR = $(PROJECT_ROOT)/mybins
DOCDIR = $(PROJECT_ROOT)/doc
LIBDIR = $(PROJECT_ROOT)/mylibs

# Library Paths
BOX2D_ROOT=$(EXTERNAL_ROOT)
GLUI_ROOT=/usr
GL_ROOT=/usr/include/

#Libraries
LIBS = -lBox2D -lglui -lglut -lGLU -lGL

# Compiler and Linker flags
CPPFLAGS=-g -Wall -fno-strict-aliasing -pg
CPPFLAGS+=-I $(BOX2D_ROOT)/include -I $(GLUI_ROOT)/include
MODIFY=$(CPPFLAGS)
LDFLAGS+=-L $(BOX2D_ROOT)/lib -L $(GLUI_ROOT)/lib

######################################

NO_COLOR=\e[0m
OK_COLOR=\e[1;32m
ERR_COLOR=\e[1;31m
WARN_COLOR=\e[1;33m
MESG_COLOR=\e[1;34m
FILE_COLOR=\e[1;37m

OK_STRING="[OK]"
ERR_STRING="[ERRORS]"
WARN_STRING="[WARNINGS]"
OK_FMT="${OK_COLOR}%30s\n${NO_COLOR}"
ERR_FMT="${ERR_COLOR}%30s\n${NO_COLOR}"
WARN_FMT="${WARN_COLOR}%30s\n${NO_COLOR}"
######################################

SRCS := $(wildcard $(SRCDIR)/*.cpp)
INCS := $(wildcard $(SRCDIR)/*.hpp)
OBJS := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
VARPATH=$(shell find ./external/include  -name Box2D)
SOFT=$(EXTERNAL_ROOT)/src/Box2D
SHARED_LIB=TRUE
REST=$(filter-out ./myobjs/main.o,$(OBJS))
type=n

.PHONY: all setup doc clean distclean graph1 graph2 graph3 graph4 graph5 plot

all: setup normal exe exelib

setup:
	@echo $(type)
	@$(ECHO) "Setting up compilation..." 
	@mkdir -p myobjs
	@mkdir -p mybins
	@mkdir -p mylibs

normal:
ifeq (,$(VARPATH))
	@ tar xvzf ./external/src/Box2D.tgz  -C ./external/src/
	@ mkdir -p $(SOFT)/build296 
	@ cd $(SOFT)/build296 ;  cmake ../ ;  make ; make install
endif

release_install:
ifeq (,$(VARPATH))
	@ tar xvzf ./external/src/Box2D.tgz  -C ./external/src/
	@ mkdir -p $(SOFT)/build296 
	@ cd $(SOFT)/build296 ;  cmake -DCMAKE_BUILD_TYPE=Release ../ ;  make ; make install 
endif

debug_install:
ifeq (,$(VARPATH))
	@ tar xvzf ./external/src/Box2D.tgz  -C ./external/src/
	@ mkdir -p $(SOFT)/build296 
	@ cd $(SOFT)/build296 ;  cmake -DCMAKE_BUILD_TYPE=Debug ../ ;  make ; make install 
endif
    
static_target: $(OBJS)
ifeq ($(SHARED_LIB),FALSE)
	@ ar -cvq libCS296test.a $(REST)
	@ mv  libCS296test.a  ./mylibs
endif
dynamic_target: $(OBJS)
ifeq ($(SHARED_LIB),TRUE)
	@ $(CC) -pg -shared -o libCS296test.so $(REST) 
	@mv  libCS296test.so  ./mylibs
	@export LD_LIBRARY_PATH=./mylibs:$LD_LIBRARY_PATH
endif
	
exe: setup $(OBJS)
	@$(PRINTF) "$(MESG_COLOR)Building executable:$(NO_COLOR) $(FILE_COLOR) %16s$(NO_COLOR)" "$(notdir $(BINDIR)/$(TARGET))"
	@$(CC) -pg -o $(BINDIR)/$(TARGET) $(LDFLAGS) $(OBJS) $(LIBS) 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else $(PRINTF) $(OK_FMT) $(OK_STRING); \
	fi;
	@$(RM) -f temp.log temp.err
	
exelib: setup $(OBJS)
	@$(PRINTF) "$(MESG_COLOR)Building executable:$(NO_COLOR) $(FILE_COLOR) %16s$(NO_COLOR)" "$(notdir $(BINDIR)/$(LIBTARGET))"
ifeq ($(SHARED_LIB),FALSE)
	@make static_target
	@$(CC) -pg -o $(BINDIR)/$(LIBTARGET)  $(LDFLAGS) ./myobjs/main.o  ./mylibs/libCS296test.a   $(LIBS)  2> temp.log || touch temp.err
else
	@make dynamic_target
	@$(CC) -pg -o $(BINDIR)/$(LIBTARGET) ./myobjs/main.o $(LDFLAGS) ./mylibs/libCS296test.so $(LIBS) 2> temp.log || touch temp.err
endif
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else $(PRINTF) $(OK_FMT) $(OK_STRING); \
	fi;
	@$(RM) -f temp.log temp.err

-include $(OBJS:.o=.d)

$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp 
	@$(PRINTF) "$(MESG_COLOR)Compiling: $(NO_COLOR) $(FILE_COLOR) %25s$(NO_COLOR)" "$(notdir $<)"
	@$(CC) $(CPPFLAGS) -fpic -c $< -o $@ -MD 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else printf "${OK_COLOR}%30s\n${NO_COLOR}" "[OK]"; \
	fi;
	@$(RM) -f temp.log temp.err

doc:
	@$(ECHO) -n "Generating Doxygen Documentation ...  "
	@$(RM) -rf doc/html
	@$(DOXYGEN) -u $(DOCDIR)/Doxyfile 2 > /dev/null
	@$(ECHO) "Done"

clean:
	@$(ECHO) -n "Cleaning up..."
	@$(RM) -rf $(OBJDIR) *~ $(DEPS) $(SRCDIR)/*~ ./myobjs ./mylibs ./mybins 
	@$(RM) -rf data plots
	@$(RM) -rf doc/*.pdf doc/*.aux doc/*.log doc/*.blg doc/*.bbl doc/*.out
	@$(ECHO) "Done"

distclean: clean
	@$(RM) -rf $(BINDIR) $(DOCDIR)/html
	@$(ECHO) -n "Cleaning up..."
	@$(RM) -rf $(OBJDIR) *~ $(DEPS) $(SRCDIR)/*~ ./myobjs ./mylibs ./mybins 
	@$(RM) -rf  $(EXTERNAL_ROOT)/include/*	 $(EXTERNAL_ROOT)/lib/*  $(EXTERNAL_ROOT)/src/Box2D
	@$(RM) -f g23_debug_prof.dat g23_release_prof.dat gmon.out *.png;
	@$(ECHO) "Done" 
	
data:
	@mkdir -p data
	@cd scripts;\
	./g23_gen_data_csv.sh;\
	./g23_gen_data_random.sh
	$(ECHO) "Report Done"



plot: data 
	@mkdir -p plots;
	@cd scripts;\
	./helper1.sh;\
	./helper2.sh;\
	./helper4.sh;\
	gnuplot g23_plot01.gpt;\
	gnuplot g23_plot02.gpt;\
	gnuplot g23_plot03.gpt;\
	gnuplot g23_plot04.gpt;\
	
report: 
	@mkdir -p data
	@mkdir -p plots
	@cd doc ;\
	pdflatex g23_projectReport; \
	bibtex g23_projectReport; \
	pdflatex g23_projectReport; \
	pdflatex g23_projectReport; \

	@cd scripts;\
	python g23_gen_html.py;\
	#python g23_gen_csv.py;\
	#python g23_gen_plots.py; \
	#@$(RM) data/averaged.csv
	


gpf:
	chmod +x gprof2dot.py;
	mybins/cs296_23_exe;
	gprof ./mybins/cs296_23_exe | ./gprof2dot.py | dot -Tpng -o output2.png;

debug_gprof:
	@mkdir -p data
	@make setup; make debug_install; make exe; make exelib;
	@./mybins/cs296_23_exe <<< 10000;
	@gprof ./mybins/cs296_23_exe gmon.out >  data/g23_debug_prof.dat;
	@chmod +x gprof2dot.py;
	@./gprof2dot.py ./data/g23_debug_prof.dat | fdp -Tpng -o doc/debug.png
	@$(RM) -f gmon.out;

release_gprof: CPPFLAGS+=-O3
release_gprof:
	@mkdir -p data;
	@make setup; make release_install; make exe; make exelib
	@./mybins/cs296_23_exe <<< 10000;
	@gprof ./mybins/cs296_23_exe gmon.out >  data/g23_release_prof.dat;
	@chmod +x gprof2dot.py;
	@./gprof2dot.py ./data/g23_release_prof.dat | fdp -Tpng -o doc/release.png
	@$(RM) -f gmon.out;

install: exe exelib doc report
	@rm -rf $(INSTALLATION_DIR)
	@mkdir $(INSTALLATION_DIR)
	@cp -r mybins/ $(INSTALLATION_DIR)
	@cp -r doc/ $(INSTALLATION_DIR)
	@cp -r mylibs/ $(INSTALLATION_DIR)
	@cp -r scripts/ $(INSTALLATION_DIR)
	

dist: distclean
	@cd ../../; \
	tar cvzf cs296_g23_project.tar.gz g23_project README.txt