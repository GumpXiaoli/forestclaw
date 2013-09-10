/*
Copyright (c) 2012 Carsten Burstedde, Donna Calhoun
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "amr_includes.H"
#include "amr_waveprop.H"
#include "slotted_disk_user.H"

#ifdef __cplusplus
extern "C"
{
#if 0
}
#endif
#endif


void slotted_disk_link_solvers(fclaw2d_domain_t *domain)
{
    fclaw2d_solver_functions_t* sf = get_solver_functions(domain);
    sf->use_single_step_update = fclaw_true;
    sf->use_mol_update = fclaw_false;
    sf->f_patch_setup              = &slotted_disk_patch_setup;
    sf->f_patch_initialize         = &slotted_disk_qinit;
    sf->f_patch_single_step_update = &slotted_disk_update;

    fclaw2d_regrid_functions_t *rf = get_regrid_functions(domain);
    rf->f_patch_tag4refinement = &slotted_disk_patch_tag4refinement;
    rf->f_patch_tag4coarsening = &slotted_disk_patch_tag4coarsening;

    fclaw2d_output_functions_t *of = get_output_functions(domain);
    of->f_patch_write_header = &slotted_disk_parallel_write_header;
    of->f_patch_write_output = &slotted_disk_parallel_write_output;

    /* This is needed to get constructors for user data */
    amr_waveprop_link_to_clawpatch();
}

void slotted_disk_setprob(fclaw2d_domain_t* domain)
{
    int vflag = 1;       // specify edge normal velocities
    int init_choice = 4; // for slotted disk
    setprob_transport_(vflag,init_choice);
}

void slotted_disk_patch_setup(fclaw2d_domain_t *domain,
                              fclaw2d_patch_t *this_patch,
                              int this_block_idx,
                              int this_patch_idx)
{
    // In case this is needed by the setaux routine
    set_block_(&this_block_idx);

    /* -------------------------------------------------------------- */
    // Global parameters
    const amr_options_t *gparms = get_domain_parms(domain);
    int mx = gparms->mx;
    int my = gparms->my;
    int mbc = gparms->mbc;

    /* -------------------------------------------------------------- */
    // Patch specific parameters
    ClawPatch *cp = get_clawpatch(this_patch);
    double xlower = cp->xlower();
    double ylower = cp->ylower();
    double dx = cp->dx();
    double dy = cp->dy();

    /* -------------------------------------------------------------- */
    // allocate space for the aux array
    amr_waveprop_define_auxarray(domain,cp);

    /* -------------------------------------------------------------- */
    // Pointers needed to pass to class setaux call, and other setaux
    // specific arguments
    double *aux;
    int maux;
    amr_waveprop_get_auxarray(domain,cp,&aux,&maux);

    /* -------------------------------------------------------------- */
    // Modified clawpack setaux routine that passes in mapping terms
    double *xp = cp->xp();
    double *yp = cp->yp();
    double *zp = cp->zp();
    double *xd = cp->xd();
    double *yd = cp->yd();
    double *zd = cp->zd();
    double *area = cp->area();

    setaux_transport_(mx,my,mbc,xlower,ylower,dx,dy,
                      maux,aux,xp,yp,zp,xd,yd,zd,area);
}

void slotted_disk_qinit(fclaw2d_domain_t *domain,
                        fclaw2d_patch_t *this_patch,
                        int this_block_idx,
                        int this_patch_idx)
{
    // In case this is needed by the setaux routine
    set_block_(&this_block_idx);

    /* -------------------------------------------------------------- */
    // Global parameters
    const amr_options_t *gparms = get_domain_parms(domain);
    int mx = gparms->mx;
    int my = gparms->my;
    int mbc = gparms->mbc;
    int meqn = gparms->meqn;

    /* -------------------------------------------------------------- */
    // Patch specific parameters
    ClawPatch *cp = get_clawpatch(this_patch);
    double xlower = cp->xlower();
    double ylower = cp->ylower();
    double dx = cp->dx();
    double dy = cp->dy();

    /* -------------------------------------------------------------- */
    // Pointers needed to pass to Fortran
    double* q = cp->q();

    double *aux;
    int maux;
    amr_waveprop_get_auxarray(domain,cp,&aux,&maux);

    double *xp = cp->xp();
    double *yp = cp->yp();
    double *zp = cp->zp();

    /* -------------------------------------------------------------- */
    qinit_transport_(mx,my,meqn,mbc,xlower,ylower,dx,dy,q,maux,aux,
                     xp,yp,zp);
}

void slotted_disk_patch_physical_bc(fclaw2d_domain *domain,
                                    fclaw2d_patch_t *this_patch,
                                    int this_block_idx,
                                    int this_patch_idx,
                                    double t,
                                    double dt,
                                    fclaw_bool intersects_bc[])
{
    // The sphere has no physical boundaries
}


void slotted_disk_b4step2(fclaw2d_domain_t *domain,
                          fclaw2d_patch_t *this_patch,
                          int this_block_idx,
                          int this_patch_idx,
                          double t,
                          double dt)
{
    // In case this is needed by the setaux routine
    set_block_(&this_block_idx);

    /* -------------------------------------------------------------- */
    // Global parameters
    const amr_options_t *gparms = get_domain_parms(domain);
    int mx = gparms->mx;
    int my = gparms->my;
    int mbc = gparms->mbc;

    /* -------------------------------------------------------------- */
    // Patch specific parameters
    ClawPatch *cp = get_clawpatch(this_patch);
    double dx = cp->dx();
    double dy = cp->dy();

    /* -------------------------------------------------------------- */
    double *aux;
    int maux;
    amr_waveprop_get_auxarray(domain,cp,&aux,&maux);


    double *xd = cp->xd();
    double *yd = cp->yd();
    double *zd = cp->zd();

    /* -------------------------------------------------------------- */
    b4step2_transport_(mx,my,mbc,dx,dy,t,maux,aux,xd,yd,zd);
}

double slotted_disk_update(fclaw2d_domain_t *domain,
                           fclaw2d_patch_t *this_patch,
                           int this_block_idx,
                           int this_patch_idx,
                           double t,
                           double dt)
{
    slotted_disk_b4step2(domain,this_patch,this_block_idx,
                         this_patch_idx,t,dt);

    double maxcfl = amr_waveprop_step2(domain,this_patch,this_block_idx,
                                       this_patch_idx,t,dt);

    return maxcfl;
}

/* -----------------------------------------------------------------
   Default routine for tagging patches for refinement and coarsening
   ----------------------------------------------------------------- */
fclaw_bool
    slotted_disk_patch_tag4refinement(fclaw2d_domain_t *domain,
                                      fclaw2d_patch_t *this_patch,
                                      int this_block_idx,
                                      int this_patch_idx,
                                      int initflag)
{
    /* -------------------------------------------------------------- */
    // Global parameters
    const amr_options_t *gparms = get_domain_parms(domain);
    int mx = gparms->mx;
    int my = gparms->my;
    int mbc = gparms->mbc;
    int meqn = gparms->meqn;

    /* -------------------------------------------------------------- */
    // Patch specific parameters
    ClawPatch *cp = get_clawpatch(this_patch);
    double xlower = cp->xlower();
    double ylower = cp->ylower();
    double dx = cp->dx();
    double dy = cp->dy();

    /* -------------------------------------------------------------- */
    // Pointers needed to pass to Fortran
    double* q = cp->q();

    int tag_patch = 0;  // == 0 or 1

    slotted_disk_tag4refinement_(mx,my,mbc,meqn,xlower,ylower,dx,dy,q,
                                 initflag, this_block_idx,tag_patch);
    return tag_patch == 1;
}

fclaw_bool slotted_disk_patch_tag4coarsening(fclaw2d_domain_t *domain,
                                       fclaw2d_patch_t *this_patch,
                                       int blockno_idx,
                                       int patchno)
{
    /* ----------------------------------------------------------- */
    // Global parameters
    const amr_options_t *gparms = get_domain_parms(domain);
    int mx = gparms->mx;
    int my = gparms->my;
    int mbc = gparms->mbc;
    int meqn = gparms->meqn;

    /* ----------------------------------------------------------- */
    // Patch specific parameters
    ClawPatch *cp = get_clawpatch(this_patch);
    double xlower = cp->xlower();
    double ylower = cp->ylower();
    double dx = cp->dx();
    double dy = cp->dy();

    /* ------------------------------------------------------------ */
    // Pointers needed to pass to Fortran
    double* q = cp->q();

    int tag_patch;  // == 0 or 1
    slotted_disk_tag4coarsening_(mx,my,mbc,meqn,xlower,ylower,dx,dy,
                                 q,tag_patch);
    return tag_patch == 0;
}

void slotted_disk_parallel_write_header(fclaw2d_domain_t* domain,
                                        int iframe, int ngrids)
{
    const amr_options_t *gparms = get_domain_parms(domain);
    double time = get_domain_time(domain);

    printf("Matlab output Frame %d  at time %16.8e\n\n",iframe,time);

    // Increase the number of fields by 1 so we can printout the mpi rank
    int mfields = gparms->meqn + 1;
    int maux = 0;
    slotted_disk_write_tfile_(iframe,time,mfields,ngrids,maux);

    /* This opens file 'fort.qXXXX' for replace
       (where XXXX = <zero padding><iframe>, e.g. 0001, 0010, 0114),
       and closes the file. */
    new_qfile_(iframe);
}


void slotted_disk_parallel_write_output(fclaw2d_domain_t *domain,
                                        fclaw2d_patch_t *this_patch,
                                        int this_block_idx,
                                        int this_patch_idx,
                                        int iframe,int num,int level)
{
    // In case this is needed by the setaux routine
    set_block_(&this_block_idx);

    /* -------------------------------------------------------------- */
    // Global parameters
    const amr_options_t *gparms = get_domain_parms(domain);
    int mx = gparms->mx;
    int my = gparms->my;
    int mbc = gparms->mbc;
    int meqn = gparms->meqn;

    /* -------------------------------------------------------------- */
    // Patch specific parameters
    ClawPatch *cp = get_clawpatch(this_patch);
    double xlower = cp->xlower();
    double ylower = cp->ylower();
    double dx = cp->dx();
    double dy = cp->dy();

    /* -------------------------------------------------------------- */
    // Pointers needed to pass to Fortran
    double* q = cp->q();

    /* -------------------------------------------------------------- */
    int matlab_level = level + 1;

    int mpirank = domain->mpirank;
    /* This opens a file for append and writes in the 'clawout' style. */
    slotted_disk_write_qfile_(mx,my,meqn,mbc,xlower,ylower,dx,dy,q,
                              iframe,num,matlab_level,this_block_idx,
                              mpirank);
}



#ifdef __cplusplus
#if 0
{
#endif
}
#endif