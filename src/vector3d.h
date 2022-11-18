#pragma once
#include <tools3d.h>




class Vector3d {
public:
    //**************************************************************
    // Members
    //**************************************************************
    float mX;//magnitude of the x component
    float mY;//magnitude of the y component
    float mZ;//magnitude of the z component


    //**************************************************************
    // Constructors
    //**************************************************************
    //default constructor
    Vector3d() {
        set(0, 0, 0);
    }

    //overloaded constructor
    Vector3d(float x, float y, float z) {
        set(x, y, z);
    }


    //**************************************************************
    // setters
    //**************************************************************

    void set(float x, float y, float z) {
        mX = x;
        mY = y;
        mZ = z;
    }


    //**************************************************************
    // getters
    //**************************************************************
    float length() const {
        //(mX^2) + (mY^2) + (mZ^2) ) ^ 0.5 );
        //float res = pow(pow(mX, 2) + pow(mY, 2) + pow(mZ, 2), 0.5);
        return sqrt(mX * mX + mY * mY + mZ * mZ);
    }


    //**************************************************************
    // actions (Cross and dot product)
    //**************************************************************
    
    //a DOT b = a1b1 + a2b2 + a3b3
    float dot(Vector3d rhs) const {
        return (mX * rhs.mX) + (mY * rhs.mY) + (mZ * rhs.mZ);
    }

    //The result is a 3D vector with the following length and orientation:
    //Length: | u x v | = | u | | v | sin theta, where theta, is the angle between uand v.
    //Orientation : u x v is perpendicular to both uand v.
    //u x v   =   ( uj vk - uk vj ,   uk vi - ui vk ,   ui vj - uj vi )T.
    Vector3d cross(Vector3d rhs) const {
        Vector3d result(mY * rhs.mZ - mZ * rhs.mY, mZ * rhs.mX - mX * rhs.mZ, mX * rhs.mY - mY * rhs.mX);
        return result;
    }

    //**************************************************************
    // actions (Operator overloads)
    //**************************************************************

    //overloaded division   (Vector3d / scaler)
    Vector3d operator / (float rhs) const {
        //create a new vector by dividing the individual components of this vector by a scaler
        Vector3d res(mX / rhs, mY / rhs, mZ / rhs);
        return res;
    }

    //overloaded mult   (Vector3d * scaler)
    Vector3d operator * (float rhs) const {
        //create a new vector by multiplying the individual components of this vector by a scaler
        Vector3d res(mX * rhs, mY * rhs, mZ * rhs);
        return res;
    }

    //(Vector3d+ Vector3d)
    Vector3d operator + (Vector3d rhs) const {
        //create a new vector by multiplying the individual components of this vector by a scaler
        Vector3d res(mX + rhs.mX, mY + rhs.mY, mZ + rhs.mZ);
        return res;
    }

    //Vector3d- Vector3d
    Vector3d operator - (Vector3d rhs) const {
        //create a new vector by multiplying the individual components of this vector by a scaler
        Vector3d res(mX - rhs.mX, mY - rhs.mY, mZ - rhs.mZ);
        return res;
    }

    //  (Vector3d- Vector3d).length
    float distance(Vector3d rhs) const {
        rhs = (*this) - rhs;
        return rhs.length();
    }

    //**************************************************************
    // actions (Rotations about the three Axis)
    //**************************************************************
    //these are assuming +x is right, +y is back (further) and +z is up
    //https://stackoverflow.com/questions/14607640/rotating-a-vector-in-3d-space
    
    //rotate around the Z axis given theta in radians (+ is CW right, - is CCW left)
    void yaw(float theta) {
        set(mX * cos(theta) - mY * sin(theta), mX * sin(theta) + mY * cos(theta), mZ);
    }

    //rotate around x axis given theta in radians (+theta looks down(rotates forward for CW from + axis))
    void pitch(float theta) {
        set(mX * cos(theta) + mZ * sin(theta), mY, -mX * sin(theta) + mZ * cos(theta));
    }

    //rotate around Y axis given theta in radians(+theta rolls left, (left wing down is CW))
    void roll(float theta) {
        set(mX, mY * cos(theta) - mZ * sin(theta), mY*sin(theta) + mZ * cos(theta)) ;
    }

    //**************************************************************
    // Actions MISC
    //**************************************************************
    void constrianNonZero() {
        if (mX == 0 and mY == 0 and mZ == 0) {
            set(1, 0, 0);
        }
    }

    //take the internal Normal Vector3d member and convert it to a unit vector
    void makeUnitVector() {
        //ensure we dont divide by zero...  This is handled in the set function
        constrianNonZero();
        //"this" is just a pointer to this particular instance of vector
        //using (*this) is just derefencing this pointer 
        //making an easy way to access this instance direclty
        (*this) = (*this) / length();  //divide x y and z componets by the length
    }


#ifdef TEST_CONFIG
#include <iostream>

    friend std::ostream& operator<<(std::ostream& os, const Vector3d& dt) {
        os << "<" << dt.mX << "," << dt.mY << "," << dt.mZ << ">";
        return os;
    }
#endif

};



