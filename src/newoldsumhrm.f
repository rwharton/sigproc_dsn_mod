C **************************************************************
      SUBROUTINE NEWOLDSUMHRM (SP,SPH,NF,NF1,P1,P2,P4,P8,P16)
C **************************************************************
C Quick and dirty harmonic summer
C SP - fundamental
C P2/P4/P8/P16 2, 4, 8, and 16 sums
C sph is workspace and equal to nf
C nf1 is the minimum period you are considering in bins

      IMPLICIT NONE
c      include 'seek.inc'
      INTEGER NF, NF1
      REAL SP(NF), SPH(*)
      REAL P1(*),P2(*),P4(*),P8(*),P16(*)

      INTEGER NF2,NF4,NF8,NF16
      INTEGER N, K
      INTEGER LA,LB,LC,LD,LE,LF,LG,LH
      INTEGER KA, KB
      INTEGER JA,JB,JC,JD

      NF2 = MAX(1,MIN(2*NF1-1,NF))
      NF4 = MAX(1,MIN(4*NF1-2,NF))
      NF8 = MAX(1,MIN(8*NF1-4,NF))
      NF16= MAX(1,MIN(16*NF1-8,NF))
      do n=1,nf
         p1(n)=sp(n)
      enddo
      DO N=1,NF
         SPH(N)=0.0
      ENDDO

      K = (NF2+1)/2

C      write(*,*) 'nf = ', nf, 'nf2 = ', nf2, ' k= ', k

      DO 20 N=NF2,NF-1,2
c         if (N+1 .eq. 21641) then
c            write(*,*) 'n+1 =',n+1,'k=',k, sp(1+n), sp(k), 
c     &          sp(1+n)+sp(k)
c         endif
c         if (N .eq. 21641) then
c            write(*,*) 'n =',n,'k=',k, sp(n), sp(k), 
c     &          sp(n)+sp(k)
c         endif
         SPH(N)=SP(N)+SP(K)
         SPH(1+N)=SP(1+N)+SP(K)
         K=K+1
   20 CONTINUE
      do n=1,nf
         p2(n)=sph(n)
      enddo

      write(*,*)'sph(74612)=',sph(74611),sph(74612),sph(74613)
      
      KA = (NF4+2)/4
      KB = (3*NF4+2)/4
      DO 40 N=NF4,NF-3,4
        if (N .eq. 149223) then
           write(*,*) 'n =',n,'ka=',ka, 'kb=',kb,
     &      sph(1+n), sp(ka), 
     &          sp(kb)
        endif
        if (N+1 .eq. 149223) then
           write(*,*) 'n+1 =',n+1,'ka=',ka, 'kb=',kb,
     &      sph(1+n), sp(ka), 
     &          sp(kb)
        endif
        if (N+2 .eq. 149223) then
           write(*,*) 'n+2 =',n+2,'ka=',ka, 'kb+1=',kb+1,
     &      sph(1+n), sp(ka), 
     &          sp(kb+1)
        endif
        if (N+3 .eq. 149223) then
           write(*,*) 'n+3 =',n+3,'ka=',ka, 'kb+2=',kb+2,
     &      sph(1+n), sp(ka), 
     &          sp(kb+2)
        endif
         SPH(N)=SPH(N)+SP(KA)+SP(KB)
         SPH(1+N)=SPH(1+N)+SP(KA)+SP(KB)
         SPH(2+N)=SPH(2+N)+SP(KA)+SP(1+KB)
         SPH(3+N)=SPH(3+N)+SP(KA)+SP(2+KB)
         KA = KA + 1
         KB = KB + 3
   40 CONTINUE
      do n=1,nf
         P4(n)=sph(n)
      enddo

      JA = (NF8+4)/8
      JB = (3*NF8+4)/8
      JC = (5*NF8+4)/8
      JD = (7*NF8+4)/8
      DO 80 N=NF8,NF-7,8
         SPH(  N)=SPH(  N)+SP(JA)+SP(  JB)+SP(  JC)+SP(  JD)
         SPH(1+N)=SPH(1+N)+SP(JA)+SP(  JB)+SP(  JC)+SP(  JD)
         SPH(2+N)=SPH(2+N)+SP(JA)+SP(  JB)+SP(1+JC)+SP(1+JD)
         SPH(3+N)=SPH(3+N)+SP(JA)+SP(1+JB)+SP(1+JC)+SP(2+JD)
         SPH(4+N)=SPH(4+N)+SP(JA)+SP(1+JB)+SP(2+JC)+SP(3+JD)
         SPH(5+N)=SPH(5+N)+SP(JA)+SP(1+JB)+SP(3+JC)+SP(4+JD)
         SPH(6+N)=SPH(6+N)+SP(JA)+SP(2+JB)+SP(3+JC)+SP(5+JD)
         SPH(7+N)=SPH(7+N)+SP(JA)+SP(2+JB)+SP(4+JC)+SP(6+JD)
         JA = JA + 1
         JB = JB + 3
         JC = JC + 5
         JD = JD + 7
   80 CONTINUE
      do n=1,nf
         P8(n)=sph(n)
      enddo

      LA = (   NF16+8)/16
      LB = (3*NF16+8)/16
      LC = (5*NF16+8)/16
      LD = (7*NF16+8)/16
      LE = (9*NF16+8)/16
      LF = (11*NF16+8)/16
      LG = (13*NF16+8)/16
      LH = (15*NF16+8)/16
      DO 160 N=NF16,NF-15,16
         SPH(  N)=SPH(  N)+SP(LA)+SP(  LB)+SP(  LC)+SP(  LD)+SP(  LE)+
     +    SP(   LF)+SP(   LG)+SP(   LH)
         SPH(1+N)=SPH(1+N)+SP(LA)+SP(  LB)+SP(  LC)+SP(  LD)+SP(  LE)+
     +    SP(   LF)+SP(   LG)+SP(   LH)
         SPH(2+N)=SPH(2+N)+SP(LA)+SP(  LB)+SP(  LC)+SP(  LD)+SP(1+LE)+
     +    SP( 1+LF)+SP( 1+LG)+SP( 1+LH)
         SPH(3+N)=SPH(3+N)+SP(LA)+SP(  LB)+SP(  LC)+SP(1+LD)+SP(1+LE)+
     +    SP( 2+LF)+SP( 2+LG)+SP( 2+LH)
         SPH(4+N)=SPH(4+N)+SP(LA)+SP(  LB)+SP(1+LC)+SP(1+LD)+SP(2+LE)+
     +    SP( 2+LF)+SP( 3+LG)+SP( 3+LH)
         SPH(5+N)=SPH(5+N)+SP(LA)+SP(  LB)+SP(1+LC)+SP(2+LD)+SP(2+LE)+
     +    SP( 3+LF)+SP( 4+LG)+SP( 4+LH)
         SPH(6+N)=SPH(6+N)+SP(LA)+SP(1+LB)+SP(1+LC)+SP(2+LD)+SP(3+LE)+
     +    SP( 4+LF)+SP( 4+LG)+SP( 5+LH)
         SPH(7+N)=SPH(7+N)+SP(LA)+SP(1+LB)+SP(2+LC)+SP(3+LD)+SP(3+LE)+
     +    SP( 4+LF)+SP( 5+LG)+SP( 6+LH)
         SPH(8+N)=SPH(8+N)+SP(LA)+SP(1+LB)+SP(2+LC)+SP(3+LD)+SP(4+LE)+
     +    SP( 5+LF)+SP( 6+LG)+SP( 7+LH)
         SPH(9+N)=SPH(9+N)+SP(LA)+SP(1+LB)+SP(2+LC)+SP(3+LD)+SP(5+LE)+
     +    SP( 6+LF)+SP( 7+LG)+SP( 8+LH)
         SPH(10+N)=SPH(10+N)+SP(LA)+SP(1+LB)+SP(3+LC)+SP(4+LD)+SP(5+LE)+
     +    SP( 6+LF)+SP( 8+LG)+SP( 9+LH)
         SPH(11+N)=SPH(11+N)+SP(LA)+SP(2+LB)+SP(3+LC)+SP(4+LD)+SP(6+LE)+
     +    SP( 7+LF)+SP( 8+LG)+SP(10+LH)
         SPH(12+N)=SPH(12+N)+SP(LA)+SP(2+LB)+SP(3+LC)+SP(5+LD)+SP(6+LE)+
     +    SP( 8+LF)+SP( 9+LG)+SP(11+LH)
         SPH(13+N)=SPH(13+N)+SP(LA)+SP(2+LB)+SP(4+LC)+SP(5+LD)+SP(7+LE)+
     +    SP( 8+LF)+SP(10+LG)+SP(12+LH)
         SPH(14+N)=SPH(14+N)+SP(LA)+SP(2+LB)+SP(4+LC)+SP(6+LD)+SP(7+LE)+
     +    SP( 9+LF)+SP(11+LG)+SP(13+LH)
         SPH(15+N)=SPH(15+N)+SP(LA)+SP(2+LB)+SP(4+LC)+SP(6+LD)+SP(8+LE)+
     +    SP(10+LF)+SP(12+LG)+SP(14+LH)
         LA = LA + 1
         LB = LB + 3
         LC = LC + 5
         LD = LD + 7
         LE = LE + 9
         LF = LF + 11
         LG = LG + 13
         LH = LH + 15
  160 CONTINUE
      do n=1,nf
         P16(n)=sph(n)
      enddo

      RETURN
C
C END OF SUBROUTINE SUMHRM
C
      END
