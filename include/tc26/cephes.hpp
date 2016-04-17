
#ifndef _CEPHES_H_
#define _CEPHES_H_

#ifdef WIN32
#ifdef FEX_CNBCDLL
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT __declspec(dllimport)
#endif
#else
#define DLLEXPORT
#endif

extern "C" DLLEXPORT
{
double cephes_igamc(double a, double x);
double cephes_igam(double a, double x);
double cephes_lgam(double x);
double cephes_p1evl(double x, double *coef, int N);
double cephes_polevl(double x, double *coef, int N);
double cephes_erf(double x);
double cephes_erfc(double x);
double cephes_normal(double x);
}

#endif /*  _CEPHES_H_  */
