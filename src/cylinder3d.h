#pragma once
#include <line3d.h>

class Cylinder3d {
public:
    //a Cylinder will be defined by a line (cener of axis) and a radias and 
    //perhaps add height offset from refence point in the future but for now its infinate
    float mRadias;
    Line3d mCenterLine;

    //**************************************************************
    // Constructors
    //**************************************************************
    //default
    Cylinder3d() {
        Vector3d refPoint(0, 0, 0);
        Vector3d directionVector(1, 0, 0);
        float radias = 0;
        set(refPoint, directionVector, radias);
    }

    Cylinder3d(Vector3d refPoint, Vector3d directionVector, float radias) {
        set(refPoint, directionVector, radias);
    }

    //**************************************************************
    // setters
    //**************************************************************
    void set(Vector3d refPoint, Vector3d directionVector, float radias) {
        mCenterLine.set(refPoint, directionVector);
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

    //find the distance from a point to the surface of the cylinder
    //if point is outside radias, d is positive, otherwise d is neg if inside
    float distance(Vector3d point) const{
        float d = mCenterLine.distance(point);  //first find distance from center line
        //now calcuate distance from surface of cyl
        d = d - mRadias;
        //if radias is negative all things will apear dist to center+R which would be odd but interesting
        return d;
    }





#ifdef TEST_CONFIG
#include <iostream>

    friend std::ostream& operator<<(std::ostream& os, const Plane3d& dt) {
        os << dt.mCenterLine << dt.mRadias;
        return os;
    }
#endif

};