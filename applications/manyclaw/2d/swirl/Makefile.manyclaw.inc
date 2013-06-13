# -*- Makefile -*-

AMR_MANYCLAW = $(FORESTCLAW)/src/solvers/amr_manyclaw
AMR_MANYCLAW_FORTRAN = $(AMR_MANYCLAW)/fortran_source

manyclaw_includes = -I$(AMR_MANYCLAW) -I$(AMR_MANYCLAW_FORTRAN)

manyclaw_lib := \
	$(AMR_MANYCLAW)/amr_manyclaw.o \
	$(AMR_MANYCLAW_FORTRAN)/limiter.o \
	$(AMR_MANYCLAW_FORTRAN)/src2.o \
	$(AMR_MANYCLAW_FORTRAN)/src2_manifold.o \
	$(AMR_MANYCLAW_FORTRAN)/b4step2_manifold.o \
	$(AMR_MANYCLAW_FORTRAN)/setaux_manifold.o \
	$(AMR_MANYCLAW_FORTRAN)/qinit_manifold.o \
	$(AMR_MANYCLAW_FORTRAN)/bc2.o \
	$(AMR_MANYCLAW_FORTRAN)/bc2_manifold.o \
	$(AMR_MANYCLAW_FORTRAN)/flux2.o \
	$(AMR_MANYCLAW_FORTRAN)/qad2.o \
	$(AMR_MANYCLAW_FORTRAN)/step2.o \
	$(AMR_MANYCLAW_FORTRAN)/ClawPatch2.o



manyclaw_objs := \
	qinit.o \
	b4step2.o \
	setaux.o \
	setprob.o \
	$(manyclaw_lib)