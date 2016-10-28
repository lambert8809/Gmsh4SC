SHELL := /bin/bash

OUTNAME=pkinterface

CXX=g++

INCLUDE = -I./ -I/usr/include/ -I/usr/local/include/gmsh/ -I./include/

PKLIB = /home/bernard/parasolid/base/shared_object/
GMSHLIB = /home/bernard/devel/gmsh/build/

CXXFLAGS  ?=  -g 

#Reconnaitre les extensions de fichier comme suffixes...
SUFFIXES ?= .cpp .o .h
.SUFFIXES: $(SUFFIXES) .

X64_CCOPTIONS=-m64 -w -fPIC

#Liste des fichiers objets nécessaires pour le programme 
OBJS = main.c libfrustrum.a libfg.a libfrustrum_delta.a ParasolidDataBase.o ParasolidGModelBuilder.o callbacks.o

$(OUTNAME): $(OBJS)
	$(CXX) $(X64_CCOPTIONS) $(INCLUDE) main.c callbacks.o ParasolidDataBase.o ParasolidGModelBuilder.o -L. -lfrustrum -lfrustrum_delta -lfg -L$(PKLIB) -lpskernel -Wl,-rpath=$(PKLIB) -L$(PKLIB) -lkid_support -Wl,-rpath=$(PKLIB)  -L$(GMSHLIB) -lGmsh -Wl,-rpath=$(GMSHLIB) -lm -lpthread  $(CXXFLAGS) -o $(OUTNAME)
	chmod a+rx $(OUTNAME)
libfrustrum.a: frustrum.c
	$(CXX) $(X64_CCOPTIONS) -c frustrum.c $(INCLUDE) $(CXXFLAGS) -o frustrum.o
	ar rcv ./libfrustrum.a ./frustrum.o
	rm frustrum.o
libfrustrum_delta.a: frustrum_delta.c
	$(CXX) $(X64_CCOPTIONS) -c frustrum_delta.c $(INCLUDE) $(CXXFLAGS) -o frustrum_delta.o
	ar rcv ./libfrustrum_delta.a ./frustrum_delta.o
	rm frustrum_delta.o
libfg.a: fg.c
	$(CXX) $(X64_CCOPTIONS) -c fg.c $(INCLUDE) $(CXXFLAGS) -o fg.o
	ar rcv ./libfg.a ./fg.o
	rm fg.o
ParasolidDataBase.o: ParasolidDataBase.cpp
	$(CXX) $(X64_CCOPTIONS) -c ParasolidDataBase.cpp $(INCLUDE) $(CXXFLAGS) -o ParasolidDataBase.o
ParasolidGModelBuilder.o: ParasolidGModelBuilder.cpp 
	$(CXX) $(X64_CCOPTIONS) -c ParasolidGModelBuilder.cpp $(INCLUDE) $(CXXFLAGS) -o ParasolidGModelBuilder.o
callbacks.o: callbacks.cpp
	$(CXX) $(X64_CCOPTIONS) -c callbacks.cpp $(INCLUDE) $(CXXFLAGS) -o callbacks.o


clean:
	rm -f *.o
	rm -f libfrustrum.a libfrustrum_delta.a libfg.a
	rm -f $(OUTNAME)

