# -*- Makefile -*-
libgeoclaw_generated_headers =
libgeoclaw_installed_headers = \
	src/solvers/fc2d_clawpack5/fc2d_clawpack5.h \
	src/solvers/fc2d_geoclaw/fc2d_geoclaw.h \
	src/solvers/fc2d_geoclaw/types.h \
	src/solvers/fc2d_geoclaw/fc2d_geoclaw_options.h

libgeoclaw_compiled_sources = \
	src/solvers/fc2d_geoclaw/fc2d_geoclaw.cpp \
	src/solvers/fc2d_geoclaw/fc2d_geoclaw_options.c \
	src/solvers/fc2d_geoclaw/amrlib_source/amr_module.f90 \
	src/solvers/fc2d_geoclaw/geolib_source/geoclaw_module.f90 \
	src/solvers/fc2d_geoclaw/amrlib_source/regions_module.f90 \
	src/solvers/fc2d_geoclaw/amrlib_source/gauges_module.f90 \
	src/solvers/fc2d_geoclaw/geolib_source/utility_module.f90 \
	src/solvers/fc2d_geoclaw/geolib_source/topo_module.f90 \
	src/solvers/fc2d_geoclaw/geolib_source/qinit_module.f90 \
	src/solvers/fc2d_geoclaw/geolib_source/fixedgrids_module.f90 \
	src/solvers/fc2d_geoclaw/geolib_source/refinement_module.f90 \
	src/solvers/fc2d_geoclaw/geolib_source/surge/holland_storm_module.f90 \
	src/solvers/fc2d_geoclaw/geolib_source/surge/constant_storm_module.f90 \
	src/solvers/fc2d_geoclaw/geolib_source/surge/stommel_storm_module.f90 \
	src/solvers/fc2d_geoclaw/geolib_source/surge/storm_module.f90 \
	src/solvers/fc2d_geoclaw/geolib_source/friction_module.f90 \
	src/solvers/fc2d_geoclaw/geolib_source/flux2fw.f \
	src/solvers/fc2d_geoclaw/riemann_source/rpn2_geoclaw.f \
	src/solvers/fc2d_geoclaw/riemann_source/rpt2_geoclaw.f \
	src/solvers/fc2d_geoclaw/riemann_source/geoclaw_riemann_utils.f \
	src/solvers/fc2d_geoclaw/fortran_source/geoclaw_set_modules.f90 \
	src/solvers/fc2d_geoclaw/fortran_source/geoclaw_step2_wrap.f90 \
	src/solvers/fc2d_geoclaw/fortran_source/geoclaw_limiter.f \
	src/solvers/fc2d_geoclaw/fortran_source/philim.f \
	src/solvers/fc2d_geoclaw/fortran_source/geoclaw_block.f \
	src/solvers/fc2d_geoclaw/amrlib_source/opendatafile.f \
	src/solvers/fc2d_geoclaw/amrlib_source/check4nans.f90 \
	src/solvers/fc2d_geoclaw/amrlib_source/quick_sort1.f \
	src/solvers/fc2d_geoclaw/geolib_source/topointegral.f \
	src/solvers/fc2d_geoclaw/geolib_source/bilinearintegral.f \
	src/solvers/fc2d_geoclaw/geolib_source/geoclaw_bc2.f \
	src/solvers/fc2d_geoclaw/geolib_source/geoclaw_step2.f90 \
	src/solvers/fc2d_geoclaw/geolib_source/geoclaw_setaux.f90 \
	src/solvers/fc2d_geoclaw/geolib_source/geoclaw_src2.f90 \
	src/solvers/fc2d_geoclaw/geolib_source/geoclaw_b4step2.f90 \
	src/solvers/fc2d_geoclaw/geolib_source/geoclaw_qinit.f90 \
	src/solvers/fc2d_geoclaw/geolib_source/cellgridintegrate2.f \
	src/solvers/fc2d_geoclaw/geolib_source/allowflag.f90 \
	src/solvers/fc2d_geoclaw/fclaw2d_source/fc2d_geoclaw_average_fort.f \
	src/solvers/fc2d_geoclaw/fclaw2d_source/fc2d_geoclaw_interpolate_fort.f \
	src/solvers/fc2d_geoclaw/fclaw2d_source/fc2d_geoclaw_output_ascii_fort.f \
	src/solvers/fc2d_geoclaw/fclaw2d_source/fc2d_geoclaw_tag4refinement_fort.f90 \
	src/solvers/fc2d_geoclaw/fclaw2d_source/fc2d_geoclaw_tag4coarsening_fort.f90 \
	src/solvers/fc2d_geoclaw/fclaw2d_source/fc2d_geoclaw_interpolate2fine_fort.f \
	src/solvers/fc2d_geoclaw/fclaw2d_source/fc2d_geoclaw_average2coarse_fort.f \
	src/solvers/fc2d_clawpack5/fclaw2d_source/fc2d_clawpack5_interpolate.f \
	src/solvers/fc2d_clawpack5/fclaw2d_source/fc2d_clawpack5_copy.f \
	src/solvers/fc2d_clawpack5/fclaw2d_source/fc2d_clawpack5_average.f \
	src/solvers/fc2d_clawpack5/fclaw2d_source/fc2d_clawpack5_ghostpack.f \
	src/solvers/fc2d_clawpack5/fclaw2d_source/fc2d_clawpack5_diagnostics.f \
	src/solvers/fc2d_clawpack5/fclaw2d_source/fc2d_clawpack5_timeinterp.f

lib_LTLIBRARIES += src/solvers/fc2d_geoclaw/libgeoclaw.la

src_solvers_fc2d_geoclaw_libgeoclaw_la_SOURCES = \
  $(libgeoclaw_internal_headers) \
  $(libgeoclaw_compiled_sources)

src_solvers_fc2d_geoclaw_libgeoclaw_la_CPPFLAGS = \
  $(AM_CPPFLAGS) $(FCLAW_CPPFLAGS) $(FCLAW_CLAWPACK5_CPPFLAGS)

FCLAW_GEOCLAW_CPPFLAGS = -I@top_srcdir@/src/solvers/fc2d_geoclaw
FCLAW_GEOCLAW_LDADD = @top_builddir@/src/solvers/fc2d_geoclaw/libgeoclaw.la

include_HEADERS += $(libgeoclaw_installed_headers)