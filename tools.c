/* tools.c 
*/
#include "pamlmodule.h"

/************************
             sequences 
*************************/
extern int damage;
extern double *kaks_values;

char BASEs[]="TCAGUYRMKSWHBVDN?-";
char nBASEs[]={1,1,1,1, 1,2,2,2,2,2,2, 3,3,3,3, 4,4,4};
char *EquateNUC[]={"T","C","A","G", "T", "TC","AG","CA","TG","CG","TA",
     "TCA","TCG","CAG","TAG", "TCAG","TCAG","TCAG"};
char AAs[] = "ARNDCQEGHILKMFPSTWYV*-?";
char AA3Str[]=
     {"AlaArgAsnAspCysGlnGluGlyHisIleLeuLysMetPheProSerThrTrpTyrVal***"};
char BINs[] ="TC";
char Nsensecodon[]={61, 60, 61, 62, 62, 63, 62, 62, 61, 62, 62};
int GeneticCode[][64] = 
     {{13,13,10,10,15,15,15,15,18,18,-1,-1, 4, 4,-1,17,
       10,10,10,10,14,14,14,14, 8, 8, 5, 5, 1, 1, 1, 1,
        9, 9, 9,12,16,16,16,16, 2, 2,11,11,15,15, 1, 1,
       19,19,19,19, 0, 0, 0, 0, 3, 3, 6, 6, 7, 7, 7, 7}, /* 0:universal */

      {13,13,10,10,15,15,15,15,18,18,-1,-1, 4, 4,17,17,
       10,10,10,10,14,14,14,14, 8, 8, 5, 5, 1, 1, 1, 1,
        9, 9,12,12,16,16,16,16, 2, 2,11,11,15,15,-1,-1,
       19,19,19,19, 0, 0, 0, 0, 3, 3, 6, 6, 7, 7, 7, 7}, /* 1:vertebrate mt.*/

      {13,13,10,10,15,15,15,15,18,18,-1,-1, 4, 4,-1,17,
       16,16,16,16,14,14,14,14, 8, 8, 5, 5, 1, 1, 1, 1,
        9, 9,12,12,16,16,16,16, 2, 2,11,11,15,15, 1, 1,
       19,19,19,19, 0, 0, 0, 0, 3, 3, 6, 6, 7, 7, 7, 7}, /* 2:yeast mt. */

      {13,13,10,10,15,15,15,15,18,18,-1,-1, 4, 4,17,17,
       10,10,10,10,14,14,14,14, 8, 8, 5, 5, 1, 1, 1, 1,
        9, 9, 9,12,16,16,16,16, 2, 2,11,11,15,15, 1, 1,
       19,19,19,19, 0, 0, 0, 0, 3, 3, 6, 6, 7, 7, 7, 7}, /* 3:mold mt. */

      {13,13,10,10,15,15,15,15,18,18,-1,-1, 4, 4,17,17,
       10,10,10,10,14,14,14,14, 8, 8, 5, 5, 1, 1, 1, 1,
        9, 9,12,12,16,16,16,16, 2, 2,11,11,15,15,15,15,
       19,19,19,19, 0, 0, 0, 0, 3, 3, 6, 6, 7, 7, 7, 7}, /* 4:invertebrate mt. */

      {13,13,10,10,15,15,15,15,18,18, 5, 5, 4, 4,-1,17,
       10,10,10,10,14,14,14,14, 8, 8, 5, 5, 1, 1, 1, 1,
        9, 9, 9,12,16,16,16,16, 2, 2,11,11,15,15, 1, 1,
       19,19,19,19, 0, 0, 0, 0, 3, 3, 6, 6, 7, 7, 7, 7}, /* 5:ciliate nuclear*/

      {13,13,10,10,15,15,15,15,18,18,-1,-1, 4, 4,17,17,
       10,10,10,10,14,14,14,14, 8, 8, 5, 5, 1, 1, 1, 1,
        9, 9, 9,12,16,16,16,16, 2, 2, 2,11,15,15,15,15,
       19,19,19,19, 0, 0, 0, 0, 3, 3, 6, 6, 7, 7, 7, 7}, /* 6:echinoderm mt.*/

      {13,13,10,10,15,15,15,15,18,18,-1,-1, 4, 4, 4,17,
       10,10,10,10,14,14,14,14, 8, 8, 5, 5, 1, 1, 1, 1,
        9, 9, 9,12,16,16,16,16, 2, 2,11,11,15,15, 1, 1,
       19,19,19,19, 0, 0, 0, 0, 3, 3, 6, 6, 7, 7, 7, 7}, /* 7:euplotid mt. */

      {13,13,10,10,15,15,15,15,18,18,-1,-1, 4, 4,-1,17,
       10,10,10,15,14,14,14,14, 8, 8, 5, 5, 1, 1, 1, 1,
        9, 9, 9,12,16,16,16,16, 2, 2,11,11,15,15, 1, 1,
       19,19,19,19, 0, 0, 0, 0, 3, 3, 6, 6, 7, 7, 7, 7},
                                                 /* 8:alternative yeast nu.*/

      {13,13,10,10,15,15,15,15,18,18,-1,-1, 4, 4,17,17,
       10,10,10,10,14,14,14,14, 8, 8, 5, 5, 1, 1, 1, 1,
        9, 9,12,12,16,16,16,16, 2, 2,11,11,15,15, 7, 7,
       19,19,19,19, 0, 0, 0, 0, 3, 3, 6, 6, 7, 7, 7, 7}, /* 9:ascidian mt. */

      {13,13,10,10,15,15,15,15,18,18,-1, 5, 4, 4,-1,17,
       10,10,10,10,14,14,14,14, 8, 8, 5, 5, 1, 1, 1, 1,
        9, 9, 9,12,16,16,16,16, 2, 2,11,11,15,15, 1, 1,
       19,19,19,19, 0, 0, 0, 0, 3, 3, 6, 6, 7, 7, 7, 7} /* 10:blepharisma nu.*/
     } ;                                         /* GeneticCode[icode][#codon] */



int noisy=0, Iround=0, NFunCall=0, NEigenQ, NPMatUVRoot;
double SIZEp=0;


int picksite (char *z, int l, int begin, int gap, char *result)
{
/* pick every gap-th site, e.g., the third codon position for example.
*/
   int il=begin;

   for (il=0, z+=begin; il<l; il+=gap,z+=gap) *result++ = *z;
   return(0);
}

int CodeChara (char b, int seqtype)
{
/* This codes nucleotides or amino acids into 0, 1, 2, ...
*/
   int i, n=(seqtype<=1?4:(seqtype==2?20:2));
   char *pch=(seqtype<=1?BASEs:(seqtype==2?AAs:BINs));

   if (seqtype<=1)
      switch (b) {
         case 'T':  case 'U':   return(0);
         case 'C':              return(1);
         case 'A':              return(2);
         case 'G':              return(3);
      }
   else
      FOR(i,n) if (b==pch[i]) return (i);
   if(noisy>=9) printf ("\nwarning: strange character '%c' ", b);
   return (-1);
}

int dnamaker (char z[], int ls, double pi[])
{
/* sequences z[] are coded 0,1,2,3
*/
   int i, j;
   double p[4], r;

   xtoy(pi, p, 4);
   for (i=1; i<4; i++) p[i]+=p[i-1];
   if (fabs(p[3]-1) > 1e-5) error2("sum pi != 1..");
   for (i=0; i<ls; i++) {
      for(j=0,r=rndu();j<4;j++) if(r<p[j]) break;
      z[i]=(char)j;
   }
   return (0);
}

int transform (char *z, int ls, int direction, int seqtype)
{
/* direction==1 from TCAG to 0123, ==0 from 0123 to TCGA.
*/
   int il, status=0;
   char *p, *pch=((seqtype==0||seqtype==1)?BASEs:(seqtype==2?AAs:BINs));

   if (direction)
      for (il=0,p=z; il<ls; il++,p++)
         { if ((*p=(char)CodeChara(*p, seqtype))==(char)(-1))  status=-1; }
   else 
      for (il=0,p=z; il<ls; il++,p++)  *p=pch[*p];
   return (status);
}


int f_mono_di (FILE *fout, char *z, int ls, int iring,
    double fb1[], double fb2[], double CondP[])
{
/* get mono- di- nucleitide frequencies.
*/
   int i,j, il;
   char *s;
   double t1, t2;

   t1 = 1./(double) ls;  
   t2=1./(double) (ls-1+iring);
   for (i=0; i<4; fb1[i++]=0.0) for (j=0; j<4; fb2[i*4+j++]=0.0) ;
   for (il=0, s=z; il<ls-1; il++, s++) {
      fb1[*s-1] += t1;
      fb2[(*s-1)* 4 + *(s+1)-1 ] += t2;
   }
   fb1[*s-1] += t1;
   if (iring) fb2[(*s-1)*4 + z[0]-1] += t2;
   for (i=0; i<4; i++)  for (j=0; j<4; j++) CondP[i*4+j] = fb2[i*4+j]/fb1[i];
   fprintf(fout, "\nmono-\n") ;
   FOR (i,4) fprintf(fout, "%12.4f", fb1[i]) ;   
   fprintf(fout, "\n\ndi-  & conditional P\n") ;       
   FOR (i,4) {
      FOR (j,4) fprintf(fout, "%9.4f%7.4f  ", fb2[i*4+j], CondP[i*4+j]) ;
      FPN(fout);
   }
   FPN(fout);
   return (0);
}

int PickExtreme (FILE *fout, char *z, int ls, int iring, int lfrag, int *ffrag)
{
/* picking up (lfrag)-tuples with extreme frequencies.
*/
   char *pz=z;
   int i, j, isf, n=(1<<2*lfrag), lvirt=ls-(lfrag-1)*(1-iring);
   double fb1[4], fb2[4*4], p_2[4*4];
   double prob1, prob2, ne1, ne2, u1, u2, ualpha=2.0;
   int ib[10];

   f_mono_di(fout, z, ls, iring, fb1, fb2, p_2 );
   if (iring) {
      error2("change PickExtreme()");
      FOR (i, lfrag-1)  z[ls+i]=z[i];       /* dangerous */
      z[ls+i]=(char) 0;
   }
   printf ("\ncounting %d tuple frequencies", lfrag);
   FOR (i, n) ffrag[i]=0;
   for (i=0; i<lvirt; i++, pz++) {
      for (j=0,isf=0; j<lfrag; j++)  isf=isf*4+(int)pz[j]-1;
      ffrag[isf] ++;
   }
   /* analyze */
   for (i=0; i<n; i++) {
      for (j=0,isf=i; j<lfrag; ib[lfrag-1-j]=isf%4,isf=isf/4,j++) ;
      for (j=0,prob1=1.0; j<lfrag; prob1 *= fb1[ ib[j++] ] ) ;
      for (j=0,prob2=fb1[ib[0]]; j<lfrag-1; j++)
         prob2 *= p_2[ib[j]*4+ib[j+1]];
      ne1 = (double) lvirt * prob1;
      ne2 = (double) lvirt * prob2;
      if (ne1<=0.0) ne1=0.5;
      if (ne2<=0.0) ne2=0.5;
      u1=((double) ffrag[i]-ne1) / sqrt (ne1);
      u2=((double) ffrag[i]-ne2) / sqrt (ne2);
      if ( fabs(u1)>ualpha /* && fabs(u2)>ualpha */ ) {
         fprintf (fout,"\n");
         FOR (j, lfrag) fprintf (fout,"%1c", BASEs[ib[j]]);
         fprintf (fout,"%6d %8.1f%7.2f %8.1f%7.2f ",ffrag[i],ne1,u1,ne2,u2);
         if (u1<-ualpha && u2<-ualpha)     fprintf (fout, " %c", '-');
         else if (u1>ualpha && u2>ualpha)  fprintf (fout, " %c", '+');
         else if (u1*u2<0 && fabs(u1) > ualpha && fabs(u2) > ualpha)
            fprintf (fout, " %c", '?');
         else
            fprintf (fout, " %c", ' ');
      }
   }
   return (0);
}

int zztox ( int n31, int l, char *z1, char *z2, double *x )
{
/*   x[n31][4][4]   */
   double t = 1./(double) (l / n31);
   int i, ib[2];
   int il;

   zero (x, n31*16);
   for (i=0; i<n31; i++)  {
      for (il=0; il<l; il += n31) {
         ib[0] = z1[il+i] - 1;
         ib[1] = z2[il+i] - 1;
         x [ i*16+ib[0]*4+ib[1] ] += t;
      }
/*
      fprintf (f1, "\nThe difference matrix X %6d\tin %6d\n", i+1,n31);
      for (j=0; j<4; j++) {
         for (k=0; k<4; k++) fprintf(f1, "%10.2f", x[i][j][k]);
         fputc ('\n', f1);
      }
*/
   }
   return (0);
}

int testXMat (double x[])
{
/* test whether X matrix is acceptable (0) or not (-1) */
   int it=0, i,j;
   double t;
   for (i=0,t=0; i<4; i++) FOR (j,4) {
      if (x[i*4+j]<0 || x[i*4+j]>1)  it=-1;
      t += x[i*4+j];
   }
   if (fabs(t-1) > 1e-4) it =-1;
   return(it);
}


int difcodonNG (char codon1[], char codon2[], double *SynSite,double *AsynSite, 
    double *SynDif, double *AsynDif, int transfed, int icode)
{
/* # of synonymous and non-synonymous sites and differences.
   Nei, M. and T. Gojobori (1986)
   returns the number of differences between two codons.
   The two codons (codon1 & codon2) do not contain ambiguity characters. 
   dmark[i] (=0,1,2) is the i_th different codon position, with i=0,1,ndiff
   step[j] (=0,1,2) is the codon position to be changed at step j (j=0,1,ndiff)
   b[i][j] (=0,1,2,3) is the nucleotide at position j (0,1,2) in codon i (0,1)

   I made some arbitrary decisions when the two codons have ambiguity characters
   20 September 2002.
*/
   int i,j,k, i1,i2, iy[2], iaa[2],ic[2];
   int ndiff,npath,nstop,sdpath,ndpath,dmark[3],step[3],b[2][3],bt1[3],bt2[3];
   int by[3] = {16, 4, 1};
   char str[4]="";

   for (i=0,*SynSite=0,nstop=0; i<2; i++) {
      for (j=0,iy[0]=iy[1]=0; j<3; j++)   {
         if (transfed) b[i][j]=(i?codon1[j]:codon2[j]);
         else          b[i][j]=(int)CodeChara((char)(i?codon1[j]:codon2[j]),0);
         iy[i]+=by[j]*b[i][j];
         if(b[i][j]<0||b[i][j]>3) { 
            if(noisy>=9) 
               printf("\nwarning ambiguity in difcodonNG: %s %s", codon1,codon2);
            *SynSite = 0.5;  *AsynSite = 2.5;
            *SynDif = (codon1[2]!=codon2[2])/2;
            *AsynDif = *SynDif + (codon1[0]!=codon2[0])+(codon1[1]!=codon2[1]);
            return((int)(*SynDif + *AsynDif));
         }
      }
      iaa[i]=GeneticCode[icode][iy[i]];
	      
      //if(iaa[i]==-1) printf("\nNG86: stop codon %s.\n",getcodon(str,iy[i]));
	      
      for(j=0; j<3; j++) 
         FOR (k,4) {
            if (k==b[i][j]) continue;
            i1=GeneticCode[icode][iy[i] + (k-b[i][j])*by[j]];
            if (i1==-1)            nstop++;
            else if (i1==iaa[i])  (*SynSite)++;
         }
   }
   *SynSite*=3/18.;     /*  2 codons, 2*9 possibilities. */
   *AsynSite=3*(1-nstop/18.) - *SynSite;

#if 0    /* MEGA 1.1 error */
   *AsynSite=3 - *SynSite;
#endif

   ndiff=0;  *SynDif=*AsynDif=0;
   FOR (k,3) dmark[k]=-1;
   FOR (k,3) if (b[0][k]-b[1][k]) dmark[ndiff++]=k;
   if (ndiff==0) return(0);
   npath=1;  nstop=0;   if(ndiff>1) npath=(ndiff==2)?2:6 ;
   if (ndiff==1) { 
      if (iaa[0]==iaa[1]) (*SynDif)++;
      else                (*AsynDif)++;
   }
   else {   /* ndiff=2 or 3 */
      FOR (k, npath)     {
         FOR (i1,3)  step[i1]=-1;
             if (ndiff==2) 
                 { step[0]=dmark[k];   step[1]=dmark[1-k];  }
              else {
                 step[0]=k/2;   step[1]=k%2;
                 if (step[0]<=step[1]) step[1]++;
                 step[2]=3-step[0]-step[1];
              }
              FOR (i1,3) bt1[i1]=bt2[i1]=b[0][i1];
              sdpath=ndpath=0;       /* mutations for each path */
              FOR (i1, ndiff) {      /* mutation steps for each path */
                 bt2[step[i1]] = b[1][step[i1]];
                 for (i2=0,ic[0]=ic[1]=0; i2<3; i2++) {
                    ic[0]+=bt1[i2]*by[i2];
                    ic[1]+=bt2[i2]*by[i2];
                 }
                 FOR (i2,2) iaa[i2]=GeneticCode[icode][ic[i2]];
                 if (iaa[1]==-1)  { nstop++;  sdpath=ndpath=0; break; }
                 if (iaa[0]==iaa[1])  sdpath++;
                 else                 ndpath++;
                 FOR (i2,3) bt1[i2]=bt2[i2];
         }
         *SynDif+=(double)sdpath;    *AsynDif+=(double)ndpath;
      }
   } 
   if (npath==nstop) {
      puts ("NG86: All paths are through stop codons..");
      if (ndiff==2) { *SynDif=0; *AsynDif=2; }
      else          { *SynDif=1; *AsynDif=2; }
   }
   else {
      *SynDif/=(double)(npath-nstop);  *AsynDif/=(double)(npath-nstop);
   }
   return (ndiff);
}

int testTransP (double P[], int n)
{
   int i,j, status=0;
   double sum, small=1e-7;

   for (i=0; i<n; i++) {
      for (j=0,sum=0; j<n; sum+=P[i*n+j++]) 
         if (P[i*n+j]<-small) status=-1;
      if (fabs(sum-1)>small && status==0) {
         printf ("\nrow sum (#%2d) = 1 = %10.6f", i+1, sum);
         status=-1;
      }
   }
   return (status);
}


int PMatUVRoot (double P[], double t, int n, double U[], double V[],
    double Root[])
{
/* P(t) = U * exp{Root*t} * V
*/
   int i,j,k;
   double expt, uexpt, *pP;

   NPMatUVRoot++;
   if (t<-0.1) printf ("\nt = %.5f in PMatUVRoot", t);
   if (t<1e-100) { identity (P, n); return(0); }
   for (k=0,zero(P,n*n); k<n; k++)
      for (i=0,pP=P,expt=exp(t*Root[k]); i<n; i++)
         for (j=0,uexpt=U[i*n+k]*expt; j<n; j++)
            *pP++ += uexpt*V[k*n+j];
   for(i=0;i<n*n;i++)  if(P[i]<0)  P[i]=0;
#if (DEBUG>=5)
      if (testTransP(P,n)) {
         /*  matout(F0,P,n,n); */
         printf("\nP(%.6f) err in PMatUVRoot.\n", t);
         error2("err in PMATUVRoot.");//exit(-1);
      }
#endif

   return (0);
}


void pijJC69 (double pij[2], double t)
{
   if (t<-0.01) printf ("\nt = %.5f in pijJC69", t);
   if (t<1e-100) 
      { pij[0]=1; pij[1]=0; }
   else
      { pij[0] = (1.+3*exp(-4*t/3.))/4;  pij[1] = (1-pij[0])/3; }
}



int PMatK80 (double P[], double t, double kappa)
{
/* PMat for JC69 and K80
*/
   int i,j;
   double e1, e2;

   if (t<-0.1) printf ("\nt = %.5f in PMatK80", t);
   if (t<1e-100) { identity (P, 4); return(0); }
   e1=exp(-4*t/(kappa+2));
   if (fabs(kappa-1)<1e-5) {
      FOR (i,4) FOR (j,4)
         if (i==j) P[i*4+j]=.25*(1+3*e1);
         else      P[i*4+j]=.25*(1-e1);
   }
   else {
      e2=exp(-2*t*(kappa+1)/(kappa+2));
      FOR (i,4) P[i*4+i]=.25*(1+e1+2*e2);
      P[0*4+1]=P[1*4+0]=P[2*4+3]=P[3*4+2]=.25*(1+e1-2*e2);
      P[0*4+2]=P[0*4+3]=P[2*4+0]=P[3*4+0]=
      P[1*4+2]=P[1*4+3]=P[2*4+1]=P[3*4+1]=.25*(1-e1);
   }
   return (0);
}


int PMatT92 (double P[], double t, double kappa, double pGC)
{
/* PMat for Tamura'92
   t is branch lnegth, number of changes per site.
*/
   double e1, e2;
   t/=(pGC*(1-pGC)*kappa + .5);

   if (t<-0.1) printf ("\nt = %.5f in PMatT92", t);
   if (t<1e-100) { identity (P, 4); return(0); }
   e1=exp(-t); e2=exp(-(kappa+1)*t/2);

   P[0*4+0]=P[2*4+2] = (1-pGC)/2*(1+e1)+pGC*e2;
   P[1*4+1]=P[3*4+3] = pGC/2*(1+e1)+(1-pGC)*e2;
   P[1*4+0]=P[3*4+2] = (1-pGC)/2*(1+e1)-(1-pGC)*e2;
   P[0*4+1]=P[2*4+3] = pGC/2*(1+e1)-pGC*e2;

   P[0*4+2]=P[2*4+0]=P[3*4+0]=P[1*4+2] = (1-pGC)/2*(1-e1);
   P[1*4+3]=P[3*4+1]=P[0*4+3]=P[2*4+1] = pGC/2*(1-e1);
   return (0);
}


int PMatTN93 (double P[], double a1t, double a2t, double bt, double pi[])
{
   double T=pi[0],C=pi[1],A=pi[2],G=pi[3], Y=T+C, R=A+G;
   double e1, e2, e3, small=-1e-4;

   if (a1t<small||a2t<small||bt<small)
      printf ("\nat=%12.6f %12.6f  bt=%12.6f", a1t,a2t,bt);

   if (a1t+a2t+bt<1e-200)  { identity(P,4);  return(0); }

   e1=exp(-bt); e2=e3=exp(-(R*a2t+Y*bt));
   if (fabs(R*a2t+Y*bt -Y*a1t-R*bt)>1e-5)  e3=exp(-(Y*a1t+R*bt));

   P[0*4+0] = T+R*T/Y*e1+C/Y*e3;
   P[0*4+1] = C+R*C/Y*e1-C/Y*e3;

   P[1*4+0] = T+R*T/Y*e1-T/Y*e3;
   P[1*4+1] = C+R*C/Y*e1+T/Y*e3;

   P[0*4+2] = P[1*4+2] = A*(1-e1);
   P[0*4+3] = P[1*4+3] = G*(1-e1);
   P[2*4+0] = P[3*4+0] = T*(1-e1);
   P[2*4+1] = P[3*4+1] = C*(1-e1);

   P[2*4+2] = A+Y*A/R*e1+G/R*e2;
   P[2*4+3] = G+Y*G/R*e1-G/R*e2;

   P[3*4+2] = A+Y*A/R*e1-A/R*e2;
   P[3*4+3] = G+Y*G/R*e1+A/R*e2;

   return(0);
}




int EvolveHKY85 (char source[], char target[], int ls, double t,
   double rates[], double pi[4], double kappa, int isHKY85)
{
/* isHKY85=1 if HKY85,  =0 if F84
   Use NULL for rates if rates are identical among sites.
*/
   int i,j,h,n=4;
   double TransP[16],a1t,a2t,bt,r, Y=pi[0]+pi[1],R=pi[2]+pi[3];

   if (isHKY85)  a1t=a2t=kappa;
   else        { a1t=1+kappa/Y; a2t=1+kappa/R; }
   bt=t/(2*(pi[0]*pi[1]*a1t+pi[2]*pi[3]*a2t)+2*Y*R);
   a1t*=bt;   a2t*=bt;
   FOR (h, ls) {
      if (h==0 || (rates && rates[h]!=rates[h-1])) {
         r=(rates?rates[h]:1);
         PMatTN93 (TransP, a1t*r, a2t*r, bt*r, pi);
         for (i=0;i<n;i++) {
            for (j=1;j<n;j++) TransP[i*n+j]+=TransP[i*n+j-1];
            if (fabs(TransP[i*n+n-1]-1)>1e-5) error2("TransP err");
         }
      }
      for (j=0,i=source[h],r=rndu();j<n-1;j++)  if (r<TransP[i*n+j]) break;
      target[h] = (char)j;
   }
   return (0);
}

int Rates4Sites (double rates[],double alpha,int ncatG,int ls, int cdf,
    double space[])
{
/* Rates for sites from the gamma (ncatG=0) or discrete-gamma (ncatG>1).
   Rates are converted into the c.d.f. if cdf=1, which is useful for
   simulation under JC69-like models. 
   space[ncatG*2]
*/
   int h, ir,j, *counts=(int*)(space+2*ncatG);
   double *rK=space, *freqK=space+ncatG;

   if (alpha==0) 
      { if(rates) FOR(h,ls) rates[h]=1; }
   else {
      if (ncatG>1) {
         DiscreteGamma (freqK, rK, alpha, alpha, ncatG, 0);
         MultiNomial (ls, ncatG, freqK, counts, space+3*ncatG);
         for (ir=0,h=0; ir<ncatG; ir++) 
            for (j=0; j<counts[ir]; j++)  rates[h++]=rK[ir];
      }
      else 
         for (h=0; h<ls; h++) rates[h]=rndgamma(alpha)/alpha;
      if (cdf) {
         for (h=1; h<ls; h++) rates[h]+=rates[h-1];
         abyx (1/rates[ls-1], rates, ls);
      }
   }
   return (0);
}


char *getcodon(char codon[], int icodon)
{
/* id : (0,63) */
   if (icodon<0||icodon>63) {
      printf("\ncodon %d\n", icodon);
      error2("getcodon.");
      return(NULL);
   }
   codon[0]=BASEs[icodon/16]; 
   codon[1]=BASEs[(icodon%16)/4];
   codon[2]=BASEs[icodon%4];
   codon[3]=0;
   return (codon);
}


char *getAAstr(char *AAstr, int iaa)
{
/* iaa (0,20) with 20 meaning termination */
   if (iaa<0 || iaa>20) error2("getAAstr: iaa err. \n");
   strncpy (AAstr, AA3Str+iaa*3, 3);
   return (AAstr);
}

int NucListall(char b, int *nb, int ib[4])
{
/* Resolve an ambiguity nucleotide b into all possibilities.  
   nb is number of bases and ib (0,1,2,3) list all of them.
   Data are complete if (nb==1).
*/
   int j,k;

   k=strchr(BASEs,b)-BASEs;
   if(k<0)
      { printf("NucListall: strange character %c\n",b); return(-1);}
   if(k<4) { *nb=1; ib[0]=k; }
   else {
      *nb=nBASEs[k];
      FOR(j,*nb) ib[j]=strchr(BASEs,EquateNUC[k][j])-BASEs;
   }
   return(0);
}

int Codon2AA(char codon[3], char aa[3], int icode, int *iaa)
{
/* translate a triplet codon[] into amino acid (aa[] and iaa), using
   genetic code icode.  This deals with ambiguity nucleotides.
   *iaa=(0,...,19),  20 for stop or missing data.
   Distinquish between stop codon and missing data? 
   naa=0: only stop codons; 1: one AA; 2: more than 1 AA.

   Returns 0: if one amino acid
           1: if multiple amino acids (ambiguity data)
           -1: if stop codon
*/
   int nb[3],ib[3][4], ic, i, i0,i1,i2, iaa0=-1,naa=0;

   for(i=0;i<3;i++)  NucListall(codon[i], &nb[i], ib[i]);
   FOR(i0,nb[0])  FOR(i1,nb[1])  FOR(i2,nb[2]) {
      ic=ib[0][i0]*16+ib[1][i1]*4+ib[2][i2];         
      *iaa=GeneticCode[icode][ic];
      if(*iaa==-1) continue;
      if(naa==0)  { iaa0=*iaa; naa++; }
      else if (*iaa!=iaa0)  naa=2;
   }
   if(naa==0)
      { printf("stop codon %c%c%c\n",codon[0],codon[1],codon[2]); *iaa=20; }
   else if(naa==2)  *iaa=20; 
   else             *iaa=iaa0;
   strncpy(aa, AA3Str+*iaa*3, 3);

   return(naa==1?0: (naa==0?-1:1));
}

int DNA2protein(char dna[], char protein[], int lc, int icode)
{
/* translate a DNA into a protein, using genetic code icode, with lc codons.
   dna[] and protein[] can be the same string.
*/
   int h, iaa, k;
   char aa3[4];

   for(h=0; h<lc; h++) {
      k=Codon2AA(dna+h*3,aa3,icode,&iaa);
      if(k==-1) printf(" stop codon at %d out of %d\n",h+1,lc);
      protein[h]=AAs[iaa];
   }
   return(0);
}


int printcu (FILE *fout, double fcodon[], int icode)
{
/* output codon usage table and other related statistics
   space[20+1+3*5]
   Outputs the genetic code table if fcodon==NULL
*/
   int wc=8, wd=0;  /* wc: for codon, wd: decimal  */
   int it, i,j,k, iaa;
   double faa[21], fb3x4[3*5]; /* chi34, Ic, lc, */
   char *word="|-", aa3[4]="   ",codon[4]="   ", ss3[4][4], *noodle;
   static double aawt[]={89.1, 174.2, 132.1, 133.1, 121.2, 146.2,
         147.1,  75.1, 155.2, 131.2, 131.2, 146.2, 149.2, 165.2, 115.1,
         105.1, 119.1, 204.2, 181.2, 117.1};

   if (fcodon) { zero(faa,21);  zero(fb3x4,12); }
   else     wc=0;
   FOR (i,4) strcpy(ss3[i],"\0\0\0");
   noodle = strc(4*(10+2+wc)-2,word[1]);
   fprintf(fout, "\n%s\n", noodle);
   for(i=0; i<4; i++,FPN(fout)) {
      FOR (j,4)  {
         FOR (k,4)  {
            it=i*16+k*4+j;   
            iaa=GeneticCode[icode][it];
            if(iaa==-1) iaa=20;
		    
            if (getcodon(codon, it)==NULL) return (-1);
	    
	    getAAstr(aa3,iaa);
            if (!strcmp(ss3[k],aa3) && j>0)   fprintf(fout, "     ");
            else  { 
               fprintf(fout, "%s %c", aa3,(iaa<20?AAs[iaa]:'*'));
               strcpy(ss3[k], aa3);
            }
            fprintf(fout, " %s", codon);
            if (fcodon) fprintf(fout, "%*.*f", wc,wd, fcodon[it] );
            if (k<3) fprintf(fout, " %c ", word[0]);
         }
         FPN (fout);
      }
      fputs (noodle, fout);
   }

   return(0);
}

int printcums (FILE *fout, int ns, double fcodons[], int icode)
{
   int neach0=6, neach=neach0, wc=3,wd=0;  /* wc: for codon, wd: decimal  */
   int iaa,it, i,j,k, i1, ngroup, igroup;
   char *word="|-", aa3[4]="   ",codon[4]="   ", ss3[4][4], *noodle;

   ngroup=(ns-1)/neach+1;
   for(igroup=0; igroup<ngroup; igroup++,FPN(fout)) {
      if (igroup==ngroup-1) neach=ns-neach0*igroup;
      noodle = strc(4*(10+wc*neach)-2, word[1]);
      strcat (noodle, "\n");
      fputs(noodle, fout);
      FOR (i,4) strcpy (ss3[i],"   ");
      FOR (i,4) {
         FOR (j,4)  {
            FOR (k,4)  {
               it = i*16+k*4+j;   
               iaa=GeneticCode[icode][it]; 
               if(iaa==-1) iaa=20;
               
	       if (getcodon(codon, it) == NULL) return (-1);
	       
	       getAAstr(aa3,iaa);
               if ( ! strcmp(ss3[k], aa3) && j>0)   fprintf(fout, "   ");
               else  { fprintf(fout, "%s", aa3); strcpy(ss3[k], aa3);  }

               fprintf(fout, " %s", codon);
               FOR (i1,neach) fprintf(fout, " %*.*f",
                       wc-1, wd, fcodons[(igroup*neach0+i1)*64+it] );
               if (k<3) fprintf(fout, " %c ", word[0]);
            }
            FPN (fout);
         }
         fputs (noodle, fout);
      }
   }
   return(0);
}

int PtoPi (double P[], double pi[], int n, double *space)
{
/* from transition probability P[ij] to pi, the stationary frequencies
   (I-P)' * pi = 0     pi * 1 = 1
   space[] is of size n*(n+1).
*/
   int i,j;
   double *T = space;      /* T[n*(n+1)]  */

   FOR (i,n)  {
      FOR (j,n)
         T[i*(n+1)+j] = (double)(i==j) - P[j*n+i];     /* transpose */
      T[i*(n+1)+n] = 0.;
   }
   fillxc (T, 1., n+1);
   matinv( T, n, n+1, pi);
   FOR (i,n) pi[i] = T[i*(n+1)+n];
   return (0);
}

int PtoX (double P1[], double P2[], double pi[], double X[])
{
/*  from P1 & P2 to X.     X = P1' diag{pi} P2
*/
   int i, j, k;

   FOR (i,4)
      FOR (j,4)
         for (k=0,X[i*4+j]=0.0; k<4; k++)  {
            X[i*4+j] += pi[k] * P1[k*4+i] * P2[k*4+j];
         }
   return (0);
}


int printaSeq (FILE *fout, char z[], int ls, int lline, int gap)
{
   int i;
   FOR (i, ls) {
      fprintf (fout, "%c", z[i]);
      if (gap && (i+1)%gap==0)  fprintf (fout, " ");
      if ((i+1)%lline==0) { fprintf (fout, "%7d", i+1); FPN (fout); }
   }
   i=ls%lline;
   if (i) fprintf (fout, "%*d\n", 7+lline+lline/gap-i-i/gap, ls);
   FPN (fout);
   return (0);
}

int printsma(FILE*fout, char*spname[], char*z[],
    int ns, int l, int lline, int gap, int seqtype, 
    int transformed, int simple, int pose[])
{
/* print multiple aligned sequences.
   use spname==NULL if no seq names available.
   pose[h] marks the position of the h_th site in z[], useful for 
   printing out the original sequences after site patterns are collapsed. 
   Sequences z[] are coded if(transformed) and not if otherwise.
*/
   int igroup, ngroup, lt, h,hp, i, b,b0=-1,igap, lspname=20, lseqlen=7;
   char indel='-', ambi='?', equal='.';
   char *pch=(seqtype<=1 ? BASEs : (seqtype==2?AAs:BINs));
   char codon[4]="   ";

   codon[0]=-1;  /* to avoid warning */
   if (gap==0) gap=lline+1;
   ngroup=(l-1)/lline+1;
   for (igroup=0,FPN(fout); igroup<ngroup; igroup++,FPN(fout))  {
      lt=min2(l,(igroup+1)*lline);  /* seqlen mark at the end of block */
      igap=lline+(lline/gap)+lspname+1-lseqlen-1; /* spaces */
      if(igroup+1==ngroup)
         igap=(l-igroup*lline)+(l-igroup*lline)/gap+lspname+1-lseqlen-1;
      /* fprintf (fout,"%*s[%*d]\n", igap, "", lseqlen,lt); */
      FOR(i,ns)  {
         if(spname) fprintf(fout,"%-*s  ", lspname,spname[i]);
         for (h=igroup*lline,lt=0,igap=0; lt<lline && h<l; h++,lt++) {
            hp=(pose?pose[h]:h);
#ifdef CODEML
            if(com.seqtype==1 && com.cleandata && transformed) {
               ic=FROM61[com.z[i][hp]];
               codon[0]=BASEs[is/16]; 
               codon[1]=BASEs[(ic%16)/4]; 
               codon[2]=BASEs[ic%4];
               fprintf(fout," %s", codon);
               continue;
            }
#endif
            b0=(int)z[0][hp];  b=(int)z[i][hp];  
            if(transformed) {
               b0=pch[b0]; b=pch[b];
            }
            if(i&&simple && b==b0 && b!=indel && b!=ambi)  b=equal;
            fputc(b, fout);
            if (++igap==gap)  { fputc(' ', fout); igap=0; }
         }
         FPN (fout);
      }
   }
   FPN(fout);
   return(0);
}


/* ***************************
        Simple tools
******************************/

static time_t time_start;

void starttime (void)
{
   time_start=time(NULL);
}

char* printtime (char timestr[])
{
/* print time elapsed since last call to starttime()
*/
   time_t t;

   t=time(NULL)-time_start;
   sprintf(timestr,"%02ld:%02ld:%02ld", t/3600,(t%3600)/60, t-(t/60)*60);
   return(timestr);
}

void sleep2(int wait)
{
/* Pauses for a specified number of seconds. */
   time_t t_cur=time(NULL);

   while(time(NULL)<t_cur+wait) ;
}



char *strc (int n, char c)
{
   static char s[256];
   int i;

   if (n>255) error2("line >255 in strc");
   FOR (i,n) s[i]=c;    s[n]=0;
   return (s);
}

int putdouble(FILE*fout, double a)
{
   double aa=fabs(a);
   return  fprintf(fout, (aa<1e-5||aa>1e6 ? "  %11.4e" : " %11.6f"), a);
}

void strcase (char *str, int direction)
{
/* direction = 0: to lower; 1: to upper */
   char *p=str;
   if(direction)  while(*p) { *p=(char)toupper(*p); p++; }
   else           while(*p) { *p=(char)tolower(*p); p++; }
}


FILE *gfopen(char *filename, char *mode)
{
   FILE *fp=(FILE*)fopen(filename, mode);
   if(fp==NULL) {
      printf("\nerror when opening file %s\n", filename);
      error2("error when opening file (gfopen)"); //exit(-1);
   }
   return(fp);
}

int appendfile(FILE*fout, char*filename)
{
   FILE *fin=gfopen(filename,"r");
   int ch;

   while((ch=fgetc(fin))!=EOF) fputc(ch,fout);
   fclose(fin);
   return(0);
}

void error2 (char * message)
{	/* exit(-1) */
 	printf("\nError: %s.\n", message);
	damage = 1; kaks_values[0] = -1; return;
}

int zero (double x[], int n)
{ int i; FOR (i,n) x[i]=0; return (0);}

double sum (double x[], int n)
{ int i; double t=0;  for(i=0; i<n; i++) t += x[i];    return(t); }

int fillxc (double x[], double c, int n)
{ int i; for(i=0; i<n; i++) x[i]=c; return (0); }

int xtoy (double x[], double y[], int n)
{ int i; for (i=0; i<n; y[i]=x[i],i++) ;  return(0); }

int abyx (double a, double x[], int n)
{ int i; for (i=0; i<n; x[i]*=a,i++) ;  return(0); }

int axtoy(double a, double x[], double y[], int n)
{ int i; for (i=0; i<n; y[i] = a*x[i],i++) ;  return(0);}

int axbytoz(double a, double x[], double b, double y[], double z[], int n)
{ int i; FOR (i,n)  z[i] = a*x[i]+b*y[i];  return (0); }

int identity (double x[], int n)
{ int i,j;  FOR (i,n)  { FOR(j,n)  x[i*n+j]=0;  x[i*n+i]=1; }  return (0); }

double distance (double x[], double y[], int n)
{  int i; double t=0;
   for (i=0; i<n; i++) t += square(x[i]-y[i]);
   return(sqrt(t));
}

double innerp (double x[], double y[], int n)
{ int i; double t=0;  FOR (i,n) t += x[i]*y[i];  return(t); }

double norm (double x[], int n)
{ int i; double t=0;  FOR (i,n) t+=x[i]*x[i];  return sqrt(t); }

int sort1 (double x[], int n, int rank[], int descending, int space[])
{
/* inefficient bubble sort */
   int i,j, it=0, *mark=space;
   double t=0;

   FOR (i,n) mark[i]=1;
   FOR (i,n) {
      for (j=0; j<n; j++)  if (mark[j]) { t=x[j]; it=j++; break; }
      if (descending) {
         for ( ; j<n; j++)
            if (mark[j] && x[j]>t) { t=x[j]; it=j; }
      }
      else {
         for ( ; j<n; j++)
            if (mark[j] && x[j]<t) { t=x[j]; it=j; }
      }
      mark[it]=0;   rank[i]=it;
   }
   return (0);
}


int f_and_x(double x[], double f[], int n, int fromf, int LastItem)
{
/* This transforms between x and f.  x and f can be identical.
   If (fromf), f->x
   else        x->f.
   The iterative variable x[] and frequency f[0,1,n-2] are related as:
      freq[k] = exp(x[k])/(1+SUM(exp(x[k]))), k=0,1,...,n-2, 
   x[] and freq[] may be the same vector.
   The last element (f[n-1] or x[n-1]=1) is updated only if(LastItem).
*/
   int i;
   double tot;

   if (fromf) {  /* f => x */
      if((tot=1-sum(f,n-1))<1e-80) error2("f[n-1]==1, not dealt with.");
      tot=1/tot;
      FOR(i,n-1)  x[i]=log(f[i]*tot);
      if(LastItem) x[n-1]=0;
   }
   else {        /* x => f */
      for(i=0,tot=1; i<n-1; i++)  tot+=(f[i]=exp(x[i]));
      FOR(i,n-1)  f[i]/=tot;
      if(LastItem) f[n-1]=1/tot;
   }
   return(0);
}

#if 0
double rndu (void)
{
/* 32-bit integer assumed */
   w_rndu *= 127773;
   return ldexp((double)w_rndu, -32);
}
#endif


static unsigned int z_rndu=137;
static unsigned int w_rndu=123456757;

void SetSeed (unsigned int seed)
{
   z_rndu=170*(seed%178)+137;
   w_rndu = seed*127773;
}


#ifdef FAST_RANDOM_NUMBER
double rndu (void)
{
/* From Ripley (1987, page 46). 32-bit integer assumed */
   w_rndu = w_rndu*69069+1;
   return ldexp((double)w_rndu, -32);
}
#else 

double rndu (void)
{
/* U(0,1): AS 183: Appl. Stat. 31:188-190 
   Wichmann BA & Hill ID.  1982.  An efficient and portable
   pseudo-random number generator.  Appl. Stat. 31:188-190

   x, y, z are any numbers in the range 1-30000.  Integer operation up
   to 30323 required.
*/
   static unsigned int x_rndu=11, y_rndu=23;
   double r;

   x_rndu = 171*(x_rndu%177) -  2*(x_rndu/177);
   y_rndu = 172*(y_rndu%176) - 35*(y_rndu/176);
   z_rndu = 170*(z_rndu%178) - 63*(z_rndu/178);
/*
   if (x_rndu<0) x_rndu+=30269;
   if (y_rndu<0) y_rndu+=30307;
   if (z_rndu<0) z_rndu+=30323;
*/
  r = x_rndu/30269.0 + y_rndu/30307.0 + z_rndu/30323.0;
  return (r-(int)r);
}

#endif


double sample_uniform(double x, double range[2], double finetune)
{
   double w[2], xnew;
   
   w[0] = x - (range[1]-range[0])*finetune/2;
   w[1] = x + (range[1]-range[0])*finetune/2;
   xnew = rnduab(w[0],w[1]);
   xnew = reflect(xnew, range[0], range[1]);
   return(xnew);
}

double reflect(double x, double a, double b)
{
/* This returns a variable in the range (a,b) by reflecting x back into the range
*/
   int rounds=0;
   double x0=x;

   if(a>=b) {
      printf("improper range %f (%f, %f)\n", x0,a,b);
      printf("");
   }
   for ( ; ; rounds) {
      if(x>=a && x<=b) return x;
      if(x<a)      x = a + a - x;
      else if(x>b) x = b - (x - b);
      if(noisy>2 && ++rounds==2) {
         printf("reflecting more than once %f (%f, %f)\n", x0,a,b);
         printf("");
      }
   }
}


void randorder(int order[], int n, int space[])
{
/* This orders 0,1,2,...,n-1 at random
   space[n]
*/
   int i,k, *item=space;

   FOR(i,n) item[i]=i;
   FOR(i,n) {
      k=(int)((n-i)*rndu());
      order[i]=item[i+k];  item[i+k]=item[i];
   }
}


double rndnorm (void)
{
/* standard normal variate, using the -Muller method (1958), improved by 
   Marsaglia and Bray (1964).  The method generates a pair of random
   variates, and only one used.
   See N. L. Johnson et al. (1994), Continuous univariate distributions, 
   vol 1. p.153.
*/
   double u1,u2, sumsquare=0;

   for (; ;) {
      u1=2*rndu()-1;
      u2=2*rndu()-1;
      sumsquare=u1*u1+u2*u2;
      if (sumsquare>=0 && sumsquare<=1) break;
   }
   return (u1*sqrt(-2*log(sumsquare)/sumsquare));
}


int rndpoisson (double m)
{
/* m is the rate parameter of the poisson
   Numerical Recipes in C, 2nd ed. pp. 293-295
*/
   static double sq, alm, g, oldm=-1;
   double em, t, y;

/* search from the origin
   if (m<5) { 
      if (m!=oldm) { oldm=m; g=exp(-m); }
      y=rndu();  sq=alm=g;
      for (em=0; ; ) {
         if (y<sq) break;
         sq+= (alm*=m/ ++em);
      }
   }
*/
   if (m<12) { 
      if (m!=oldm) { oldm=m; g=exp(-m); }
      em=-1; t=1;
      for (; ;) {
         em++; t*=rndu();
         if (t<=g) break;
      }
   }
   else {
     if (m!=oldm) {
        oldm=m;  sq=sqrt(2*m);  alm=log(m);
        g=m*alm-LnGamma(m+1);
     }
     do {
        do {
           y=tan(3.141592654*rndu());
           em=sq*y+m;
        } while (em<0);
        em=floor(em);
        t=0.9*(1+y*y)*exp(em*alm-LnGamma(em+1)-g);
     } while (rndu()>t);
   }
   return ((int) em);
}

double rndgamma1 (double s);
double rndgamma2 (double s);

double rndgamma (double s)
{
/* random standard gamma (Mean=Var=s,  with shape par=s, scale par=1)
      r^(s-1)*exp(-r)
   J. Dagpunar (1988) Principles of random variate generation,
   Clarendon Press, Oxford
   calling rndgamma1() if s<1 or
           rndgamma2() if s>1 or
           exponential if s=1
*/
   double r=0;

   if (s<=0)      puts ("jgl gamma..");
   else if (s<1)  r=rndgamma1 (s);
   else if (s>1)  r=rndgamma2 (s);
   else           r=-log(rndu());
   return (r);
}


double rndgamma1 (double s)
{
/* random standard gamma for s<1
   switching method
*/
   double r, x=0,small=1e-37,w;
   static double a,p,uf,ss=10,d;

   if (s!=ss) {
      a=1-s;
      p=a/(a+s*exp(-a));
      uf=p*pow(small/a,s);
      d=a*log(a);
      ss=s;
   }
   for (;;) {
      r=rndu();
      if (r>p)        x=a-log((1-r)/(1-p)), w=a*log(x)-d;
      else if (r>uf)  x=a*pow(r/p,1/s), w=x;
      else            return (0);
      r=rndu ();
      if (1-r<=w && r>0)
         if (r*(w+1)>=1 || -log(r)<=w)  continue;
      break;
   }
   return (x);
}

double rndgamma2 (double s)
{
/* random standard gamma for s>1
   Best's (1978) t distribution method
*/
   double r,d,f,g,x;
   static double b,h,ss=0;
   if (s!=ss) {
      b=s-1;
      h=sqrt(3*s-0.75);
      ss=s;
   }
   for (;;) {
      r=rndu ();
      g=r-r*r;
      f=(r-0.5)*h/sqrt(g);
      x=b+f;
      if (x <= 0) continue;
      r=rndu();
      d=64*r*r*g*g*g;
      if (d*x < x-2*f*f || log(d) < 2*(b*log(x/b)-f))  break;
   }
   return (x);
}


int rndNegBinomial (double shape, double mean)
{
/* mean=mean, var=mean^2/shape+m 
*/
   return (rndpoisson(rndgamma(shape)/shape*mean));
}

int SampleCat (double P[], int ncat, double space[])
{
/*  sample from ncat categories, based on probability P[]
*/
   int i;
   double *p=space, r;

   FOR (i,ncat) p[i]=P[i];
   for (i=1; i<ncat; i++) p[i]+=p[i-1];
   if (fabs(p[ncat-1]-1) > 1e-5) puts ("Sum P != 1.."), error2("Sum P != 1.."); //exit (-1);
   r=rndu();
   FOR (i, ncat) if (r<p[i]) break;
   return (i);
}

int MultiNomial (int n, int ncat, double prob[], int nobs[], double space[])
{
/* sample n times from a mutinomial distribution M(ncat, prob[])
   prob[] is considered cumulative prob if (space==NULL)
   ncrude is the number or crude categories, and lcrude marks the
   starting category for each crude category.  These are used 
   to speed up the process when ncat is large.
*/
   int i, j, crude=(ncat>20), ncrude, lcrude[200];
   double r, *pcdf=(space==NULL?prob:space), small=1e-6;

   ncrude=max2(5,ncat/20); ncrude=min2(200,ncrude);
   FOR(i,ncat) nobs[i]=0;
   if (space) {
      xtoy(prob, pcdf, ncat);
      for(i=1; i<ncat; i++) pcdf[i]+=pcdf[i-1];
   }
   if (fabs(pcdf[ncat-1]-1) > small) error2("sum P!=1 in MultiNomial");
   if (crude) {
      for(j=1,lcrude[0]=i=0; j<ncrude; j++)  {
         while (pcdf[i]<(double)j/ncrude) i++;
         lcrude[j]=i-1;
      }
   }
   FOR(i,n) {
      r=rndu();
      j=0;
      if (crude) {
         for (; j<ncrude; j++) if (r<(j+1.)/ncrude) break;
         j=lcrude[j];
      }
      for (; j<ncat-1; j++) if (r<pcdf[j]) break;
      nobs[j] ++;
   }
   return (0);
}     


/* functions concerning the CDF and percentage points of the gamma and
   Chi2 distribution
*/
double PointNormal (double prob)
{
/* returns z so that Prob{x<z}=prob where x ~ N(0,1) and (1e-12)<prob<1-(1e-12)
   returns (-9999) if in error
   Odeh RE & Evans JO (1974) The percentage points of the normal distribution.
   Applied Statistics 22: 96-97 (AS70)

   Newer methods:
     Wichura MJ (1988) Algorithm AS 241: the percentage points of the
       normal distribution.  37: 477-484.
     Beasley JD & Springer SG  (1977).  Algorithm AS 111: the percentage 
       points of the normal distribution.  26: 118-121.

*/
   double a0=-.322232431088, a1=-1, a2=-.342242088547, a3=-.0204231210245;
   double a4=-.453642210148e-4, b0=.0993484626060, b1=.588581570495;
   double b2=.531103462366, b3=.103537752850, b4=.0038560700634;
   double y, z=0, p=prob, p1;

   p1 = (p<0.5 ? p : 1-p);
   if (p1<1e-20) z=999;
   else {
      y = sqrt (log(1/(p1*p1)));   
      z = y + ((((y*a4+a3)*y+a2)*y+a1)*y+a0) / ((((y*b4+b3)*y+b2)*y+b1)*y+b0);
   }
   return (p<0.5 ? -z : z);
}

double CDFNormal (double x)
{
/* Hill ID  (1973)  The normal integral.  Applied Statistics, 22:424-427.
   Algorithm AS 66.   (error < ?)
   adapted by Z. Yang, March 1994.  Hill's routine does not look good, and I
   haven't consulted
      Adams AG  (1969)  Algorithm 39.  Areas under the normal curve.
      Computer J. 12: 197-198.
*/
    int invers=0;
    double p, limit=10, t=1.28, y=x*x/2;

    if (x<0) {  invers=1;  x=-x; }
    if (x>limit)  return (invers?0:1);
    if (x<t)  
       p = .5 - x * (    .398942280444 - .399903438504 * y
                   /(y + 5.75885480458 - 29.8213557808
                   /(y + 2.62433121679 + 48.6959930692
                   /(y + 5.92885724438))));
    else 
       p = 0.398942280385 * exp(-y) /
           (x - 3.8052e-8 + 1.00000615302 /
           (x + 3.98064794e-4 + 1.98615381364 /
           (x - 0.151679116635 + 5.29330324926 /
           (x + 4.8385912808 - 15.1508972451 /
           (x + 0.742380924027 + 30.789933034 /
           (x + 3.99019417011))))));
    return (invers ? p : 1-p);
}

double LnGamma (double x)
{
/* returns ln(gamma(x)) for x>0, accurate to 10 decimal places.  
   Stirling's formula is used for the central polynomial part of the procedure.

   Pike MC & Hill ID (1966) Algorithm 291: Logarithm of the gamma function.
   Communications of the Association for Computing Machinery, 9:684
*/
   double f=0, fneg=0, z;

   if(x<=0) {
      error2("lnGamma not implemented for x<0");
      if((int)x-x==0) { puts("lnGamma undefined"); return(-1); }
      for (fneg=1; x<0; x++) fneg/=x;
      if(fneg<0) error2("strange!! check lngamma");
      fneg=log(fneg);
   }
   if (x<7) {
      f=1;  z=x-1;
      while (++z<7)  f*=z;
      x=z;   f=-log(f);
   }
   z = 1/(x*x);
   return  fneg+ f + (x-0.5)*log(x) - x + .918938533204673 
          + (((-.000595238095238*z+.000793650793651)*z-.002777777777778)*z
               +.083333333333333)/x;  
}

double DFGamma(double x, double alpha, double beta)
{
/* mean=alpha/beta; var=alpha/beta^2
*/
   if (alpha<=0 || beta<=0) error2("err in DFGamma()");
   if (alpha>100) error2("large alpha in DFGamma()");
   return pow(beta*x,alpha)/x * exp(-beta*x - LnGamma(alpha));

}


double IncompleteGamma (double x, double alpha, double ln_gamma_alpha)
{
/* returns the incomplete gamma ratio I(x,alpha) where x is the upper 
           limit of the integration and alpha is the shape parameter.
   returns (-1) if in error
   ln_gamma_alpha = ln(Gamma(alpha)), is almost redundant.
   (1) series expansion     if (alpha>x || x<=1)
   (2) continued fraction   otherwise
   RATNEST FORTRAN by
   Bhattacharjee GP (1970) The incomplete gamma integral.  Applied Statistics,
   19: 285-287 (AS32)
*/
   int i;
   double p=alpha, g=ln_gamma_alpha;
   /* double accurate=1e-8, overflow=1e30; */
   double accurate=1e-10, overflow=1e60;
   double factor, gin=0, rn=0, a=0,b=0,an=0,dif=0, term=0, pn[6];

   if (x==0) return (0);
   if (x<0 || p<=0) return (-1);

   factor=exp(p*log(x)-x-g);   
   if (x>1 && x>=p) goto l30;
   /* (1) series expansion */
   gin=1;  term=1;  rn=p;
 l20:
   rn++;
   term*=x/rn;   gin+=term;

   if (term > accurate) goto l20;
   gin*=factor/p;
   goto l50;
 l30:
   /* (2) continued fraction */
   a=1-p;   b=a+x+1;  term=0;
   pn[0]=1;  pn[1]=x;  pn[2]=x+1;  pn[3]=x*b;
   gin=pn[2]/pn[3];
 l32:
   a++;  b+=2;  term++;   an=a*term;
   for (i=0; i<2; i++) pn[i+4]=b*pn[i+2]-an*pn[i];
   if (pn[5] == 0) goto l35;
   rn=pn[4]/pn[5];   dif=fabs(gin-rn);
   if (dif>accurate) goto l34;
   if (dif<=accurate*rn) goto l42;
 l34:
   gin=rn;
 l35:
   for (i=0; i<4; i++) pn[i]=pn[i+2];
   if (fabs(pn[4]) < overflow) goto l32;
   for (i=0; i<4; i++) pn[i]/=overflow;
   goto l32;
 l42:
   gin=1-factor*gin;

 l50:
   return (gin);
}


double PointChi2 (double prob, double v)
{
/* returns z so that Prob{x<z}=prob where x is Chi2 distributed with df=v
   returns -1 if in error.   0.000002<prob<0.999998
   RATNEST FORTRAN by
       Best DJ & Roberts DE (1975) The percentage points of the 
       Chi2 distribution.  Applied Statistics 24: 385-388.  (AS91)
   Converted into C by Ziheng Yang, Oct. 1993.
*/
   double e=.5e-6, aa=.6931471805, p=prob, g, small=1e-6;
   double xx, c, ch, a=0,q=0,p1=0,p2=0,t=0,x=0,b=0,s1,s2,s3,s4,s5,s6;

   if (p<small)   return(0);
   if (p>1-small) return(9999);
   if (v<=0)      return (-1);

   g = LnGamma (v/2);
   xx=v/2;   c=xx-1;
   if (v >= -1.24*log(p)) goto l1;

   ch=pow((p*xx*exp(g+xx*aa)), 1/xx);
   if (ch-e<0) return (ch);
   goto l4;
l1:
   if (v>.32) goto l3;
   ch=0.4;   a=log(1-p);
l2:
   q=ch;  p1=1+ch*(4.67+ch);  p2=ch*(6.73+ch*(6.66+ch));
   t=-0.5+(4.67+2*ch)/p1 - (6.73+ch*(13.32+3*ch))/p2;
   ch-=(1-exp(a+g+.5*ch+c*aa)*p2/p1)/t;
   if (fabs(q/ch-1)-.01 <= 0) goto l4;
   else                       goto l2;
  
l3: 
   x=PointNormal (p);
   p1=0.222222/v;   ch=v*pow((x*sqrt(p1)+1-p1), 3.0);
   if (ch>2.2*v+6)  ch=-2*(log(1-p)-c*log(.5*ch)+g);
l4:
   q=ch;   p1=.5*ch;
   if ((t=IncompleteGamma (p1, xx, g))<0)
      error2 ("\nIncompleteGamma");
   p2=p-t;
   t=p2*exp(xx*aa+g+p1-c*log(ch));   
   b=t/ch;  a=0.5*t-b*c;

   s1=(210+a*(140+a*(105+a*(84+a*(70+60*a))))) / 420;
   s2=(420+a*(735+a*(966+a*(1141+1278*a))))/2520;
   s3=(210+a*(462+a*(707+932*a)))/2520;
   s4=(252+a*(672+1182*a)+c*(294+a*(889+1740*a)))/5040;
   s5=(84+264*a+c*(175+606*a))/2520;
   s6=(120+c*(346+127*c))/5040;
   ch+=t*(1+0.5*t*s1-b*c*(s1-b*(s2-b*(s3-b*(s4-b*(s5-b*s6))))));
   if (fabs(q/ch-1) > e) goto l4;

   return (ch);
}

int DiscreteGamma (double freqK[], double rK[], 
    double alpha, double beta, int K, int median)
{
/* discretization of gamma distribution with equal proportions in each 
   category
*/
   int i;
   double t, factor=alpha/beta*K, lnga1;

   if (median) {
      FOR(i,K) rK[i]=PointGamma((i*2.+1)/(2.*K), alpha, beta);
      for(i=0,t=0; i<K; i++) t+=rK[i];
      FOR(i,K) rK[i]*=factor/t;
   }
   else {
      lnga1=LnGamma(alpha+1);
      for (i=0; i<K-1; i++)
         freqK[i]=PointGamma((i+1.0)/K, alpha, beta);
      for (i=0; i<K-1; i++)
         freqK[i]=IncompleteGamma(freqK[i]*beta, alpha+1, lnga1);
      rK[0] = freqK[0]*factor;
      rK[K-1] = (1-freqK[K-2])*factor;
      for (i=1; i<K-1; i++)  rK[i] = (freqK[i]-freqK[i-1])*factor;
   }
   for (i=0; i<K; i++) freqK[i]=1.0/K;

   return (0);
}


int AutodGamma (double M[], double freqK[], double rK[], double *rho1,
    double alpha, double rho, int K)
{
/* Auto-discrete-gamma distribution of rates over sites, K equal-probable
   categories, with the mean for each category used.
   This routine calculates M[], freqK[] and rK[], using alpha, rho and K.
*/
   int i,j, i1, i2;
   double *point=freqK;
   double x, y, large=20, v1;
/*
   if (fabs(rho)>1-1e-4) error2("rho out of range");
*/
   FOR (i,K-1) point[i]=PointNormal((i+1.0)/K);
   for (i=0; i<K; i++) {
      for (j=0; j<K; j++) {
         x = (i<K-1?point[i]:large);
         y = (j<K-1?point[j]:large);
         M[i*K+j] = CDFBinormal(x,y,rho);
      }
   }
   for (i1=0; i1<2*K-1; i1++) {
      for (i2=0; i2<K*K; i2++) {
         i=i2/K; j=i2%K;
         if (i+j != 2*(K-1)-i1) continue;
         y=0;
         if (i>0) y-= M[(i-1)*K+j];
         if (j>0) y-= M[i*K+(j-1)];
         if (i>0 && j>0) y += M[(i-1)*K+(j-1)];
         M[i*K+j] = (M[i*K+j]+y)*K;

         if (M[i*K+j]<0) printf("M(%d,%d) =%12.8f<0\n", i+1, j+1, M[i*K+j]);
      }
   }

   DiscreteGamma (freqK, rK, alpha, alpha, K, 0);

   for (i=0,v1=*rho1=0; i<K; i++) {
      v1+=rK[i]*rK[i]*freqK[i];
      for (j=0; j<K; j++)
         *rho1 += freqK[i]*M[i*K+j]*rK[i]*rK[j];
   }
   v1-=1;
   *rho1=(*rho1-1)/v1;
   return (0);
}


double CDFBinormal (double h1, double h2, double r)
{
/* F(h1,h2,r) = prob(x<h1, y<h2), where x and y are standard binormal, 
*/
   return (LBinormal(h1,h2,r)+CDFNormal(h1)+CDFNormal(h2)-1);
}    


double LBinormal (double h1, double h2, double r)
{
/* L(h1,h2,r) = prob(x>h1, y>h2), where x and y are standard binormal, 
   with r=corr(x,y),  error < 2e-7.
      Drezner Z., and G.O. Wesolowsky (1990) On the computation of the
      bivariate normal integral.  J. Statist. Comput. Simul. 35:101-107.
*/
   int i;
   double x[]={0.04691008, 0.23076534, 0.5, 0.76923466, 0.95308992};
   double w[]={0.018854042, 0.038088059, 0.0452707394,0.038088059,0.018854042};
   double Lh=0, r1, r2, r3, rr, aa, ab, h3, h5, h6, h7, h12;

   h12=(h1*h1+h2*h2)/2;
   if (fabs(r)>=0.7) {
      r2=1-r*r;   r3=sqrt(r2);
      if (r<0) h2*=-1;
      h3=h1*h2;   h7=exp(-h3/2);
      if (fabs(r)!=1) {
         h6=fabs(h1-h2);   h5=h6*h6/2; h6/=r3; aa=.5-h3/8;  ab=3-2*aa*h5;
         Lh = .13298076*h6*ab*(1-CDFNormal(h6))
            - exp(-h5/r2)*(ab+aa*r2)*0.053051647;
         for (i=0; i<5; i++) {
            r1=r3*x[i];  rr=r1*r1;   r2=sqrt(1-rr);
            Lh-=w[i]*exp(-h5/rr)*(exp(-h3/(1+r2))/r2/h7-1-aa*rr);
         }
      }
      if (r>0) Lh = Lh*r3*h7+(1-CDFNormal(max2(h1,h2)));
      else if (r<0) Lh = (h1<h2?CDFNormal(h2)-CDFNormal(h1):0) - Lh*r3*h7;
   }
   else {
      h3=h1*h2;
      if (r!=0) 
         for (i=0; i<5; i++) {
            r1=r*x[i]; r2=1-r1*r1;
           Lh+=w[i]*exp((r1*h3-h12)/r2)/sqrt(r2);
         }
      Lh=(1-CDFNormal(h1))*(1-CDFNormal(h2))+r*Lh;
   }
   return (Lh);
}    


double probBinomial (int n, int k, double p)
{
/* calculates  {n\choose k} * p^k * (1-p)^(n-k)
*/
   double C, up, down;

   if (n<40 || (n<1000&&k<10)) {
      for (down=min2(k,n-k),up=n,C=1; down>0; down--,up--) C*=up/down;
      if (fabs(p-.5)<1e-6) C *= pow(p,(double)n);
      else                 C *= pow(p,(double)k)*pow((1-p),(double)(n-k));
   }
   else  {
      C = exp((LnGamma(n+1.)-LnGamma(k+1.)-LnGamma(n-k+1.))/n);
      C = pow(p*C,(double)k) * pow((1-p)*C,(double)(n-k));
   }
   return C;
}

double CDFBeta(double x, double pin, double qin, double lnbeta)
{
/* Returns distribution function of the beta distribution, that is,  
   the incomplete beta ratio I_x(p,q) ).
   This is called from InverseCDFBeta() in a root-finding loop.
     This routine is a translation into C of a Fortran subroutine
     by W. Fullerton of Los Alamos Scientific Laboratory.
     Bosten and Battiste (1974).
     Remark on Algorithm 179, CACM 17, p153, (1974).
*/
   double ans, c, finsum, p, ps, p1, q, term, xb, xi, y;
   int n, i, ib;
   static double eps = 0, alneps = 0, sml = 0, alnsml = 0;

   if(x<0 || x>1 || pin<0 || qin<0) error2("out of range in CDFBeta");
   if (eps == 0) {/* initialize machine constants ONCE */
      eps = pow((double)FLT_RADIX, -(double)DBL_MANT_DIG);
      alneps = log(eps);
      sml = DBL_MIN;
      alnsml = log(sml);
   }
   y = x;  p = pin;  q = qin;

    /* swap tails if x is greater than the mean */
   if (p / (p + q) < x) {
      y = 1 - y;
      p = qin;
      q = pin;
   }

   if(lnbeta==0) lnbeta=LnGamma(p)+LnGamma(q)-LnGamma(p+q);

   if ((p + q) * y / (p + 1) < eps) {  /* tail approximation */
      ans = 0;
      xb = p * log(max2(y, sml)) - log(p) - lnbeta;
      if (xb > alnsml && y != 0)
         ans = exp(xb);
      if (y != x || p != pin)
      ans = 1 - ans;
   }
   else {
      /* evaluate the infinite sum first.  term will equal */
      /* y^p / beta(ps, p) * (1 - ps)-sub-i * y^i / fac(i) */
      ps = q - floor(q);
      if (ps == 0)
         ps = 1;

      xb=LnGamma(ps)+LnGamma(p)-LnGamma(ps+p);
      xb = p * log(y) - xb - log(p);

      ans = 0;
      if (xb >= alnsml) {
         ans = exp(xb);
         term = ans * p;
         if (ps != 1) {
            n = (int)max2(alneps/log(y), 4.0);
         for(i=1 ; i<= n ; i++) {
            xi = i;
            term = term * (xi - ps) * y / xi;
            ans = ans + term / (p + xi);
         }
      }
   }

   /* evaluate the finite sum. */
   if (q > 1) {
      xb = p * log(y) + q * log(1 - y) - lnbeta - log(q);
      ib = (int) (xb/alnsml);  if(ib<0) ib=0;
      term = exp(xb - ib * alnsml);
      c = 1 / (1 - y);
      p1 = q * c / (p + q - 1);

      finsum = 0;
      n = (int) q;
      if (q == (double)n)
         n = n - 1;
         for(i=1 ; i<=n ; i++) {
            if (p1 <= 1 && term / eps <= finsum)
               break;
            xi = i;
            term = (q - xi + 1) * c * term / (p + q - xi);
            if (term > 1) {
               ib = ib - 1;
               term = term * sml;
            }
            if (ib == 0)
               finsum = finsum + term;
         }
         ans = ans + finsum;
      }
      if (y != x || p != pin)
         ans = 1 - ans;
      if(ans>1) ans=1;
      if(ans<0) ans=0;
   }
   return ans;
}

static volatile double xtrunc;

double InverseCDFBeta(double prob, double p, double q, double lnbeta)
{
/* This calculates the inverseCDF of the beta distribution

   Cran, G. W., K. J. Martin and G. E. Thomas (1977).
   Remark AS R19 and Algorithm AS 109, Applied Statistics, 26(1), 111-114.
   Remark AS R83 (v.39, 309-310) and correction (v.40(1) p.236).

   My own implementation of the algorithm did not bracket the variable well.  
   This version is Adpated from the pbeta and qbeta routines from 
   "R : A Computer Language for Statistical Data Analysis", and it fails for 
   extreme values of p and q as well, although it seems better than my 
   previous version.
   Ziheng Yang, May 2001
*/
   double fpu=3e-308, acu_min=1e-300, lower=fpu, upper=1-2.22e-16;
   /* acu_min>= fpu: Minimal value for accuracy 'acu' which will depend on (a,p); */
   int swap_tail, i_pb, i_inn;
   double a, adj, g, h, pp, prev=0, qq, r, s, t, tx=0, w, y, yprev;
   double acu;
   volatile double xinbta;

   if(prob<0 || prob>1 || p<0 || q<0) error2("out of range in InverseCDFBeta");

   /* define accuracy and initialize */
   xinbta = prob;

   /* test for admissibility of parameters */
   if(p<0 || q<0 || prob<0 || prob>1)  error2("beta par err");
   if (prob == 0 || prob == 1)
      return prob;

   if(lnbeta==0) lnbeta=LnGamma(p)+LnGamma(q)-LnGamma(p+q);

   /* change tail if necessary;  afterwards   0 < a <= 1/2    */
   if (prob <= 0.5) {
      a = prob;   pp = p; qq = q; swap_tail = 0;
   }
   else { /* change tail, swap  p <-> q :*/
      a = 1. - prob; pp = q; qq = p; swap_tail = 1;
   }

   /* calculate the initial approximation */
   r = sqrt(-log(a * a));
   y = r - (2.30753+0.27061*r)/(1.+ (0.99229+0.04481*r) * r);

   if (pp > 1. && qq > 1.) {
      r = (y * y - 3.) / 6.;
      s = 1. / (pp*2. - 1.);
      t = 1. / (qq*2. - 1.);
      h = 2. / (s + t);
      w = y * sqrt(h + r) / h - (t - s) * (r + 5./6. - 2./(3.*h));
      xinbta = pp / (pp + qq * exp(w + w));
   }
   else {
      r = qq*2.;
      t = 1. / (9. * qq);
      t = r * pow(1. - t + y * sqrt(t), 3.);
      if (t <= 0.)
         xinbta = 1. - exp((log((1. - a) * qq) + lnbeta) / qq);
      else {
         t = (4.*pp + r - 2.) / t;
         if (t <= 1.)
            xinbta = exp((log(a * pp) + lnbeta) / pp);
         else
            xinbta = 1. - 2./(t+1.);
      }
   }

   /* solve for x by a modified newton-raphson method, using CDFBeta */
   r = 1. - pp;
   t = 1. - qq;
   yprev = 0.;
   adj = 1.;


   
/* Changes made by Ziheng to fix a bug in qbeta()
   qbeta(0.25, 0.143891, 0.05) = 3e-308   wrong (correct value is 0.457227)
*/
   if(xinbta<0) xinbta=(a+.5)/2;
   else if (xinbta < lower)  xinbta = lower;
   else if (xinbta > upper)  xinbta = upper;


   /* Desired accuracy should depend on (a,p)
    * This is from Remark .. on AS 109, adapted.
    * However, it's not clear if this is "optimal" for IEEE double prec.
    * acu = fmax2(acu_min, pow(10., -25. - 5./(pp * pp) - 1./(a * a)));
    * NEW: 'acu' accuracy NOT for squared adjustment, but simple;
    * ---- i.e.,  "new acu" = sqrt(old acu)
    */
   acu = pow(10., -13. - 2.5/(pp * pp) - 0.5/(a * a));
   acu = max2(acu, acu_min);

   for (i_pb=0; i_pb < 1000; i_pb++) {
      y = CDFBeta(xinbta, pp, qq, lnbeta);
      /* y = pbeta2(xinbta, pp, qq, lnbeta) -- to SAVE CPU; */
      y = (y - a) *
         exp(lnbeta + r * log(xinbta) + t * log(1. - xinbta));
      if (y * yprev <= 0)
         prev = max2(fabs(adj),fpu);
      g = 1;
      for (i_inn=0; i_inn < 1000; i_inn++) {
         adj = g * y;
         if (fabs(adj) < prev) {
            tx = xinbta - adj; /* trial new x */
            if (tx >= 0. && tx <= 1.) {
               if (prev <= acu || fabs(y) <= acu)   goto L_converged;
               if (tx != 0. && tx != 1.)  break;
            }
         }
         g /= 3.;
      }
      /* this prevents trouble with excess FPU precision on some machines. */
      xtrunc = tx;
      if (xtrunc == xinbta)
         goto L_converged;
      xinbta = tx;
      yprev = y;
   }
/*
   printf("\nwarning: InverseCDFBeta(%.2f, %.5f, %.5f) = %.6e\n", 
      prob,p,q, (swap_tail ? 1. - xinbta : xinbta));
*/
   L_converged:
   return (swap_tail ? 1. - xinbta : xinbta);
}


static double prob_InverseCDF, *par_InverseCDF;
static double (*cdf_InverseCDF)(double x,double par[]);
double diff_InverseCDF(double x);

double diff_InverseCDF(double x)
{
/* This is the difference between the given p and the CDF(x), the 
   objective function to be minimized.
*/
   double px=(*cdf_InverseCDF)(x,par_InverseCDF);
   return(square(prob_InverseCDF-px));
}

double InverseCDF(double(*cdf)(double x,double par[]),
       double p,double x,double par[],double xb[2])
{
/* Use x for initial value if in range
*/
   double sdiff,step=min2(0.05,(xb[1]-xb[0])/100);

   prob_InverseCDF=p;  par_InverseCDF=par; cdf_InverseCDF=cdf;
   if(x<=xb[0]||x>=xb[1]) x=.5;
   LineSearch(diff_InverseCDF, &sdiff, &x, xb, step);
   return(x);
}


int ScatterPlot (int n, int nseries, int yLorR[], double x[], double y[],
    int nrow, int ncol, int ForE)
{
/* This plots a scatter diagram.  There are nseries of data (y) 
   for the same x.  nrow and ncol specifies the #s of rows and cols 
   in the text output.
   Use ForE=1 for floating format
   yLorR[nseries] specifies which y axis (L or R) to use, if nseries>1.
*/
   char *chart,ch, *fmt[2]={"%*.*e ", "%*.*f "}, symbol[]="*~^@",overlap='&';
   int i,j,is,iy,ny=1, ncolr=ncol+3, irow=0, icol=0, w=10, wd=2;
   double large=1e32, xmin, xmax, xgap, ymin[2], ymax[2], ygap[2];

   for (i=1,xmin=xmax=x[0]; i<n; i++) 
      { if(xmin>x[i]) xmin=x[i]; if(xmax<x[i]) xmax=x[i]; }
   for (i=0; i<2; i++) { ymin[i]=large; ymax[i]=-large; }
   for (j=0; j<(nseries>1)*nseries; j++)
      if (yLorR[j]==1) ny=2;
      else if (yLorR[j]!=0) printf ("err: y axis %d", yLorR[j]);
   for (j=0; j<nseries; j++) {
      for (i=0,iy=(nseries==1?0:yLorR[j]); i<n; i++) {
         if (ymin[iy]>y[j*n+i])  ymin[iy]=y[j*n+i];
         if (ymax[iy]<y[j*n+i])  ymax[iy]=y[j*n+i];
      }
   }
   if (xmin==xmax) { puts("no variation in x?"); }
   xgap=(xmax-xmin)/ncol;   
   for (iy=0; iy<ny; iy++) ygap[iy]=(ymax[iy]-ymin[iy])/nrow;

   printf ("\n%10s", "legend: ");
   for (is=0; is<nseries; is++) printf ("%2c", symbol[is]);
   printf ("\n%10s", "y axies: ");
   if (ny==2)  for(is=0; is<nseries; is++) printf ("%2d", yLorR[is]);

   printf ("\nx   : (%10.2e, %10.2e)", xmin, xmax);
   printf ("\ny[1]: (%10.2e, %10.2e)\n", ymin[0], ymax[0]);
   if (ny==2) printf ("y[2]: (%10.2e, %10.2e)  \n", ymin[1], ymax[1]);

   chart=(char*)malloc((nrow+1)*ncolr*sizeof(char));
   for (i=0; i<nrow+1; i++) {
      for (j=1; j<ncol; j++) chart[i*ncolr+j]=' ';
      if (i%5==0) chart[i*ncolr+0]=chart[i*ncolr+j++]='+'; 
      else        chart[i*ncolr+0]=chart[i*ncolr+j++]='|'; 
      chart[i*ncolr+j]='\0'; 
      if (i==0||i==nrow) 
         FOR(j,ncol+1) chart[i*ncolr+j]=(char)(j%10==0?'+':'-');
   }

   for (is=0; is<nseries; is++) {
      for (i=0,iy=(nseries==1?0:yLorR[is]); i<n; i++) {
         for(j=0; j<ncol+1; j++) if(x[i]<=xmin+(j+0.5)*xgap) { icol=j; break; }
         for(j=0; j<nrow+1; j++) 
            if(y[is*n+i]<=ymin[iy]+(j+0.5)*ygap[iy]) { irow=nrow-j; break;}

/*
         chart[irow*ncolr+icol]=symbol[is];
*/
         if ((ch=chart[irow*ncolr+icol])==' ' || ch=='-' || ch=='+') 
            chart[irow*ncolr+icol]=symbol[is];
         else
            chart[irow*ncolr+icol]=overlap;

      }
   }
   printf ("\n");
   for (i=0; i<nrow+1; i++) {
     if (i%5==0) printf (fmt[ForE], w-1, wd, ymin[0]+(nrow-i)*ygap[0]);
     else        printf ("%*s", w, "");
     printf ("%s", chart+i*ncolr); 
     if (ny==2 && i%5==0) printf(fmt[ForE], w-1, wd, ymin[1]+(nrow-i)*ygap[1]);
     printf ("\n");
   }
   printf ("%*s", w-6, "");
   for (j=0; j<ncol+1; j++) if(j%10==0) printf(fmt[ForE], 10-1,wd,xmin+j*xgap);
   printf ("\n%*s\n", ncol/2+1+w, "x");
   free(chart);
   return(0);
}


long factorial(int n)
{
   long f, i;
   if (n>10) error2("n>10 in factorial");
   for (i=2,f=1; i<=(long)n; i++) f*=i;
   return (f);
}


double Binomial(double n, double k, double *scale)
{
/* calculates n choose k, but currently only works for int k>0
   n can be any real number.
   If(*scale!=0) the result should be c+exp(*scale).
*/
   double c,i,large=1e99;

   *scale=0;
   if(k==0) return(1);
   if(k<0 || (int)k!=k) 
      error2("k is not a whole number in Binomial.");

   if(n>0 && (int)n==n) k=min2(k,n-k);
   for (i=1,c=1; i<=k; i++) {
      c*=(n-k+i)/i;
      if(c>large)
         { *scale+=log(c); c=1; } 
   }
   return(c);
}

/****************************
          Vectors and matrices 
*****************************/

double Det3x3 (double x[3*3])
{
   return 
       x[0*3+0]*x[1*3+1]*x[2*3+2] 
     + x[0*3+1]*x[1*3+2]*x[2*3+0] 
     + x[0*3+2]*x[1*3+0]*x[2*3+1] 
     - x[0*3+0]*x[1*3+2]*x[2*3+1] 
     - x[0*3+1]*x[1*3+0]*x[2*3+2] 
     - x[0*3+2]*x[1*3+1]*x[2*3+0] ;
}

int matby (double a[], double b[], double c[], int n,int m,int k)
/* a[n*m], b[m*k], c[n*k]  ......  c = a*b
*/
{
   int i,j,i1;
   double t;
   FOR (i,n)  FOR(j,k) {
      for (i1=0,t=0; i1<m; i1++) t+=a[i*m+i1]*b[i1*k+j];
      c[i*k+j] = t;
   }
   return (0);
}


int matIout (FILE *fout, int x[], int n, int m)
{
   int i,j;
   for (i=0,FPN(fout); i<n; i++,FPN(fout)) 
      FOR(j,m) fprintf(fout,"%6d", x[i*m+j]);
   return (0);
}

int matout (FILE *fout, double x[], int n, int m)
{
   int i,j;
   for (i=0,FPN(fout); i<n; i++,FPN(fout)) 
      FOR(j,m) fprintf(fout," %11.6f", x[i*m+j]);
   return (0);
}


int matout2 (FILE * fout, double x[], int n, int m, int wid, int deci)
{
   int i,j;
   for (i=0,FPN(fout); i<n; i++,FPN(fout)) 
      FOR(j,m) fprintf(fout," %*.*f", wid-1, deci, x[i*m+j]);
   return (0);
}

int mattransp1 (double x[], int n)
/* transpose a matrix x[n*n], stored by rows.
*/
{
   int i,j;
   double t;
   FOR (i,n)  for (j=0; j<i; j++)
      if (i!=j) {  t=x[i*n+j];  x[i*n+j]=x[j*n+i];   x[j*n+i]=t; }
   return (0);
}

int mattransp2 (double x[], double y[], int n, int m)
{
/* transpose a matrix  x[n][m] --> y[m][n]
*/
   int i,j;

   FOR (i,n)  FOR (j,m)  y[j*n+i]=x[i*m+j];
   return (0);
}

int matinv (double x[], int n, int m, double space[])
{
/* x[n*m]  ... m>=n
*/
   register int i,j,k;
   int *irow=(int*) space;
   double ee=1.0e-30, t,t1,xmax;
   double det=1.0;

   FOR (i,n)  {
      xmax = 0.;
      for (j=i; j<n; j++)
         if (xmax < fabs(x[j*m+i])) { xmax = fabs(x[j*m+i]); irow[i]=j; }
      det *= xmax;
      if (xmax < ee)   {
         printf("\nDet = %.4e close to zero at %3d!\t\n", xmax,i+1);
         return(-1);
      }
      if (irow[i] != i) {
         FOR (j,m) {
            t = x[i*m+j];
            x[i*m+j] = x[irow[i]*m+j];
            x[irow[i]*m+j] = t;
         }
      }
      t = 1./x[i*m+i];
      FOR (j,n) {
         if (j == i) continue;
         t1 = t*x[j*m+i];
         FOR(k,m)  x[j*m+k] -= t1*x[i*m+k];
         x[j*m+i] = -t1;
      }
      FOR(j,m)   x[i*m+j] *= t;
      x[i*m+i] = t;
   }                            /* i  */
   for (i=n-1; i>=0; i--) {
      if (irow[i] == i) continue;
      FOR(j,n)  {
         t = x[j*m+i];
         x[j*m+i] = x[j*m + irow[i]];
         x[j*m + irow[i]] = t;
      }
   }
   return (0);
}


int getpi_sqrt (double pi[], double pi_sqrt[], int n, int *npi0)
{
   int j;
   for(j=0,*npi0=0; j<n; j++)
      if(pi[j]) pi_sqrt[(*npi0)++]=sqrt(pi[j]);
   *npi0 = n - *npi0;
   return(0);
}

int eigenQREV (double Q[], double pi[], double pi_sqrt[], int n, int npi0,
               double Root[], double U[], double V[])
{
/* 
   This finds the eigen solution of the rate matrix Q for a time-reversible 
   Markov process, using the algorithm for a real symmetric matrix.
   Rate matrix Q = S * diag{pi} = U * diag{Root} * V, 
   where S is symmetrical, all elements of pi are positive, and U*V = I.
   pi_sqrt[n-npi0] has to be calculated before calling this routine.

   [U 0] [Q_0 0] [U^-1 0]    [Root  0]
   [0 I] [0   0] [0    I]  = [0     0]

   Ziheng Yang, 25 December 2001 (ref is CME/eigenQ.pdf)
*/
   int i,j, inew,jnew, nnew=n-npi0, status;

   /* store in U the symmetrical matrix S = sqrt(D) * Q * sqrt(-D) */
   if(pi_sqrt==NULL)  error2("pi_sqrt should be calculated before");
   if(npi0==0) {
      for(i=0; i<n; i++)
         for(j=0,U[i*n+i] = Q[i*n+i]; j<i; j++)
            U[i*n+j] = U[j*n+i] = (Q[i*n+j] * pi_sqrt[i]/pi_sqrt[j]);
      status=eigenRealSym(U, n, Root, V);
      for(i=0;i<n;i++) for(j=0;j<n;j++)  V[i*n+j] = U[j*n+i] * pi_sqrt[j];
      for(i=0;i<n;i++) for(j=0;j<n;j++)  U[i*n+j] /= pi_sqrt[i];
   }
   else {
      for(i=0,inew=0; i<n; i++) {
         if(pi[i]) {
            for(j=0,jnew=0; j<i; j++) 
               if(pi[j]) {
                  U[inew*nnew+jnew] = U[jnew*nnew+inew] 
                                    = Q[i*n+j] * pi_sqrt[inew]/pi_sqrt[jnew];
                  jnew++;
               }
            U[inew*nnew+inew] = Q[i*n+i];
            inew++;
         }
      }
      status=eigenRealSym(U, nnew, Root, V);

      for(i=n-1,inew=nnew-1; i>=0; i--)   /* construct Root */
         Root[i] = (pi[i] ? Root[inew--] : 0);
      for(i=n-1,inew=nnew-1; i>=0; i--) {  /* construct V */
         if(pi[i]) {
            for(j=n-1,jnew=nnew-1; j>=0; j--)
               if(pi[j]) {
                  V[i*n+j] = U[jnew*nnew+inew]*pi_sqrt[jnew];
                  jnew--;
               }
               else 
                  V[i*n+j] = (i==j);
            inew--;
         }
         else 
            for(j=0; j<n; j++)  V[i*n+j] = (i==j);
      }
      for(i=n-1,inew=nnew-1; i>=0; i--) {  /* construct U */
         if(pi[i]) {
            for(j=n-1,jnew=nnew-1;j>=0;j--)
               if(pi[j]) {
                  U[i*n+j] = U[inew*nnew+jnew]/pi_sqrt[inew];
                  jnew--;
               }
               else 
                  U[i*n+j] = (i==j);
            inew--;
         }
         else 
            for(j=0;j<n;j++)
               U[i*n+j] = (i==j);
      }
   }

   if(fabs(Root[0])>1e-12 && noisy) printf("Root[0] = %.5e\n",Root[0]);
   Root[0]=0;
   return(status);
}


/* eigen solution for real symmetric matrix */

void HouseholderRealSym(double a[], int n, double d[], double e[]);
int EigenTridagQLImplicit(double d[], double e[], int n, double z[]);
void EigenSort(double d[], double U[], int n);

int eigenRealSym(double A[], int n, double Root[], double Offdiag[])
{
/* This finds the eigen solution of a real symmetrical matrix A[n*n].  In return, 
   A has the right vectors and Root has the eigenvalues. work[n] is the working space.
   The matrix is first reduced to a tridiagonal matrix using HouseholderRealSym(), 
   and then using the QL algorithm with implicit shifts.  

   Adapted from routine tqli in Numerical Recipes in C, with reference to LAPACK
   Ziheng Yang, 23 May 2001
*/
   int status=0;
   HouseholderRealSym(A, n, Root, Offdiag);
   status=EigenTridagQLImplicit(Root, Offdiag, n, A);
   EigenSort(Root, A, n);

   return(status);
}


void EigenSort(double d[], double U[], int n)
{
/* this sorts the eigen values d[] and rearrange the (right) eigen vectors U[]
*/
   int k,j,i;
   double p;

   for (i=0;i<n-1;i++) {
      p=d[k=i];
      for (j=i+1;j<n;j++)
         if (d[j] >= p) p=d[k=j];
      if (k != i) {
         d[k]=d[i];
         d[i]=p;
         for (j=0;j<n;j++) {
            p=U[j*n+i];
            U[j*n+i]=U[j*n+k];
            U[j*n+k]=p;
         }
      }
   }
}

void HouseholderRealSym(double a[], int n, double d[], double e[])
{
/* This uses HouseholderRealSym transformation to reduce a real symmetrical matrix 
   a[n*n] into a tridiagonal matrix represented by d and e.
   d[] is the diagonal (eigends), and e[] the off-diagonal.
*/
   int m,k,j,i;
   double scale,hh,h,g,f;

   for (i=n-1;i>=1;i--) {
      m=i-1;
      h=scale=0;
      if (m > 0) {
         for (k=0;k<=m;k++)
            scale += fabs(a[i*n+k]);
         if (scale == 0)
            e[i]=a[i*n+m];
         else {
            for (k=0;k<=m;k++) {
               a[i*n+k] /= scale;
               h += a[i*n+k]*a[i*n+k];
            }
            f=a[i*n+m];
            g=(f >= 0 ? -sqrt(h) : sqrt(h));
            e[i]=scale*g;
            h -= f*g;
            a[i*n+m]=f-g;
            f=0;
            for (j=0;j<=m;j++) {
               a[j*n+i]=a[i*n+j]/h;
               g=0;
               for (k=0;k<=j;k++)
                  g += a[j*n+k]*a[i*n+k];
               for (k=j+1;k<=m;k++)
                  g += a[k*n+j]*a[i*n+k];
               e[j]=g/h;
               f += e[j]*a[i*n+j];
            }
            hh=f/(h*2);
            for (j=0;j<=m;j++) {
               f=a[i*n+j];
               e[j]=g=e[j]-hh*f;
               for (k=0;k<=j;k++)
                  a[j*n+k] -= (f*e[k]+g*a[i*n+k]);
            }
         }
      } 
      else
         e[i]=a[i*n+m];
      d[i]=h;
   }
   d[0]=e[0]=0;

   /* Get eigenvectors */
   for (i=0;i<n;i++) {
      m=i-1;
      if (d[i]) {
         for (j=0;j<=m;j++) {
            g=0;
            for (k=0;k<=m;k++)
               g += a[i*n+k]*a[k*n+j];
            for (k=0;k<=m;k++)
               a[k*n+j] -= g*a[k*n+i];
         }
      }
      d[i]=a[i*n+i];
      a[i*n+i]=1;
      for (j=0;j<=m;j++) a[j*n+i]=a[i*n+j]=0;
   }
}

#define SIGN(a,b) ((b) >= 0.0 ? fabs(a) : -fabs(a))

int EigenTridagQLImplicit(double d[], double e[], int n, double z[])
{
/* This finds the eigen solution of a tridiagonal matrix represented by d and e.  
   d[] is the diagonal (eigenvalues), e[] is the off-diagonal
   z[n*n]: as input should have the identity matrix to get the eigen solution of the 
   tridiagonal matrix, or the output from HouseholderRealSym() to get the 
   eigen solution to the original real symmetric matrix.
   z[n*n]: has the orthogonal matrix as output

   Adapted from routine tqli in Numerical Recipes in C, with reference to
   LAPACK fortran code.
   Ziheng Yang, May 2001
*/
   int m,j,iter,niter=30, status=0, i,k;
   double s,r,p,g,f,dd,c,b, aa,bb;

   for (i=1;i<n;i++) e[i-1]=e[i];  e[n-1]=0;
   for (j=0;j<n;j++) {
      iter=0;
      do {
         for (m=j;m<n-1;m++) {
            dd=fabs(d[m])+fabs(d[m+1]);
            if (fabs(e[m])+dd == dd) break;  /* ??? */
         }
         if (m != j) {
            if (iter++ == niter) {
               status=-1;
               break;
            }
            g=(d[j+1]-d[j])/(2*e[j]);

            /* r=pythag(g,1); */

            if((aa=fabs(g))>1)  r=aa*sqrt(1+1/(g*g));
            else                r=sqrt(1+g*g);

            g=d[m]-d[j]+e[j]/(g+SIGN(r,g));
            s=c=1;
            p=0;
            for (i=m-1;i>=j;i--) {
               f=s*e[i];
               b=c*e[i];

               /*  r=pythag(f,g);  */
               aa=fabs(f); bb=fabs(g);
               if(aa>bb)       { bb/=aa;  r=aa*sqrt(1+bb*bb); }
               else if(bb==0)             r=0;
               else            { aa/=bb;  r=bb*sqrt(1+aa*aa); }

               e[i+1]=r;
               if (r == 0) {
                  d[i+1] -= p;
                  e[m]=0;
                  break;
               }
               s=f/r;
               c=g/r;
               g=d[i+1]-p;
               r=(d[i]-g)*s+2*c*b;
               d[i+1]=g+(p=s*r);
               g=c*r-b;
               for (k=0;k<n;k++) {
                  f=z[k*n+i+1];
                  z[k*n+i+1]=s*z[k*n+i]+c*f;
                  z[k*n+i]=c*z[k*n+i]-s*f;
               }
            }
            if (r == 0 && i >= j) continue;
            d[j]-=p; e[j]=g; e[m]=0;
         }
      } while (m != j);
   }
   return(status);
}

#undef SIGN





int MeanVar (double x[], int n, double *m, double *v)
{
   int i;

   for (i=0,*m=0; i<n; i++) *m=(*m*i+x[i])/(i+1.);
   for (i=0,*v=0; i<n; i++) *v+=square(x[i]- *m);
   if (n>1) *v/=(n-1.);
   return(0);
}

int variance (double x[], int n, int nx, double mx[], double vx[])
{
/* x[nx][n], mx[nx], vx[nx][nx]
*/
   int i, j, k;

   FOR(i,nx)  mx[i]=0;
   FOR(i,nx)  FOR (k,n) 
      mx[i]=(mx[i]*k+x[i*n+k])/(k+1.);
   FOR (i, nx*nx) vx[i]=0;
   for (i=0; i<nx; i++)  for (j=i; j<nx; j++) {
       FOR (k,n) vx[i*nx+j]+=(x[i*n+k]-mx[i])*(x[j*n+k]-mx[j]);
       vx[j*nx+i]=(vx[i*nx+j]/=(n-1.));
   }
   return(0);
}

int correl (double x[], double y[], int n, double *mx, double *my,
    double *v11, double *v12, double *v22, double *r)
{
   int i;

   *mx=*my=*v11=*v12=*v22=0.0;
   for (i=0; i<n; i++) {
       *v11 += square(x[i] - *mx)*i/(i+1.);
       *v22 += square(y[i] - *my) * i/(i+1.);
       *v12 += (x[i] - *mx) * (y[i] - *my)*i/(i+1.);
       *mx=(*mx * i + x[i])/(i+1.);
       *my=(*my * i + y[i])/(i+1.);
   }
   *v11/=n;   *v22/=n;   *v12/=n;

   if (*v11>0.0 && *v22>0.0)  *r=*v12/sqrt(*v11 * *v22);
   else                       *r=-9;
   return(0);
}


int bubblesort (float x[], int n)
{
/* inefficient bubble sort */
   int i,j;
   float t=0;

   for(i=0;i<n;i++) {
      for(j=i;j<n;j++)
         if(x[j]<x[i]) { t=x[i]; x[i]=x[j]; x[j]=t; }
   }
   return (0);
}


typedef float resulttype;

int comparefloat (const void *a, const void *b)
{  
   resulttype aa = *(resulttype*)a, bb= *(resulttype*)b;
   return (aa==bb ? 0 : aa > bb ? 1 : -1);
}


int DescriptiveStatistics (FILE *fout, char infile[], int nbin)
{
/* this reads fin nx+2 times.
*/
   FILE *fin=fopen(infile,"r");
   int  n, nx, i,j,k, jj;
   char *fmt=" %9.6f", timestr[32];
   double *x, *mean, *median, *minx, *maxx, *x025, *x975, *var, t;
   double *mid, *freq, *gap;  /* size nbin, for binning */
   resulttype *y;

   starttime();
   if (fin==NULL) { /* puts("input file open err"); exit(-1); */ error2("input file open err"); }
   fscanf(fin,"%d%d", &n,&nx);
   printf("\n%d observations %d variables\n", n,nx);
   x = (double*)malloc((nx*7+nx*nx)*sizeof(double));
   mid = (double*)malloc((2*nx*nbin+nx)*sizeof(double));
   if (x==NULL || mid==NULL) { /* puts("did not get enough space."); exit(-1); */ error2("did not get enough space."); }
   for(j=0;j<nx*7+nx*nx;j++) x[j]=0; 
   mean=x+nx; median=mean+nx; minx=median+nx; maxx=minx+nx; 
   x025=maxx+nx; x975=x025+nx; var=x975+nx;
   freq=mid+nx*nbin; gap=freq+nx*nbin;
   printf("collecting min, max, and mean");
   for(i=0; i<n; i++) {
      for(j=0;j<nx;j++) fscanf(fin,"%lf", &x[j]);
      if(i==0) 
         for(j=0;j<nx;j++) minx[j]=maxx[j]=x[j];
      else {
         for(j=0;j<nx;j++) 
            if      (minx[j]>x[j]) minx[j]=x[j];
            else if (maxx[j]<x[j]) maxx[j]=x[j];
      }
      for(j=0;j<nx;j++) mean[j]+=x[j]/n;
   }
   printf(" %10s\nhistogram & variance",printtime(timestr));
   for(j=0;j<nx;j++) {
      gap[j]=(maxx[j]-minx[j])/nbin;
      for (k=0; k<nbin; k++) 
         { freq[j*nbin+k]=0; mid[j*nbin+k]=minx[j]+gap[j]*(k+0.5); }
   }
   rewind(fin);  fscanf(fin,"%d%d", &n,&nx);
   for (i=0; i<n; i++) {
      for(j=0;j<nx;j++) fscanf(fin,"%lf", &x[j]);
      for(j=0;j<nx;j++) {
         for (k=0; k<nbin; k++) if(x[j]<=minx[j]+gap[j]*(k+1)) break;
         freq[j*nbin+k]++;
      }
      for(j=0;j<nx;j++) for(k=0;k<=j;k++)
          var[j*nx+k] += (x[j]-mean[j])*(x[k]-mean[k])/n;
   }
   printf("%10s\nsorting to get median and percentiles\n",printtime(timestr));
   y=(float*)malloc(n*sizeof(float));
   if(y==NULL) 
	{  /* printf("not enough mem for %d variables\n",n); exit(-1); */
		error2("not enough mem for variables");
	}
   for(jj=0;jj<nx;jj++) {
      rewind(fin);  fscanf(fin,"%d%d", &n,&nx);
      for(i=0;i<n;i++) {
         for(j=0;j<nx;j++) fscanf(fin,"%lf", &x[j]);
         y[i]=(float)x[jj];
      }

      /* bubblesort(y, n); */
      qsort(y, (size_t)n, sizeof(float), comparefloat);

      median[jj]=y[(n+1)/2];
      x025[jj]=y[(int)(n*.025+.5)];
      x975[jj]=y[(int)(n*.975+.5)];
      printf("  variable %d out of %d %10s\n",jj+1,nx,printtime(timestr));
   }

   fprintf(fout,"\nmean    ");  for(j=0;j<nx;j++) fprintf(fout, fmt, mean[j]);
   fprintf(fout,"\nmedian  ");  for(j=0;j<nx;j++) fprintf(fout, fmt, median[j]);
   fprintf(fout,"\nS.D.    ");  for(j=0;j<nx;j++) fprintf(fout, fmt, sqrt(var[j*nx+j]));
   fprintf(fout,"\nmin     ");  for(j=0;j<nx;j++) fprintf(fout, fmt, minx[j]);
   fprintf(fout,"\nmax     ");  for(j=0;j<nx;j++) fprintf(fout, fmt, maxx[j]);
   fprintf(fout,"\n2.5%%    "); for(j=0;j<nx;j++) fprintf(fout, fmt, x025[j]);
   fprintf(fout,"\n97.5%%   "); for(j=0;j<nx;j++) fprintf(fout, fmt, x975[j]);
   fprintf (fout, "\n\ncorrelation coefficient\n");
   for (j=0; j<nx; j++,fputc('\n',fout))
      for (k=0; k<=j; k++) {
         t=sqrt(var[j*nx+j]*var[k*nx+k]);
         fprintf(fout, fmt, (t>0?var[j*nx+k]/t:-9));
      }
   fprintf(fout, "\nmidvalue and freq for bins\n");
   for (k=0; k<nbin; k++,fputc('\n',fout))
      for(j=0;j<nx;j++)
         fprintf(fout, "%s%.5f\t%.5f", (j?"\t\t":""),mid[j*nbin+k], freq[j*nbin+k]/n);

   free(x); free(mid);  free(y);
   return(0);
}


/******************************************
          Minimization
*******************************************/

int H_end (double x0[], double x1[], double f0, double f1,
    double e1, double e2, int n)
/*   Himmelblau termination rule.   return 1 for stop, 0 otherwise.
*/
{
   double r;
   if((r=norm(x0,n))<e2)  r=1;
   r*=e1;
   if(distance(x1,x0,n)>=r)  return(0);
   r=fabs(f0);  if(r<e2) r=1;     
   r*=e1;
   if (fabs(f1-f0)>=r) return (0);
   return (1);
}

int AlwaysCenter=0;
double Small_Diff=5e-6;  /* reasonable values 1e-5, 1e-7 */

int gradient (int n, double x[], double f0, double g[], 
    double (*fun)(double x[],int n), double space[], int Central)
{
/*  f0=fun(x) is always given
*/
   int i,j;
   double *x0=space, *x1=space+n, eh0=Small_Diff, eh;  /* 1e-7 */

   if (Central) {
      FOR(i,n)  {
         FOR(j, n)  x0[j]=x1[j]=x[j];
         eh=pow(eh0*(fabs(x[i])+1), 0.67);
         x0[i]-=eh; x1[i]+=eh;
         g[i] = ((*fun)(x1,n) - (*fun)(x0,n))/(eh*2.0);
      }
   }
   else {
      FOR(i,n)  {
         FOR(j, n)  x1[j]=x[j];
         eh=eh0*(fabs(x[i])+1);
         x1[i]+=eh;
         g[i] = ((*fun)(x1,n)-f0)/eh;
      }
   }
   return(0);
}

int Hessian (int n, double x[], double f0, double g[], double H[],
    double (*fun)(double x[], int n), double space[])
{
/* Hessian matrix H[n][n] by the central difference method
   # of function calls: (1+2*n*n)
*/
   int i,j,k;
   double *x1=space, eh0=Small_Diff*2, *eh=x1+n, f11,f22,f12,f21;  
/* eh0=1e-5 or 1e-6                              1:+  2:-  */

   FOR (k,n) eh[k] = eh0*(1+fabs(x[k]));
   FOR (i,n)  {
      for (j=i; j<n; j++)  {
         FOR (k,n) x1[k]=x[k];
         x1[i]+=eh[i]/2.0;  x1[j]+=eh[j]/2.0;  f11=(*fun)(x1,n);
         x1[i]-=eh[i];      x1[j]-=eh[j];      f22=(*fun)(x1,n);
         if (i==j)  {
             H[i*n+i]=(f11+f22-2*f0)/(eh[i]*eh[i]);
             g[i]=(f11-f22)/(eh[i]*2);
             continue;
         }
         x1[i]+=eh[i];                         f12=(*fun)(x1,n);
         x1[i]-=eh[i];      x1[j]+=eh[j];      f21=(*fun)(x1,n);
         H[i*n+j]=H[j*n+i] = (f11+f22-f12-f21)/(eh[i]*eh[j]);
      }
   }
   return(0);
}


int jacobi_gradient (double x[], double J[],
    int (*fun) (double x[], double y[], int nx, int ny),
    double space[], int nx, int ny);

int jacobi_gradient (double x[], double J[],
    int (*fun) (double x[], double y[], int nx, int ny),
    double space[], int nx, int ny)
{
/* Jacobi by central difference method
   J[ny][nx]  space[2*nx+2*ny]
*/
   int i,j;
   double *x0=space, *x1=space+nx, *y0=x1+nx, *y1=y0+ny, eh0=1.0e-4, eh;

   FOR (i,nx)  {
      FOR (j, nx)  x0[j]=x1[j]=x[j];
      eh=(x[i]==0.0) ? eh0 : fabs(x[i])*eh0;
      x0[i] -= eh; x1[i] += eh;
      (*fun) (x0, y0, nx, ny);
      (*fun) (x1, y1, nx, ny);
      FOR (j,ny) J[j*nx+i] = (y1[j]-y0[j])/(eh*2.0);
   }
   return(0);
}

int nls2 (FILE *fout, double *sx, double * x0, int nx,
      int (*fun)(double x[], double y[], int nx, int ny),
      int (*jacobi)(double x[], double J[], int nx, int ny),
      int (*testx) (double x[], int nx),
      int ny, double e)
{
/* non-linear least squares: minimization of s=f(x)^2.
   by the damped NLS, or Levenberg-Marguard-Morrison(LMM) method.
   x[n] C[n,n+1] J[ny,n] y[ny] iworker[n]
*/
   int n=nx, ii, i, i1, j, istate=0, increase=0, maxround=500,sspace;
   double s0=0.0, s=0.0, t;
   double v=0.0, vmax=1.0/e, bigger=2.5, smaller=0.75;
       /* v : Marguardt factor, suggested factors in SSL II (1.5,0.5)  */
   double *x, *g, *p, *C, *J, *y, *space, *space_J;

   sspace=(n*(n+4+ny)+ny+2*(n+ny))*sizeof(double);
   if((space=(double*)malloc(sspace))==NULL) error2("oom in nls2");
   zero (space, n*(n+4+ny)+ny);
   x=space;  g=x+n;  p=g+n;  C=p+n;  J=C+n*(n+1);  y=J+ny*n; space_J=y+ny;

   (*fun) (x0, y, n, ny);
   for (i=0, s0=0; i<ny; i++)   s0 += y[i]*y[i];

   FOR (ii, maxround)  {
      increase=0;
      if (jacobi)  (*jacobi) (x0, J, n, ny);
      else         jacobi_gradient (x0, J, fun, space_J, n, ny);
      if (ii == 0) {
         for (j=0,t=0; j<ny*n; j++)  t += J[j] * J[j];
         v = sqrt (t) / (double) (ny*n);     /*  v = 0.0;  */
      }
      FOR (i,n)  {
         for (j=0,t=0; j<ny; j++)  t += J[j*n+i] * y[j];
         g[i] = 2*t;
         C[i*(n+1)+n] = -t;
         for (j=0; j<=i; j++) {
            for (i1=0,t=0; i1<ny; i1++)  t += J[i1*n+i] * J[i1*n+j];
            C[i*(n+1)+j] = C[j*(n+1)+i] = t;
         }
         C[i*(n+1)+i] += v*v;
      }
      if (matinv( C,n,n+1, y+ny) == -1)  {
         v *= bigger;
         continue;
      }
      FOR (i,n)   p[i] = C[i*(n+1)+n];

      t = bound (n, x0, p, x, testx);
      if (t>1) t=1;
      FOR (i,n) x[i] = x0[i] + t * p[i];

      (*fun) (x, y, n, ny);
      for (i=0,s=0; i<ny; i++)  s += y[i]*y[i];

      if (fout) {
         fprintf (fout,"\n%4d  %10.6f",ii+1,s);
         /* FOR(i,n) fprintf(fout,"%8.4f",x[i]); */
      }
      if (s0<s) increase = 1;
      if (H_end(x0,x,s0,s,e,e,n)) break;
      if (increase)  {  v*=bigger;  if (v>vmax)  { istate=1; break; } }
      else    {         v*=smaller; xtoy (x, x0, n); s0=s; }
   }                    /* ii, maxround */
   if (increase)   *sx=s0;
   else       {    *sx=s;    xtoy(x, x0, n);   }
   if (ii == maxround) istate=-1;
   free (space);
   return (istate);
}



double bound (int nx, double x0[], double p[], double x[],
       int(*testx)(double x[], int nx))
{
/* find largest t so that x[]=x0[]+t*p[] is still acceptable.
   for bounded minimization, p is possibly changed in this function
   using testx()
*/
   int i, nd=0;
   double factor=20, by=1, small=1e-8;  /* small=(SIZEp>1?1e-7:1e-8) */ 

   xtoy (x0, x, nx);
   FOR (i,nx)  {
      x[i]=x0[i]+small*p[i];
      if ((*testx) (x, nx))  {  p[i]=0.0;  nd++; }
      x[i]=x0[i];
   }
   if (nd==nx) { if (noisy) puts ("bound:no move.."); return (0); }

   for (by=0.75; ; ) {
      FOR (i,nx)  x[i]=x0[i]+factor*p[i];
      if ((*testx)(x,nx)==0)  break;
      factor *= by;
   }
   return(factor);
}






double LineSearch(double(*fun)(double x),double *f,double *x0,double xb[2],double step)
{
/* linear search using quadratic interpolation 

   From Wolfe M. A.  1978.  Numerical methods for unconstrained
   optimization: An introduction.  Van Nostrand Reinhold Company, New York.
   pp. 62-73.
   step is used to find the bracket (a1,a2,a3)
*/
   int ii=0, maxround=100, i;
   double e=1e-15, small=1e-20,factor=1.2, step1, percentUse=0;
   double a0,a1,a2,a3,a4=-1,a5,a6, f0,f1,f2,f3,f4=-1,f5,f6;
/*
int debug=0;
*/
/* find a bracket (a1,a2,a3) with function values (f1,f2,f3)
   so that a1<a2<a3 and f2<f1 and f2<f3
*/

   if(step<=0) return(*x0);
   a0=a1=a2=a3=f0=f1=f2=f3=-1;
   if(*x0<xb[0]||*x0>xb[1]) error2("err LineSearch: x0 out of range");
   f2=f0=fun(a2=a0=*x0);
   step1=min2(step,(a0-xb[0])/4);
   step1=max2(step1,e);
   for(i=0,a1=a0,f1=f0; ; i++) {
      a1-=(step1*=factor); 
      if(a1>xb[0]) {
         f1=fun(a1);
         if(f1>f2)  break;
         else {
            a3=a2; f3=f2; a2=a1; f2=f1;
         }
      }
      else {
         a1=xb[0];  f1=fun(a1);
         if(f1<=f2) { a2=a1; f2=f1; }
         break;
      }
   }

   if(i==0) { /* *x0 is the best point during the previous search */
      step1=min2(step,(xb[1]-a0)/4);
      for(i=0,a3=a2,f3=f2; ; i++) {
         a3+=(step1*=factor); 
         if(a3<xb[1]) {
            f3=fun(a3);
            if(f3>f2)  break;
            else 
               { a1=a2; f1=f2; a2=a3; f2=f3; }
         }
         else {
            a3=xb[1];  f3=fun(a3);
            if(f3<f2) { a2=a3; f2=f3; }
            break;
         }
      }
   }

   /* iteration by quadratic interpolation, fig 2.2.9-10 (pp 71-71) */
   for (ii=0; ii<maxround; ii++) {
      /* a4 is the minimum from the parabola over (a1,a2,a3)  */

      if (a1>a2+1e-99 || a3<a2-1e-99 || f2>f1+1e-99 || f2>f3+1e-99) /* for linux */
         { printf("\npoints out of order (ii=%d)!",ii+1); break; }

/*
      if (a1>a2 || a3<a2 || f2>f1 || f2>f3)
         { printf("\npoints out of order (ii=%d)!",ii+1); break; }
*/
      a4 = 2*((a2-a3)*f1+(a3-a1)*f2+(a1-a2)*f3);
      if (fabs(a4)>small)
         a4=((a2*a2-a3*a3)*f1+(a3*a3-a1*a1)*f2+(a1*a1-a2*a2)*f3)/a4;
      if (a4>a3 || a4<a1)  a4=(a1+2*a2+a3)/4;  /* not useful */
      else                 percentUse++;
      f4=fun(a4);

      if (fabs(f2-f4)*(1+fabs(f2))<=e && fabs(a2-a4)*(1+fabs(a2))<=e)  break;

      if (a1<=a4 && a4<=a2) {    /* fig 2.2.10 */
         if (fabs(a2-a4)>.2*fabs(a1-a2)) {
            if (f1>=f4 && f4<=f2) { a3=a2; a2=a4;  f3=f2; f2=f4; }
            else { a1=a4; f1=f4; }
         }
         else {
            if (f4>f2) {
               a5=(a2+a3)/2; f5=fun(a5);
               if (f5>f2) { a1=a4; a3=a5;  f1=f4; f3=f5; }
               else       { a1=a2; a2=a5;  f1=f2; f2=f5; }
            }
            else {
               a5=(a1+a4)/2; f5=fun(a5);
               if (f5>=f4 && f4<=f2)
                  { a3=a2; a2=a4; a1=a5;  f3=f2; f2=f4; f1=f5; }
               else {
                  a6=(a1+a5)/2; f6=fun(a6);
                  if (f6>f5)
                       { a1=a6; a2=a5; a3=a4;  f1=f6; f2=f5; f3=f4; }
                  else { a2=a6; a3=a5;  f2=f6; f3=f5; }
               }
            }
         }
      }
      else {                     /* fig 2.2.9 */
         if (fabs(a2-a4)>.2*fabs(a2-a3)) {
            if (f2>=f4 && f4<=f3) { a1=a2; a2=a4;  f1=f2; f2=f4; }
            else                  { a3=a4; f3=f4; }
         }
         else {
            if (f4>f2) {
               a5=(a1+a2)/2; f5=fun(a5);
               if (f5>f2) { a1=a5; a3=a4;  f1=f5; f3=f4; }
               else       { a3=a2; a2=a5;  f3=f2; f2=f5; }
            }
            else {
               a5=(a3+a4)/2; f5=fun(a5);
               if (f2>=f4 && f4<=f5)
                  { a1=a2; a2=a4; a3=a5;  f1=f2; f2=f4; f3=f5; }
               else {
                  a6=(a3+a5)/2; f6=fun(a6);
                  if (f6>f5)
                      { a1=a4; a2=a5; a3=a6;  f1=f4; f2=f5; f3=f6; }
                  else { a1=a5; a2=a6;  f1=f5; f2=f6; }
               }
            }
         }
      }
   }   /*  for (ii) */
   if (f2<=f4)  { *f=f2; a4=a2; }
   else           *f=f4;

if(noisy>9 && (a6=percentUse/ii)<.5)
 printf("\nLineSearch: only %6.2f%% useful?\n",a6*100);

   return (*x0=(a4+a2)/2);
}



double fun_ls (double t, double (*fun)(double x[],int n), 
       double x0[], double p[], double x[], int n);

double fun_ls (double t, double (*fun)(double x[],int n), 
       double x0[], double p[], double x[], int n)
{  int i;   FOR (i,n) x[i]=x0[i] + t*p[i];   return ( (*fun)(x, n) ); }


double LineSearch2 (double(*fun)(double x[],int n), double *f, double x0[], 
       double p[], double step, double limit, double e, double space[], int n)
{
/* linear search using quadratic interpolation 
   from x0[] in the direction of p[],
                x = x0 + a*p        a ~(0,limit)
   returns (a).    *f: f(x0) for input and f(x) for output

   x0[n] x[n] p[n] space[n]

   adapted from Wolfe M. A.  1978.  Numerical methods for unconstrained
   optimization: An introduction.  Van Nostrand Reinhold Company, New York.
   pp. 62-73.
   step is used to find the bracket and is increased or reduced as necessary, and is 
   not terribly important.
*/
   int ii=0, maxround=10;
   double *x=space, factor=2, small=1e-10, e1=e*1e-3, e2=1e-5;
   double a0, a1, a2, a3, a4, a5, a6, f0, f1, f2, f3, f4, f5, f6;

/* look for bracket (a1, a2, a3) with function values (f1, f2, f3)
   step length step given, and only in the direction a>=0
*/

   if (noisy>2)
      printf ("\n%4d h-lim-p %8.4f %8.4f %8.4f ",Iround+1,step,limit,norm(p,n));

   if (step<=0 || limit<small || step>=limit) {
      if (noisy>2) 
         printf ("\nh-lim-p:%20.8e%20.8e%20.8e %12.6f\n",step,limit,norm(p,n),*f);
      return (0);
   }
   a0=a1=0; f1=f0=*f;
   a2=a0+step; f2=fun_ls(a2, fun,x0,p,x,n);
   if (f2>f1) {
      for (; ;) {
         step/=factor;
         if (step<small) return (0);
         a3=a2;    f3=f2;
         a2=a0+step;  f2=fun_ls(a2, fun,x0,p,x,n);
         if (f2<=f1) break;
      }
   }
   else {
      for (; ;) {
         step*=factor;
         if (step>limit) step=limit;
         a3=a0+step;  f3=fun_ls(a3, fun,x0,p,x,n);
         if (f3>=f2) break;
         a1=a2; f1=f2;    a2=a3; f2=f3;
         if (step>=limit) {
            if (noisy>2) printf("%14.6f%3c%7.4f%6d", *f=f3, 'm', a3, NFunCall);
            *f=f3; return(a3);
         }
      }
   }

   a4=(a2+a3)/2; f4=fun_ls(a4, fun,x0,p,x,n);
   if (f4<f2) { a1=a2; f1=f2;   a2=a4; f2=f4; }
   else { a3=a4; f3=f4; }

   /* iteration by quadratic interpolation, fig 2.2.9-10 (pp 71-71) */

   for (ii=0; ii<maxround; ii++) {
      /* a4 is the minimum from the parabola over (a1,a2,a3)  */

      if (a1>a2 || a3<a2 || f2>f1 || f2>f3) { puts ("\n? in ls2!"); break; }
      a4 = 2*((a2-a3)*f1+(a3-a1)*f2+(a1-a2)*f3);
      if (a4>small*.01)
         a4 = ((a2*a2-a3*a3)*f1+(a3*a3-a1*a1)*f2+(a1*a1-a2*a2)*f3)/a4;
      if (a4>a3 || a4<a1)  a4=(a1+2*a2+a3)/4;
      f4 = fun_ls(a4, fun,x0,p,x,n);

      if ((fabs(f2)>=e2 && fabs(f2-f4)<=e1*fabs(f2))
          || (fabs(f2)<e2 && fabs(f2-f4)<=e1))    break;

      if (a1<=a4 && a4<=a2) {    /* fig 2.2.10 */
         if (fabs(a2-a4)>.2*fabs(a1-a2)) {
            if (f1>=f4 && f4<=f2) { a3=a2; a2=a4;  f3=f2; f2=f4; }
            else { a1=a4; f1=f4; }
         }
         else {
            if (f4>f2) {
               a5=(a2+a3)/2; f5=fun_ls(a5, fun,x0,p,x,n);
               if (f5>f2) { a1=a4; a3=a5;  f1=f4; f3=f5; }
               else       { a1=a2; a2=a5;  f1=f2; f2=f5; }
            }
            else {
               a5=(a1+a4)/2; f5=fun_ls(a5, fun,x0,p,x,n);
               if (f5>=f4 && f4<=f2)
                  { a3=a2; a2=a4; a1=a5;  f3=f2; f2=f4; f1=f5; }
               else {
                  a6=(a1+a5)/2; f6=fun_ls(a6, fun,x0,p,x,n);
                  if (f6>f5)
                       { a1=a6; a2=a5; a3=a4;  f1=f6; f2=f5; f3=f4; }
                  else { a2=a6; a3=a5;  f2=f6; f3=f5; }
               }
            }
         }
      }
      else {                     /* fig 2.2.9 */
         if (fabs(a2-a4)>.2*fabs(a2-a3)) {
            if (f2>=f4 && f4<=f3) { a1=a2; a2=a4;  f1=f2; f2=f4; }
            else                  { a3=a4; f3=f4; }
         }
         else {
            if (f4>f2) {
               a5=(a1+a2)/2; f5=fun_ls(a5, fun,x0,p,x,n);
               if (f5>f2) { a1=a5; a3=a4;  f1=f5; f3=f4; }
               else       { a3=a2; a2=a5;  f3=f2; f2=f5; }
            }
            else {
               a5=(a3+a4)/2; f5=fun_ls(a5, fun,x0,p,x,n);
               if (f2>=f4 && f4<=f5)
                  { a1=a2; a2=a4; a3=a5;  f1=f2; f2=f4; f3=f5; }
               else {
                  a6=(a3+a5)/2; f6=fun_ls(a6, fun,x0,p,x,n);
                  if (f6>f5)
                      { a1=a4; a2=a5; a3=a6;  f1=f4; f2=f5; f3=f6; }
                  else { a1=a5; a2=a6;  f1=f5; f2=f6; }
               }
            }
         }
      }
   }

   if (f2>f0 && f4>f0)  a4=0;
   if (f2<=f4)  { *f=f2; a4=a2; }
   else         *f=f4;
   if (noisy>2) printf ("%14.6f%3d%7.4f%6d", *f,ii, a4, NFunCall);

   return (a4);
}



/*
#define Safeguard_Newton
*/

int Newton (FILE *fout, double *f, double (* fun)(double x[], int n),
    int (* ddfun) (double x[], double *fx, double dx[], double ddx[], int n),
    int (*testx) (double x[], int n),
    double x0[], double space[], double e, int n)
{
   int i,j, maxround=500;
   double f0=1e40, /*small=1e-10,*/ h, SIZEp, t, *H, *x, *g, *p, *tv;

   H=space,  x=H+n*n;   g=x+n;   p=g+n, tv=p+n;

   printf ("\n\nIterating by Newton\tnp:%6d\nInitial:", n);
   FOR (i,n) printf ("%8.4f", x0[i]);       FPN (F0);
   if (fout) fprintf (fout, "\n\nNewton\tnp:%6d\n", n);
   if (testx (x0, n)) error2("Newton..invalid initials.");
   FOR (Iround, maxround) {
       if (ddfun)
           (*ddfun) (x0, f, g, H, n);
       else  {
           *f = (*fun)(x0, n);
           Hessian (n, x0, *f, g, H, fun, tv);
       }
       matinv (H, n, n, tv);
       FOR (i,n) for (j=0,p[i]=0; j<n; j++)  p[i]-=H[i*n+j]*g[j];

       h=bound (n, x0, p, tv, testx);
       t=min2(h,1);
       SIZEp=norm(p,n);

#ifdef Safeguard_Newton
       if (SIZEp>4) {
           while (t>small) {
               FOR (i,n)  x[i]=x0[i]+t*p[i];
               if ((*f=fun(x,n)) < f0) break;
               else t/=2;
           }
       }
       if (t<small) t=min2(h, .5);
#endif

       FOR (i,n)  x[i]=x0[i]+t*p[i];
       if (noisy>2) {
            printf ("\n%3d h:%7.4f %12.6f  x", Iround+1, SIZEp, *f);
            FOR (i,n) printf ("%7.4f  ", x0[i]);
       }
       if (fout) {
            fprintf (fout, "\n%3d h:%7.4f%12.6f  x", Iround+1, SIZEp, *f);
            FOR (i,n) fprintf (fout, "%7.4f  ", x0[i]);
            fflush(fout);
       }
       if ((h=norm(x0,n))<e)  h=1;
       if (SIZEp<0.01 && distance(x,x0,n)<h*e) break;

       f0=*f;
       xtoy (x,x0,n);
    }
    xtoy (x, x0, n);    *f=fun(x0, n);

    if (Iround==maxround) return(-1);
    return(0);
}


int gradientB (int n, double x[], double f0, double g[], 
    double (*fun)(double x[],int n), double space[], int xmark[]);

extern int noisy, Iround;
extern double SIZEp;

int gradientB (int n, double x[], double f0, double g[], 
    double (*fun)(double x[],int n), double space[], int xmark[])
{
/* f0=fun(x) is always provided.
   xmark=0: central; 1: upper; -1: down
*/
   int i,j;
   double *x0=space, *x1=space+n, eh0=Small_Diff, eh;  /* eh0=1e-6 || 1e-7 */

   FOR(i,n) {
      eh=eh0*(fabs(x[i])+1);
      if (xmark[i]==0 && (AlwaysCenter || SIZEp<1)) {   /* central */
         FOR (j, n)  x0[j]=x1[j]=x[j];
         eh=pow(eh,.67);  x0[i]-=eh; x1[i]+=eh;
         g[i]=((*fun)(x1,n)-(*fun)(x0,n))/(eh*2.0);
      }
      else  {                         /* forward or backward */
         FOR (j, n)  x1[j]=x[j];
         if (xmark[i]) eh*=-xmark[i];
         x1[i] += eh;
         g[i]=((*fun)(x1,n)-f0)/eh;
      }
   }
   return(0);
}


#define BFGS
/*
#define SR1
#define DFP
*/

int ming2 (FILE *fout, double *f, double (*fun)(double x[], int n),
    int (*dfun)(double x[], double *f, double dx[], int n),
    double x[], double xb[][2], double space[], double e, int n)
{
/* n-variate minimization with bounds using the BFGS algorithm
     g0[n] g[n] p[n] x0[n] y[n] s[n] z[n] H[n*n] C[n*n] tv[2*n]
     xmark[n],ix[n]
   Size of space should be (check carefully?)
      #define spaceming2(n) ((n)*((n)*2+9+2)*sizeof(double))
   nfree: # free variables
   xmark[i]=0 for inside space; -1 for lower boundary; 1 for upper boundary.
   x[] has initial values at input and returns the estimates in return.
   ix[i] specifies the i-th free parameter

*/
   int i,j, i1,i2,it, maxround=1000, fail=0, *xmark, *ix, nfree;
   double small=1.e-20;     /* small value for checking |w|=0   */
   double f0, *g0, *g, *p, *x0, *y, *s, *z, *H, *C, *tv;
   double w,v, alpha, am, h;

   if(n==0) return(0);
   g0=space;   g=g0+n;  p=g+n;   x0=p+n;
   y=x0+n;     s=y+n;   z=s+n;   H=z+n;  C=H+n*n, tv=C+n*n;
   xmark=(int*)(tv+2*n);  ix=xmark+n;

   FOR (i,n)  { xmark[i]=0; ix[i]=i; }
   for(i=0,nfree=0;i<n;i++) {
      if(x[i]<=xb[i][0]) { x[i]=xb[i][0]; xmark[i]=-1; continue; }
      if(x[i]>=xb[i][1]) { x[i]=xb[i][1]; xmark[i]= 1; continue; }
      ix[nfree++]=i;
   }
   if(nfree<n && n<50) {
      FPN(F0);  FOR(j,n) printf(" %9.6f", x[j]);  FPN(F0);
      FOR(j,n) printf(" %9.5f", xb[j][0]);  FPN(F0);
      FOR(j,n) printf(" %9.5f", xb[j][1]);  FPN(F0);
      if(nfree<n) printf("warning: ming2, %d paras at boundary.",n-nfree);
   }

   f0=*f=(*fun)(x,n);
   xtoy(x,x0,n);
   if (noisy>2) {
      printf ("\nIterating by ming2\nInitial: fx= %12.6f\nx=",f0);
      FOR(i,n) printf("%9.5f",x[i]);   FPN(F0);
   }

   if (dfun)  (*dfun) (x0, &f0, g0, n);
   else       gradientB (n, x0, f0, g0, fun, tv, xmark);

   SIZEp=0; identity (H,nfree);
   FOR (Iround, maxround) {
      for (i=0,zero(p,n); i<nfree; i++)  FOR (j,nfree)
         p[ix[i]] -= H[i*nfree+j]*g0[ix[j]];
      SIZEp=norm(p,n);      /* check this */

      for (i=0,am=20; i<n; i++) {  /* max2 step length */
         if (p[i]>0 && (xb[i][1]-x0[i])/p[i]<am) am=(xb[i][1]-x0[i])/p[i];
         else if (p[i]<0 && (xb[i][0]-x0[i])/p[i]<am) am=(xb[i][0]-x0[i])/p[i];
      }

      if (Iround==0)    h=fabs(2*f0*.01/innerp(g0,p,n));  /* check this?? */
      else              h=norm(s,nfree)/SIZEp;
      h=max2(h,1e-5);   h=min2(h,am/8);
      *f=f0;
      alpha = LineSearch2(fun,f,x0,p,h,am, min2(1e-5,e*10), tv,n); /* n or nfree? */

      if (alpha<=0) {
         if (fail) {
            if (AlwaysCenter) { Iround=maxround;  break; }
            else { AlwaysCenter=1; identity(H,n); fail=1; }
         }
         else   
            { if(noisy>2) printf(".. ");  identity(H,nfree); fail=1; }
      }
      else  {
         fail=0;
         FOR(i,n)  x[i]=x0[i]+alpha*p[i];
         if (fout) {
            fprintf (fout, "\n%3d %7.4f %13.6f  x: ", Iround+1, SIZEp, *f);
            FOR (i,n) fprintf (fout, "%8.5f  ", x[i]);
            fflush (fout);
         }
         w=.2;  if(e<1e-4) w=0.01;  if(e<1e-6) w=e*1000;
         if (SIZEp<w && (f0- *f<2.0) && H_end(x0,x,f0,*f,e,e,n))
            break;
      }
      if (dfun)  (*dfun) (x, f, g, n);
      else       gradientB (n, x, *f, g, fun, tv, xmark);

      /* modify the working set */
      FOR (i, n) {         /* add constraints, reduce H */
         if (xmark[i]) continue;
         if (fabs(x[i]-xb[i][0])<1e-6 && -g[i]<0)  xmark[i]=-1;
         else if (fabs(x[i]-xb[i][1])<1e-6 && -g[i]>0)  xmark[i]=1;
         if (xmark[i]==0) continue;
         xtoy (H, C, nfree*nfree);
         FOR (it, nfree) if (ix[it]==i) break;
         for (i1=it; i1<nfree-1; i1++) ix[i1]=ix[i1+1];
         for (i1=0,nfree--; i1<nfree; i1++) FOR (i2,nfree)
            H[i1*nfree+i2]=C[(i1+(i1>=it))*(nfree+1) + i2+(i2>=it)];
      }
      for (i=0,it=0,w=0; i<n; i++) {  /* delete a constraint, enlarge H */
         if (xmark[i]==-1 && -g[i]>w)     { it=i; w=-g[i]; }
         else if (xmark[i]==1 && -g[i]<-w) { it=i; w=g[i]; }
      }
      if (w>10*SIZEp/nfree) {          /* *** */
         xtoy (H, C, nfree*nfree);
         FOR (i1,nfree) FOR (i2,nfree) H[i1*(nfree+1)+i2]=C[i1*nfree+i2];
         FOR (i1,nfree+1) H[i1*(nfree+1)+nfree]=H[nfree*(nfree+1)+i1]=0;
         H[(nfree+1)*(nfree+1)-1]=1;
         xmark[it]=0;   ix[nfree++]=it;
      }

      if (noisy>2) {
         printf (" |%3d/%d", n-nfree, n);
         /* FOR (i,n)  if (xmark[i]) printf ("%4d", i+1); */
      }
      for (i=0,f0=*f; i<nfree; i++)
        {  y[i]=g[ix[i]]-g0[ix[i]];  s[i]=x[ix[i]]-x0[ix[i]]; }
      FOR (i,n) { g0[i]=g[i]; x0[i]=x[i]; }

      for (i=0,w=v=0.; i<nfree; i++) {
         for (j=0,z[i]=0.; j<nfree; j++) z[i]+=H[i*nfree+j]*y[j];
         w+=y[i]*z[i];    v+=y[i]*s[i];
      }
      if (fabs(v)<small)   { identity(H,nfree); fail=1; continue; }
      FOR (i,nfree)  FOR (j,nfree)
         H[i*nfree+j] += ((1+w/v)*s[i]*s[j]-z[i]*s[j]-s[i]*z[j])/v;
   }    /* for (Iround,maxround)  */

   *f=(*fun)(x,n);  /* try to remove this after updating LineSearch2() */
   if (noisy>2) FPN(F0);

   if (Iround==maxround) {
      if (fout) fprintf (fout,"\ncheck convergence!\n");
      return(-1);
   }
   return(0);
}



int ming1 (FILE *fout, double *f, double (* fun)(double x[], int n),
    int (*dfun) (double x[], double *f, double dx[], int n),
    int (*testx) (double x[], int n),
    double x0[], double space[], double e, int n)
{
/* n-D minimization using quasi-Newton or conjugate gradient algorithms, 
   using function and its gradient.

   g0[n] g[n] p[n] x[n] y[n] s[n] z[n] H[n*n] tv[2*n]
   using bound()
*/
   int i,j, maxround=1000, fail=0;
   double small=1.e-20;     /* small value for checking |w|=0   */
   double f0, *g0, *g, *p, *x, *y, *s, *z, *H, *tv;
   double w,v, t, h;

   if (testx (x0, n))
      { printf ("\nInvalid initials..\n"); matout(F0,x0,1,n); return(-1); }
   f0 = *f = (*fun)(x0, n);

   if (noisy>2) {
      printf ("\n\nIterating by ming1\nInitial: fx= %12.6f\nx=", f0);
      FOR (i,n) printf ("%8.4f", x0[i]);       FPN (F0);
   }
   if (fout) {
      fprintf (fout, "\n\nIterating by ming1\nInitial: fx= %12.6f\nx=", f0);
      FOR (i,n) fprintf (fout, "%10.6f", x0[i]);
   }
   g0=space;   g=g0+n;  p=g+n;   x=p+n;
   y=x+n;      s=y+n;   z=s+n;   H=z+n;  tv=H+n*n;
   if (dfun)  (*dfun) (x0, &f0, g0, n);
   else       gradient (n, x0, f0, g0, fun, tv, AlwaysCenter);

   SIZEp=0;  xtoy (x0, x, n);  xtoy (g0,g,n);  identity (H,n);  
   FOR (Iround, maxround) {
      FOR (i,n) for (j=0,p[i]=0.; j<n; j++)  p[i] -= H[i*n+j]*g[j];
      t=bound (n, x0, p, tv, testx);

      if (Iround == 0)  h = fabs(2*f0*.01/innerp(g,p,n));
      else              h = norm(s,n)/SIZEp;
      h = max2(h,1e-5);  h = min2(h,t/8);
      SIZEp = norm(p,n);

      t = LineSearch2 (fun, f, x0, p, h, t, .00001, tv, n);

      if (t<=0 || *f<=0 || *f>1e32) {
         if (fail) {
            if(SIZEp>.1 && noisy>2) 
               printf("\nSIZEp:%9.4f  Iround:%5d", SIZEp, Iround+1);
            if (AlwaysCenter) { Iround=maxround;  break; }
            else { AlwaysCenter=1; identity(H,n); fail=1; }
         }
         else      { identity(H, n); fail=1; }
      }
      else  {
         fail=0;
         FOR(i,n)  x[i]=x0[i]+t*p[i];

         if (fout) {
            fprintf (fout, "\n%3d %7.4f%14.6f  x", Iround+1, SIZEp, *f);
            FOR (i,n) fprintf (fout, "%8.5f  ", x[i]);
            fflush (fout);
         }
         if (SIZEp<0.001 && H_end (x0,x,f0,*f,e,e,n))
            { xtoy(x,x0,n); break; }
      }
      if (dfun)  (*dfun) (x, f, g, n);
      else       gradient (n,x,*f,g,fun,tv, (AlwaysCenter||fail||SIZEp<1));

      for (i=0,f0=*f; i<n; i++)
         { y[i]=g[i]-g0[i];  s[i]=x[i]-x0[i];  g0[i]=g[i]; x0[i]=x[i]; }

      /* renewal of H varies with different algorithms   */
#ifdef SR1
      /*   Symmetrical Rank One (Broyden, C. G., 1967) */
      for (i=0,w=.0; i<n; i++) {
         for (j=0,t=.0; j<n; j++) t += H[i*n+j] * y[j];
         z[i]=s[i] - t;
         w += y[i]*z[i];
      }
      if (fabs(w)<small)   { identity(H,n); fail=1; continue; }
      FOR (i,n)  FOR (j,n)  H[i*n+j] += z[i]*z[j]/w;
#else
#ifdef DFP
      /* Davidon (1959), Fletcher and Powell (1963). */
      for (i=0,w=v=0.; i<n; i++) {
         for (j=0,z[i]=.0; j<n; j++) z[i] += H[i*n+j] * y[j];
         w += y[i]*z[i];  v += y[i]*s[i];
      }
      if (fabs(w)<small || fabs(v)<small)  { identity(H,n); fail=1; continue;}
      FOR (i,n)  FOR (j,n)  H[i*n+j] += s[i]*s[j]/v - z[i]*z[j]/w;
#else
      for (i=0,w=v=0.; i<n; i++) {
         for (j=0,z[i]=0.; j<n; j++) z[i] += H[i*n+j] * y[j];
         w+=y[i]*z[i];    v+=y[i]*s[i];
      }
      if (fabs(v)<small)   { identity(H,n); fail=1; continue; }
      FOR (i,n)  FOR (j,n)
         H[i*n+j] += ( (1+w/v)*s[i]*s[j] - z[i]*s[j] - s[i]*z[j] ) / v;
#endif
#endif
   }    /* for (Iround,maxround)  */

   if (Iround==maxround) {
      if (fout) fprintf (fout,"\ncheck convergence!\n");
      return(-1);
   }
   return(0);
}
