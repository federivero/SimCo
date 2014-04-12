/* 
 * File:   CustomMacros.h
 * Author: fede
 *
 * Created on 26 de marzo de 2014, 02:12 PM
 */

#ifndef CUSTOMMACROS_H
#define	CUSTOMMACROS_H

#include <cmath>

#define log2(x) (log((double) (x))) / (log(2.0))
#define intlog2(x) round(log2(x))
#define isPowerOf2(x) ((x > 0) && (!(x & (x - 1))))
#define base2Exp(x) (1 << x)

#endif	/* CUSTOMMACROS_H */

