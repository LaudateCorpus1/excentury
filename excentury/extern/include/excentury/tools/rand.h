/** RAND.H
% Author: Manuel Lopez <jmlopez.rod@gmail.com>
% License: http://creativecommons.org/licenses/by-sa/3.0/
% Date Created: April 26, 2010
% Last Modified: December 13, 2013
*/

/*
Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

 - Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

 - Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in
   the documentation and/or other materials provided with the
   distribution.

 - The names of its contributors may not be used to endorse or
   promote products derived from this software without specific prior
   written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

Any feedback is very welcome.
http://www.math.keio.ac.jp/matumoto/emt.html
email: matumoto@math.keio.ac.jp
*/

#ifndef XC_RAND_H
#define XC_RAND_H

namespace excentury {

#include "_norm_CDF.h"

class MTRand {
private:
    unsigned long int _mt[624];
    unsigned int index;

public:
    static unsigned int total;
    MTRand() {
        ++total;
        long int tmp(total);  // total is unsigned and so is -total
        seed(-tmp);
    }
    MTRand(const long int &s) {
        ++total;
        seed(s);
    }
    void seed(long int seed_) {
        register int i = 1;
        if (seed_ > 0) {
            _mt[0] = (unsigned long int)seed_ & 0xffffffffUL;
        } else {
            _mt[0] = (unsigned long int)time(0) - seed_;
        }
        for (; i < 624; ++i) {
            _mt[i] = (1812433253UL*(_mt[i-1] ^ (_mt[i-1] >> 30)) + i)
                     & 0xffffffffUL;
        }
        index = i;
    }
    // integer in [0, 2^32-1]
    unsigned long int rand_int() {
        register unsigned long int k;
        register int i = 0;
        if (index == 624) {
            for (; i < 227; ++i){
                k = (_mt[i] & 0x80000000UL) | (_mt[i+1] & 0x7fffffffUL);
                _mt[i] = _mt[i+397] ^ ( k >> 1) ^
                         (k & 0x1UL ? 0x9908b0dfUL : 0x0UL);
            }
            for (; i < 623; ++i){
                k = (_mt[i] & 0x80000000UL) | (_mt[i+1] & 0x7fffffffUL);
                _mt[i] = _mt[i-227] ^ ( k >> 1) ^
                         (k & 0x1UL ? 0x9908b0dfUL : 0x0UL);
            }
            k = (_mt[623] & 0x80000000UL) | (_mt[0] & 0x7fffffffUL);
            _mt[623] = _mt[396] ^ ( k >> 1) ^
                       (k & 0x1UL ? 0x9908b0dfUL : 0x0UL);
            index = 0;
        }
        k = _mt[index++];
        k ^= (k >> 11);
        k ^= (k << 7) & 0x9d2c5680UL;
        k ^= (k << 15) & 0xefc60000UL;
        k ^= (k >> 18);
        return k;
    }
    // real number in (0,1)
    double rand() {
        return ((double)(rand_int())+0.5)*(1.0/4294967296.0);
    }
    // real number in [0,1]
    double rand_inc() {
        return ((double)(rand_int()))*(1.0/4294967295.0);
    }
    // real number in [0,1)
    double rand_left_inc() {
        return ((double)(rand_int()))*(1.0/4294967296.0);
    }
    /* Reference:
    * http://www.taygeta.com/random/gaussian.html
    */
    double normal(const double &mean_, const double& std_) {
        register double i, j, k;
        do {
            i = 2.0 * rand_inc() - 1.0;
            j = 2.0 * rand_inc() - 1.0;
            k = i*i + j*j;
        } while (k >= 1.0 || k == 0.0);
        return mean_ + i * std_ * sqrt(-2.0*log(k)/k);
    }
    /* Reference:
    Marsaglia, G., and W. W. Tsang.
    "A Simple Method for Generating Gamma Variables."
    ACM Transactions on Mathematical Software. Vol. 26, 2000, pp. 363–372.
    Returns:
    returns a random number chosen from gamma distributions with unit scale.
    randg generates the number using a shape parameter equal to a.
    */
    double randg(double a) {
        register double d, c, x, v, u;
        d = a-1.0/3.0;
        c = 1.0/sqrt(9.0*d);
        for (;;) {
            do {
                x = normal(0.0, 1.0);
                v = 1.0 + c*x;
            } while (v <= 0.0);
            v = v*v*v;
            u = rand();
            if (u < 1.0-0.0331*(x*x)*(x*x)) return (d*v);
            if (log(u) < 0.5*x*x+d*(1.0-v+log(v))) return (d*v);
        }
    }
    double gamrnd(double a, double b) {
        if (a < 1) return b*randg(a+1.0)*pow(rand(), 1.0/a);
        return b*randg(a);
    }
};

unsigned int MTRand::total = 0;

/* rg.rand() is a random number from [0, 1).
 * Uniform(a, b) = a + (b-a)*random.rand()
 * m = (a+b)/2
 * s = (sqrt((b-a)*(b-a)/12))
 * a = m - sqrt(3)*s
 * b = m + sqrt(3)*s
 * Uniform(m, s) = m + (2*random.rand()-1)*sqrt(3)*s
 */
template<class T>
inline double uniform_rand(T& rg_, double mean_, double std_) {
    return mean_+(2.0*rg_.rand()-1.0)*sqrt(3.0)*std_;
}

template<class T>
inline double gamma_rand(T& rg_, double mean_, double std_) {
    if (mean_ == 0) return 0;
    if (std_ == 0) return mean_;
    return rg_.gamrnd(mean_*mean_/(std_*std_), (std_*std_)/mean_);
}

template<class T>
inline double exp_rand(T& rg_, double mean_, double std_) {
    return mean_ - std_ - log(rg_.rand())*std_;
}

template<class T>
inline double delta_rand(T& rg_, double t, double s, double b) {
    if (rg_.rand() < b) {
        return t - s*(1.0-b)/sqrt(b*(1.0-b));
    }
    return t + s*b/sqrt(b*(1.0-b));
}

template<class T>
inline double truncated_normal_rand(T& rg_, double t, double s) {
    static double ns;
    static double x;
    static double os = -1.0;  // old value of s

    if (os != s) {
        os = s;
        double cdfvalp;
        double cdfvalq;
        double pdfval;

        double at = -t/s;
        double num;
        double den;

        pdfval = M_2_SQRTPI*M_SQRT1_2*at*exp(-0.5*(at)*(at));
        cdfnor(&cdfvalp, &cdfvalq, &at, &t, &s);
        den = 1.0 - 2.0*cdfvalp;
        num = 1.0 + pdfval/(1.0-2.0*cdfvalp);

        ns = (s == 0.0) ? 0.0 : sqrt(num)*s;
    }
    x = rg_.normal(t, ns);
    while (x < 0 || x > 2*t) {
        x = rg_.normal(t, ns);
    }
    return x;
}

}

#endif
