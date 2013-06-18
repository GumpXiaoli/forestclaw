       subroutine qinit(maxmx,maxmy,meqn,mbc,mx,my,xlower,ylower,
     &                   dx,dy,q,maux,aux)
c     =====================================================
c
c      # Set initial conditions for q
c      # -------To test well-balancing ----------
c
       implicit double precision (a-h,o-z)
       dimension q(1-mbc:maxmx+mbc, 1-mbc:maxmy+mbc, meqn)
       dimension aux(1-mbc:maxmx+mbc, 1-mbc:maxmy+mbc, maux)
       common /comic/ Px,Py,Pz
       common /comsphere/ Rsphere, Omega
       common /cprob/ ampl, tol1, tol2

       common /comfine/ dxmin, dymin
       common /comq0/ q0sum


c
      pi = 4.d0*datan(1.d0)

c     # symmetry axis (Px,Py,Pz) set in setprob.f

       do 20 i=1,mx
	  xc = xlower + (i-0.5d0)*dx
          do 20 j=1,my
	     yc = ylower + (j-0.5d0)*dy
c
c            # set the clawpack initial values:
             bot = aux(i,j,19)
             q(i,j,1) = -bot
             q(i,j,2) = 0.d0
             q(i,j,3) = 0.d0
             q(i,j,4) = 0.d0


c            # add a small amplitude Gaussian peak:
c            # ampl is now read from setprob.data
c            ampl = 5000.d0
c            ampl = 10.d0
             call mapc2m(xc,yc,xp,yp,zp)
             theta = dasin((xp*Px + yp*Py + zp*Pz) / Rsphere)
             theta2 = pi/6.d0
             q1 = dexp(-1000.d0*(theta-theta2)**2)
             R = dmax1(dsqrt(xp**2 + yp**2), 1.d-10)
             u0 = 2.d2*ampl*q1 / (Rsphere*R)
             if (q1 .gt. 1.d-14) then
                q(i,j,1) = q(i,j,1) + ampl*q1
                q(i,j,2) = u0*xp*zp
                q(i,j,3) = u0*yp*zp
                q(i,j,4) = -u0*(xp**2+yp**2)
                endif

  20         continue

c             rf = nint(dx/dxmin)
c             if (rf .lt. 16) then
c                return
c             endif
c
c             q0sum = 0
c             do i = 1,mx
c                do j = 1,my
c                   area = aux(i,j,1)
c                   q0sum = q0sum + q(i,j,1)*area
c                enddo
c             enddo

       return
       end