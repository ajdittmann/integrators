#ifndef INTEGRATE_H
#define INTEGRATE_H

#include "interval.h"

double trap(double (*f)(double, void *), double xa, double xb, int N,
            void *args);
double simp(double (*f)(double, void *), double xa, double xb, int N,
            void *args);
double romb(double (*f)(double, void *), double xa, double xb, int N,
            double atol, double rtol, void *args, int *Neval, double *eps,
            int verbose);

double gl(double (*f)(double, void *), double xa, double xb, int N,
          void *args);
double quad(double (*f)(double, void *), double xa, double xb, int N,
            void *args, double *zi, double *wi, double za, double zb);
double trap_adapt(double (*f)(double, void *), double xa, double xb, int Nmax,
                  double atol, double rtol, void *args, int *Neval,
                  double *eps, struct Mesh3 *mout, int verbose);
double simp_adapt(double (*f)(double, void *), double xa, double xb, int Nmax,
                  double atol, double rtol, void *args, int *Neval,
                  double *eps, struct Mesh5 *mout, int verbose);
double gl7_adapt(double (*f)(double, void *), double xa, double xb, int Nmax,
                 double atol, double rtol, void *args, int *Neval,
                 double *eps, struct Mesh *mout, int verbose);
double gen_adapt(double (*f)(double, void *), double xa, double xb, int Nmax,
                 int (*processInterval)(double (*f)(double, void*), void *,
                                         Interval *),
                 int (*splitInterval)(double (*f)(double, void *), void *,
                                Interval *, Interval *, Interval *),
                 double atol, double rtol, void *args, int *Neval,
                 double *eps, struct Mesh *mout, int verbose);
double m3_adapt(double (*f)(double, void *), double xa, double xb, int Nmax,
                 int (*processInterval)(double (*f)(double, void*), void *,
                                         Interval3 *),
                 int (*splitInterval)(double (*f)(double, void *), void *,
                                Interval3 *, Interval3 *, Interval3 *),
                 double atol, double rtol, void *args, int *Neval,
                 double *eps, struct Mesh3 *mout, int verbose);
double m5_adapt(double (*f)(double, void *), double xa, double xb, int Nmax,
                 int (*processInterval)(double (*f)(double, void*), void *,
                                         Interval5 *),
                 int (*splitInterval)(double (*f)(double, void *), void *,
                                Interval5 *, Interval5 *, Interval5 *),
                 double atol, double rtol, void *args, int *Neval,
                 double *eps, struct Mesh5 *mout, int verbose);
int trapProcessInterval(double (*f)(double, void *), void *args, Interval3 *i);
int trapSplitInterval(double (*f)(double, void *), void *args,
                        Interval3 *i0, Interval3 *i1, Interval3 *i2);
int simpProcessInterval(double (*f)(double, void *), void *args, Interval5 *i);
int simpSplitInterval(double (*f)(double, void *), void *args,
                      Interval5 *i0, Interval5 *i1, Interval5 *i2);
int gl7ProcessInterval(double (*f)(double, void *), void *args, Interval *i);
int gl7SplitInterval(double (*f)(double, void *), void *args,
                        Interval *i0, Interval *i1, Interval *i2);
void glPoints(int *N, double *x, double *w);

#endif
