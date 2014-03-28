/* NORM_CDF.H: Helper header for rand.h
% This file contains only one function of interest: cdfnor
% You can find the original source code here:
% http://www.netlib.org/random/dcdflib.c.tar.gz
% For more info start here:
% http://people.sc.fsu.edu/~jburkardt/cpp_src/dcdflib/dcdflib.html
% The code has been reduced to the bare minimal so that cdfnor works.
*/

inline double fifdint(double a) {
    return (double) ((int) a);
}

int ipmpar(int *i) {
    static int imach[11];
    imach[1] = 2;
    imach[2] = 31;
    imach[3] = 2147483647;
    imach[4] = 2;
    imach[5] = 24;
    imach[6] = -125;
    imach[7] = 128;
    imach[8] = 53;
    imach[9] = -1021;
    imach[10] = 1024;
    return imach[*i];
}

double spmpar(int *i) {
    static int K1 = 4;
    static int K2 = 8;
    static int K3 = 9;
    static int K4 = 10;
    static double spmpar,b,binv,bm1,one,w,z;
    static int emax,emin,ibeta,m;

    if(*i > 1) goto S10;
    b = ipmpar(&K1);
    m = ipmpar(&K2);
    spmpar = pow(b,(double)(1-m));
    return spmpar;
S10:
    if(*i > 2) goto S20;
    b = ipmpar(&K1);
    emin = ipmpar(&K3);
    one = 1.0;
    binv = one/b;
    w = pow(b,(double)(emin+2));
    spmpar = w*binv*binv*binv;
    return spmpar;
S20:
    ibeta = ipmpar(&K1);
    m = ipmpar(&K2);
    emax = ipmpar(&K4);
    b = ibeta;
    bm1 = ibeta-1;
    one = 1.0;
    z = pow(b,(double)(m-1));
    w = ((z-one)*b+bm1)/(b*z);
    z = pow(b,(double)(emax-2));
    spmpar = w*z*b*b;
    return spmpar;
}

void cumnor(double *arg,double *result,double *ccum) {
    static double a[5] = {
        2.2352520354606839287e00,1.6102823106855587881e02,1.0676894854603709582e03,
        1.8154981253343561249e04,6.5682337918207449113e-2
    };
    static double b[4] = {
        4.7202581904688241870e01,9.7609855173777669322e02,1.0260932208618978205e04,
        4.5507789335026729956e04
    };
    static double c[9] = {
        3.9894151208813466764e-1,8.8831497943883759412e00,9.3506656132177855979e01,
        5.9727027639480026226e02,2.4945375852903726711e03,6.8481904505362823326e03,
        1.1602651437647350124e04,9.8427148383839780218e03,1.0765576773720192317e-8
    };
    static double d[8] = {
        2.2266688044328115691e01,2.3538790178262499861e02,1.5193775994075548050e03,
        6.4855582982667607550e03,1.8615571640885098091e04,3.4900952721145977266e04,
        3.8912003286093271411e04,1.9685429676859990727e04
    };
    static double half = 0.5e0;
    static double p[6] = {
        2.1589853405795699e-1,1.274011611602473639e-1,2.2235277870649807e-2,
        1.421619193227893466e-3,2.9112874951168792e-5,2.307344176494017303e-2
    };
    static double one = 1.0e0;
    static double q[5] = {
        1.28426009614491121e00,4.68238212480865118e-1,6.59881378689285515e-2,
        3.78239633202758244e-3,7.29751555083966205e-5
    };
    static double sixten = 1.60e0;
    static double sqrpi = 3.9894228040143267794e-1;
    static double thrsh = 0.66291e0;
    static double root32 = 5.656854248e0;
    static double zero = 0.0e0;
    static int K1 = 1;
    static int K2 = 2;
    static int i;
    static double del,eps,temp,x,xden,xnum,y,xsq,min;

    eps = spmpar(&K1)*0.5e0;
    min = spmpar(&K2);
    x = *arg;
    y = fabs(x);
    if(y <= thrsh) {
        xsq = zero;
        if(y > eps) xsq = x*x;
        xnum = a[4]*xsq;
        xden = xsq;
        for(i=0; i<3; i++) {
            xnum = (xnum+a[i])*xsq;
            xden = (xden+b[i])*xsq;
        }
        *result = x*(xnum+a[3])/(xden+b[3]);
        temp = *result;
        *result = half+temp;
        *ccum = half-temp;
    }
    else if(y <= root32) {
        xnum = c[8]*y;
        xden = y;
        for(i=0; i<7; i++) {
            xnum = (xnum+c[i])*y;
            xden = (xden+d[i])*y;
        }
        *result = (xnum+c[7])/(xden+d[7]);
        xsq = fifdint(y*sixten)/sixten;
        del = (y-xsq)*(y+xsq);
        *result = exp(-(xsq*xsq*half))*exp(-(del*half))**result;
        *ccum = one-*result;
        if(x > zero) {
            temp = *result;
            *result = *ccum;
            *ccum = temp;
        }
    }
    else  {
        *result = zero;
        xsq = one/(x*x);
        xnum = p[5]*xsq;
        xden = xsq;
        for(i=0; i<4; i++) {
            xnum = (xnum+p[i])*xsq;
            xden = (xden+q[i])*xsq;
        }
        *result = xsq*(xnum+p[4])/(xden+q[4]);
        *result = (sqrpi-*result)/y;
        xsq = fifdint(x*sixten)/sixten;
        del = (x-xsq)*(x+xsq);
        *result = exp(-(xsq*xsq*half))*exp(-(del*half))**result;
        *ccum = one-*result;
        if(x > zero) {
            temp = *result;
            *result = *ccum;
            *ccum = temp;
        }
    }
    if(*result < min) *result = 0.0e0;
    if(*ccum < min) *ccum = 0.0e0;
}

/* CDFNOR FUNCTION */
inline void cdfnor(double *p, double *q, double *x,double *mean, double *sd) {
    static double z;
    z = (*x-*mean)/ *sd;
    cumnor(&z,p,q);
}
