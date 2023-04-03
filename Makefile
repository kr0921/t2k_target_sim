# $Id: Makefile,v 1.1 2011/10/07 11:29:22 mhartz Exp $
# --------------------------------------------------------------
# GNUmakefile for examples module.  Gabriele Cosmo, 06/04/98.
# --------------------------------------------------------------

name := T2K_target_sim
G4TARGET := $(name)
G4EXLIB := true

ifndef G4INSTALL
  G4INSTALL = ../Geant4_10.1.03.04/geant4_source
endif

.PHONY: all
all: lib bin

ROOTLIBS := $(shell root-config --glibs --libs)
ROOTINCLUDES := $(shell root-config --prefix)/include 
ROOTCFLAGS := $(shell root-config --cflags) 

CPPFLAGS += $(ROOTCFLAGS)
CPPFLAGS += -I$(ROOTCFLAGS)
CPPFLAGS += $(ROOTLIBS)

include $(G4INSTALL)/config/binmake.gmk
