/* 
 * File:   Utils.h
 * Author: fede
 *
 * Created on 19 de julio de 2014, 07:49 PM
 */

#ifndef UTILS_H
#define	UTILS_H

class Utils{
public:
    static void toHexChar(unsigned char convert, unsigned char& out1, unsigned char& out2){
        unsigned char firstDigit = convert >> 4;
        unsigned char secondDigit = convert & 0xF;
        out1 = (unsigned char) (firstDigit < 10? (firstDigit + '0') : (firstDigit + 55));
        out2 = (unsigned char) (secondDigit < 10? (secondDigit + '0') : (secondDigit + 55));
    }
    
};

#endif	/* UTILS_H */

