#pragma once


//#define PI 3.14159265359

float degToRad(float deg) {
    return deg * PI / 180.0;
}
float radToDeg(float rad) {
    return rad * 180.0 / PI;
}


float myAbs(float res) {
    if (res < 0.0) res = -res;  //ABS
    return res;
}

