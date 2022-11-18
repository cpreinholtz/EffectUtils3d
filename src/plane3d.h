#include <vector3d.h>

#pragma once





class Plane3d {
private:


public:
    //the plane will be described using the point normal method (a reference point on the plane and a non-zero vector orthogonal to the plane)
    Vector3d mNormalVector;//Should really be private because it MUST be a unit vector, which occours in the set function
    Vector3d mRefPoint;

    //**************************************************************
    // Constructors
    //**************************************************************
    Plane3d(Vector3d refPoint, Vector3d normalVector) {
        set(refPoint, normalVector);
    }

    //default constructor
    Plane3d() {
        Vector3d refPoint(0, 0, 0);
        Vector3d normalVector(1, 0, 0);
        set(refPoint, normalVector);
    }

    //**************************************************************
    // actions
    //**************************************************************
    // 
    //revolve around a point
        //use the point as the ref coord
        //set yaw pitch and roll rates

    //rotate around the origin
    
    //translate


    //**************************************************************
    // setters
    //**************************************************************
    void set(Vector3d refPoint, Vector3d normalVector) {
        mRefPoint = refPoint;
        mNormalVector = normalVector;
        mNormalVector.constrianNonZero();
        mNormalVector.makeUnitVector();
    }


    //**************************************************************
    // getters
    //**************************************************************
    //consider removing
    Vector3d getRefPoint() const {
        return mRefPoint;
    }

    Vector3d getNormalVector() const {
        return mNormalVector;
    }


    //**************************************************************
    // Utilities
    //**************************************************************
    
    //returns SIGNED distance from the plane (negative numbers result from being on the opposite side as the normal vector)
    float distance(Vector3d postition) const {
        //https://mathinsight.org/distance_point_plane

        //d = | v DOT n |  
        //where n is UNIT normal vector  //dont need to divide by length of normal vector bc normal vector is already a unit vector
        //v is the vector connecting our refernece point on our plane and the position to find distance of
        Vector3d v(postition - mRefPoint);
        float result = v.dot(mNormalVector);
        //lets return a signed number which will tell us if "poisiton" is above or below the plane WRT the normal vector
        return result;
    }

    //CONSIDER MAKING A BASE CLASS FOR ALL GEOMETRIC OBJS AND PLACING THIS IN THERE
    //overload distance function for dicrete coordinates
    float distance(float x, float y, float z) const {
        Vector3d c(x, y, z);
        return distance(c);
    }


#ifdef TEST_CONFIG
#include <iostream>

    friend std::ostream& operator<<(std::ostream& os, const Plane3d& dt) {
        os << dt.mRefPoint << dt.mNormalVector;
        return os;
    }
#endif


};

