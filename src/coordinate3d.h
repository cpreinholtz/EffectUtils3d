#pragma once



class Coord3d {
public:
    float x;
    float y;
    float z;


    //**************************************************************
    // Constructors
    //**************************************************************
    //default
    Coord3d() {
        set(0, 0, 0);
    }

    Coord3d(float xx, float yy, float zz) {
        set(xx, yy, zz);
    }



    //**************************************************************
    // setters
    //**************************************************************
    //set by passing in x, y, and z
    void set(float xx, float yy, float zz) {
        x = xx;
        y = yy;
        z = zz;
    }

    //unecisary

    //set by passing in an existing coordinate object
    //void set(Coord3d setTo){
    //    x=setTo.x;
    //    y=setTo.y;
    //    z=setTo.z;
    //}




    //**************************************************************
    // Misc
    //**************************************************************
#ifdef TEST_CONFIG
#include <iostream>

    friend ostream& operator<<(ostream& os, const Coord3d& dt) {
        os << "(" << dt.x << "," << dt.y << "," << dt.z << ")";
        return os;
    }
#endif
    /*
    Coord3d operator + (Coord3d const &setTo){
        Coord3d res;
        res.x = x+setTo.x;
        res.y = x+setTo.y;
        res.z = x+setTo.z;
        return res
    }*/

};

