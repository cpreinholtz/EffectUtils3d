#pragma once


class CoordSpherical {
public:
    float radias;
    float theta;
    float phi;


    //**************************************************************
    // Constructors
    //**************************************************************
    //default
    CoordSpherical() {
        set(0, 0, 0);
    }

    CoordSpherical(float r, float t, float p) {
        set(r, t, p);
    }



    //**************************************************************
    // setters
    //**************************************************************
    //set by passing in x, y, and z
    void set(float r, float t, float p) {
        radias = r;
        theta = constrain(theta, 0, 360);
        phi = constrain(theta, 0, 180);
    }

    void set(Coord3d c
        art) {
        radias =
    }




    //**************************************************************
    // Misc
    //**************************************************************
#ifdef TEST_CONFIG
#include <iostream>

    friend ostream& operator<<(ostream& os, const Coord3d& dt) {
        os << "(" << dt.radias << "," << dt.theta << "," << dt.phi << ")";
        return os;
    }
#endif

private:

    //void normalize() {
    //    while (theta < 0.0) theta = theta + 360;
    //    while (theta > 360.0) theta = theta - 360;

    //    //assume that someon entering 181 really mean 179
    //    while (phi < 0.0) phi = phi + 360;
    //    while (phi > 360.0) phi = phi - 360;
    //}

};