## Makefile.am in applications/clawpack/euler/2d/quadrants

bin_PROGRAMS += applications/clawpack/euler/2d/quadrants/quadrants

applications_clawpack_euler_2d_quadrants_quadrants_SOURCES = \
	applications/clawpack/euler/2d/quadrants/quadrants.cpp \
	applications/clawpack/euler/2d/quadrants/quadrants_user.cpp \
	applications/clawpack/euler/2d/quadrants/setprob.f \
	applications/clawpack/euler/2d/quadrants/user_4.6/qinit.f \
	applications/clawpack/euler/2d/quadrants/user_5.0/qinit.f90 \
	applications/clawpack/euler/2d/rp/clawpack46_rpn2_euler4.f \
	applications/clawpack/euler/2d/rp/clawpack46_rpt2_euler4.f \
	applications/clawpack/euler/2d/rp/clawpack5_rpn2_euler4.f90 \
	applications/clawpack/euler/2d/rp/clawpack5_rpt2_euler4.f90

quadrants_headers = \
	applications/clawpack/euler/2d/quadrants/quadrants_user.h \
	applications/clawpack/euler/2d/rp/euler_user_fort.h

quadrants_inifiles = \
	applications/clawpack/euler/2d/quadrants/fclaw_options.ini \
	applications/clawpack/euler/2d/quadrants/regression.ini

applications_clawpack_euler_2d_quadrants_quadrants_SOURCES += \
	$(quadrants_headers) \
	$(quadrants_inifiles)

applications_clawpack_euler_2d_quadrants_quadrants_CPPFLAGS = \
        $(AM_CPPFLAGS) \
        $(FCLAW_CLAWPACK46_CPPFLAGS) \
        $(FCLAW_CLAWPACK5_CPPFLAGS) \
        $(FCLAW_CLAWPATCH_CPPFLAGS)

applications_clawpack_euler_2d_quadrants_quadrants_LDADD = \
        $(LDADD) \
        $(FCLAW_CLAWPACK46_LDADD) \
        $(FCLAW_CLAWPACK5_LDADD)  \
        $(FCLAW_CLAWPATCH_LDADD)  \
        $(FCLAW_LDADD)
