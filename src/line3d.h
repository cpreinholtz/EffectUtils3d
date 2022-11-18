#pragma once
#include <vector3d.h>




class Line3d {
public:
    //lines will be defined with a refence point and a direction
    Vector3d mRefPoint;
    Vector3d mDirectionVector;//cannot be zero vector!!!


    //**************************************************************
    // Constructors
    //**************************************************************
    //default
    Line3d() {
        Vector3d refPoint(0, 0, 0);
        Vector3d directionVector(1, 0, 0);
        set(refPoint, directionVector);
    }

    Line3d(Vector3d refPoint, Vector3d directionVector) {
        set(refPoint, directionVector);
    }



    //**************************************************************
    // setters
    //**************************************************************
    //set by passing in x, y, and z
    void set(Vector3d refPoint, Vector3d directionVector) {
        mRefPoint = refPoint;
        mDirectionVector = directionVector;
        mDirectionVector.constrianNonZero();
    }
    //**************************************************************
    // getters
    //**************************************************************

    //**************************************************************
    // Actions
    //**************************************************************

    //Distance from a point to our line
    //https://onlinemschool.com/math/library/analytic_geometry/p_line/#:~:text=Online%20calculator.-,Distance%20from%20a%20point%20to%20a%20line%20%2D%203%2DDimensional.,the%20point%20to%20the%20line.
    //If M0(x0, y0, z0) point coordinates, s = {m; n; p} directing vector of line l, M1(x1, y1, z1) - coordinates of point on line l, 
    //then distance between point M0(x0, y0, z0) and line l can be found using the following formula:
    //d = | M0M1×s| /  |s |
    float distance(Vector3d point) const {
        Vector3d numerator = point - mRefPoint;
        numerator = numerator.cross(mDirectionVector);
        return (numerator.length() / mDirectionVector.length());
    }


    //**************************************************************
    // Misc
    //**************************************************************
#ifdef TEST_CONFIG
#include <iostream>

    friend std::ostream& operator<<(std::ostream& os, const Line3d& dt) {
        os << dt.mRefPoint << dt.mDirectionVector;
        return os;
    }
#endif


};

