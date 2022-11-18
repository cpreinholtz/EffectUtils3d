#pragma once
#pragma once
#include <vector3d.h>

class Sphere3d {
public:
    //a Sphere will be defined by a point (cener of sphere) and a radias and 
    float mRadias;
    Vector3d mRefPoint;

    //**************************************************************
    // Constructors
    //**************************************************************
    //default
    Sphere3d() {
        Vector3d refPoint(0, 0, 0);
        float radias = 0;
        set(refPoint, radias);
    }

    Sphere3d(Vector3d refPoint, float radias) {
        set(refPoint, radias);
    }

    //**************************************************************
    // setters
    //**************************************************************
    void set(Vector3d refPoint, float radias) {
        mRefPoint = refPoint;
        mRadias = abs(radias);//negative radias would make no sense?  well it would create a buffer zone?
    }


    //**************************************************************
    // Utilities
    //**************************************************************

    //increase (or decrease) radias by this ammount.  
    //radias ensured to remain non negative
    void grow(float delta) {
        mRadias = mRadias + delta;
        if (mRadias < 0.0) mRadias = 0.0;
    }

    //find the distance from a point to the surface of the sphere
    //if point is outside radias, d is positive, otherwise d is neg if inside
    float distance(Vector3d point) const {
        Vector3d connector = point - mRefPoint;
        float d = connector.length();  //first find distance from center point
        //now calcuate distance from surface
        d = d - mRadias;
        //if radias is negative all things will apear dist to center+R which would be odd but interesting
        return d;
    }





#ifdef TEST_CONFIG
#include <iostream>

    friend std::ostream& operator<<(std::ostream& os, const Plane3d& dt) {
        os << dt.mCenterPoint << dt.mRadias;
        return os;
    }
#endif

};