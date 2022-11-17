#include <coordinate3d.h>

#pragma once

#define PI 3.14159265359

float degToRad(float deg) {
    return deg * PI / 180;
}
float radToDeg(float rad) {
    return rad * 180 / PI;
}

class Vector {
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
    Vector() {
        set(0, 0, 0);
    }

    //overloaded constructor
    Vector(Coord3d components) {
        set(components);
    }

    //overloaded constructor
    Vector(float x, float y, float z) {
        set(x, y, z);
    }


    //**************************************************************
    // actions
    //**************************************************************

    //overloaded division   (Vector / scaler)
    Vector operator / (float rhs) {
        //create a new vector by dividing the individual components of this vector by a scaler
        Vector res(mX / rhs, mY / rhs, mZ / rhs);
        return res;
    }

    //overloaded mult   (Vector * scaler)
    Vector operator * (float rhs) {
        //create a new vector by multiplying the individual components of this vector by a scaler
        Vector res(mX * rhs, mY * rhs, mZ * rhs);
        return res;
    }

    //(Vector+ Vector)
    Vector operator + (Vector rhs) {
        //create a new vector by multiplying the individual components of this vector by a scaler
        Vector res(mX + rhs.mX, mY + rhs.mY, mZ + rhs.mZ);
        return res;
    }

    //Vector- Vector
    Vector operator - (Vector rhs) {
        //create a new vector by multiplying the individual components of this vector by a scaler
        Vector res(mX - rhs.mX, mY - rhs.mY, mZ - rhs.mZ);
        return res;
    }


    //these are assuming +x is right, +y is back (further) and +z is up
    // 
    // 
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
    // setters
    //**************************************************************
    void set(Coord3d components) {
        set(components.x, components.y, components.z);
    }


    void set(float x, float y, float z) {
        mX = x;
        mY = y;
        mZ = z;
    }


    //**************************************************************
    // getters
    //**************************************************************
    float getLength() const {
        //(mX^2) + (mY^2) + (mZ^2) ) ^ 0.5 );
        //float res = pow(pow(mX, 2) + pow(mY, 2) + pow(mZ, 2), 0.5);
        return sqrt(mX*mX + mY*mY +mZ*mZ);
    }

    Coord3d getComponents() const {
        Coord3d components(mX, mY, mZ);
        return components;
    }



    //**************************************************************
    // MISC
    //**************************************************************
#ifdef TEST_CONFIG
#include <iostream>

    friend ostream& operator<<(ostream& os, const Vector& dt) {
        os << "<" << dt.mX << "," << dt.mY << "," << dt.mZ << ">";
        return os;
    }
#endif

};



