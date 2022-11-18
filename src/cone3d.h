#pragma once


#include <vector3d.h>
#include <plane3d.h> //used for distance
#include <line3d.h> //used for distance

class Cone3d {
private:

 
public:
    //the cone will be described using
    
    Vector3d mRefPoint;     //center of the "bottom" circle
    Vector3d mNormalVector;//normal vector of the "bottom" circle
    float mRadias;          //radias of the "bottom" circle
    Vector3d mTopPoint;     //top of the cone.  I hope to allow for non "right" cones in which the top point is not necisarilly directly above

    //**************************************************************
    // Constructors
    //**************************************************************
    Cone3d(Vector3d refPoint, Vector3d normalVector, float radias, Vector3d topPoint ) {
        set(refPoint, normalVector, radias, topPoint);
    }

    //default constructor
    Cone3d() {
        Vector3d refPoint(0, 0, 0);
        Vector3d normalVector(1, 0, 0);
        float radias = 1.0;
        Vector3d topPoint(1, 0, 0);
        set(refPoint, normalVector, radias, topPoint);
    }


    //**************************************************************
    // setters
    //**************************************************************
    void set(Vector3d refPoint, Vector3d normalVector, float radias, Vector3d topPoint) {
        mRefPoint = refPoint;
        mNormalVector = normalVector;
        mRadias = abs(radias);
        mTopPoint = topPoint;
        mNormalVector.constrianNonZero();
        mNormalVector.makeUnitVector();
    }


    //**************************************************************
    // getters
    //**************************************************************


    //**************************************************************
    // Utilities
    //**************************************************************

    //Okay, so actually finding the distance of a point from a surface of a cone is insane (linear algebra) 
    //but here is a *decent* approximation 
    //(there will be artifacts aka features on the plane level with the bottom circle and top point)
    //dist will be negative if inside cone
    float distance(Vector3d position) const {
        //we are going to assess some cases seperatly 
        // (for these descriptions imagine the cone is straight up and down like a birthday hat)
        Plane3d p2(mRefPoint, mNormalVector);//make a plane from the bottom circle definitions
        float coneHeight = p2.distance(mTopPoint); //find total height of cone
        float pointHeight = p2.distance(position); //find height of pos
        float dist;

        if (coneHeight * pointHeight < 0.0) {//lazy way to tell if the points are on opposite sides of the plane
            //the point is "below" the cone but inside the bottom circle when projected onto that plane
            dist = abs(pointHeight); //find the distance from plane
            float distFromCenter = mRefPoint.distance(position);
            if (distFromCenter > mRadias) { //if not near the circle
                float distFromRadiasRatio = distFromCenter / mRadias;
                dist = dist * distFromRadiasRatio;//this creates exponential decay downwards, but a nice fade outwards
            }
        }
        else if (abs(coneHeight) < abs(pointHeight)) {//point is "above" cone
            //the point is "above" the cone 
            Vector3d v3 = position - mTopPoint;// just compute the distance from top to point
            dist = v3.length();//(this sort of breaks if the cone is very "fat" because the point may be closer to the surface)
        }
        else { //only thing left is in line (sideways) with cone
            //the point is "level with" the cone  (below top point but above bottom)
            //compute distance from center line, 
            //but subtract the cone radias at that height (find distance from bottom plane for height)
            Vector3d v2 = mTopPoint - mRefPoint; //direction vector for center line
            Line3d l2(mRefPoint, mNormalVector); //create center line( note this is different from normal vector for oblong cones
            float c2 = l2.distance(position); //find distance from center line
            float heightRatio = pointHeight / coneHeight;//make height into a ratio
            dist = c2 - mRadias * abs(heightRatio); // use that ratio for finding radias at this height
        }
        return dist;

    }



#ifdef TEST_CONFIG
#include <iostream>

    friend std::ostream& operator<<(std::ostream& os, const Plane3d& dt) {
        os << dt.mRefPoint << dt.mNormalVector <<mRadias << mTopPoint;
        return os;
    }
#endif


};

