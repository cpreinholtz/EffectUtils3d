#include <vector3d.h>

#pragma once





class Plane {
private:
    //the plane will be described using the point normal method (a reference point on the plane and a non-zero vector orthogonal to the plane)
    Coord3d mRefPoint;
    Vector mNormalVector;


public:
    //**************************************************************
    // Constructors
    //**************************************************************
    Plane(Coord3d refPoint, Vector normalVector) {
        set(refPoint, normalVector);
    }

    //default constructor
    Plane() {
        Coord3d refPoint(0, 0, 0);
        Vector normalVector(1, 0, 0);
        set(refPoint, normalVector);
    }

    //**************************************************************
    // actions
    //**************************************************************

    //signed distance(to see if something is on the same or opposite side of normal vector definition)

    //**************************************************************
    // setters
    //**************************************************************
    void set(Coord3d refPoint, Vector normalVector) {
        mRefPoint = refPoint;
        mNormalVector = normalVector;
        makeUnitVector();
    }


    //**************************************************************
    // getters
    //**************************************************************
    Coord3d getRefPoint() const {
        return mRefPoint;
    }

    Vector getNormalVector() const {
        return mNormalVector;
    }


    //https://mathinsight.org/distance_point_plane
    float getDistance(Coord3d postition) {
        float res = getSignedDistance(postition);
        if (res < 0.0) res = -res;  //ABS
        return res;
    }

    float getDistance(float x, float y, float z) {
        Coord3d c(x, y, z);
        return getDistance(c);
    }

    float getSignedDistance(Coord3d postition) {

        //can do this with less multiplies if we do |A(X1-X0) +B(Y1-Y0) + C(Z1-Z0)|   
        //where P0is refpoint and P1 is position and ABC is normal unit vector
        //this works though
        float res = mNormalVector.mX * postition.x + mNormalVector.mY * postition.y + mNormalVector.mZ * postition.z; //AX1+BY1+CY1
        res = res - mNormalVector.mX * mRefPoint.x - mNormalVector.mY * mRefPoint.y - mNormalVector.mZ * mRefPoint.z; //-AX0 + BY0 + CY0
        //dont need to divide by length of normal vector bc normal vector is already a unit vector
        return res;
    }

    float getSignedDistance(float x, float y, float z) {
        Coord3d c(x, y, z);
        return getSignedDistance(c);
    }

private:
    //**************************************************************
    // private actions and setters
    //**************************************************************

    //take the internal Normal Vector member and convert it to a unit vector
    void makeUnitVector() {
        constrianNonZero();             //ensure we dont divide by zero...
        mNormalVector = mNormalVector / mNormalVector.getLength();
    }

    //take the internal Normal Vector member and convert it to a unit vector
    void constrianNonZero() {
        if (mNormalVector.mX == 0 and mNormalVector.mY == 0 and mNormalVector.mZ == 0) {
            mNormalVector.set(1, 0, 0);
        }
    }

};

