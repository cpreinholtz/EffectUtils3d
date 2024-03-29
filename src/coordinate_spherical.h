#pragma once

#ifdef TEST_CONFIG
#include <cmath>
#endif

#include <vector3d.h>


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
        theta = constrain(t, 0, 360);
        phi = constrain(p, 0, 180);
    }

    void set(Vector3d v) {
        float r = sqrt(pow(v.mX, 2) + pow(v.mY, 2) + pow(v.mZ, 2));
        float t = 0;
        if (v.mY > 0 && v.mX > 0) {
            t = radToDeg(atan(abs(v.mY) / abs(v.mX))) ;
        }
        else if (v.mY > 0 && v.mX < 0) {
            t = 180.0 - radToDeg(atan(v.mY / abs(v.mX))) ;
        }
        else if (v.mY < 0 && v.mX < 0) {
            t = 180.0 + radToDeg(atan(abs(v.mY) / abs(v.mX))) ;
        } 
        else if (v.mY < 0 && v.mX > 0) {
            t = 360 - radToDeg(atan(abs(v.mY) / v.mX));
        }        
        float p = radToDeg(acos(v.mZ / r));
        set(r, t, p);
    }

    //**************************************************************
    // getters
    //**************************************************************
    Vector3d getVector3d(){
        float x = radias * sin(degToRad(phi)) * cos(degToRad(theta));
        float y = radias * sin(degToRad(phi)) * sin(degToRad(theta));
        float z = radias * cos(degToRad(phi));
        Vector3d vector(x, y, z);
        return vector;
    }

    




    //**************************************************************
    // Misc
    //**************************************************************
#ifdef TEST_CONFIG
#include <iostream>

    friend ostream& operator<<(ostream& os, const CoordSpherical& dt) {
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