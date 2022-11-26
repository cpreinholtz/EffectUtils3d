#pragma once

#include <vector3d.h>
#include <ColorUtilsHsi.h>



class Pixel3d{
public:
    //pixel is defined by a color and a 3d position
    hsiF mColor;
    Vector3d mPosition;

    //**************************************************************
    // Constructors
    //**************************************************************
    Pixel3d() {
        hsiF color;
        color.h = 0; color.s = 0; color.i = 0;
        Vector3d position;
        set(color, position);
    }

    //**************************************************************
    // setters
    //**************************************************************
    void set(hsiF color, Vector3d position) {
        mColor = color;
        mPosition = position;
    }

    //**************************************************************
    // getters
    //**************************************************************
    rgbF getRgb() {
        return Hsi2Rgb(mColor);
    }

    //**************************************************************
    // actions
    //**************************************************************
    void tweakHue(float delta) {
        tweak(mColor.h, delta);
    }
    void tweakIntensity(float delta) {
        tweak(mColor.i, delta);
    }
    void tweakSaturation(float delta) {
        tweak(mColor.s, delta);
    }
    //given a value (passed by refenece) tweak it by a certain ammount
    void tweak(float & tweakThis, float delta) {
        tweakThis = tweakThis + delta; //add delta
        tweakThis = constrain(tweakThis, 0.0, 1.0);
    }


    //**************************************************************
    // mixing
    //**************************************************************
    //average hue sat and intensity


    //

#ifdef TEST_CONFIG
#include <iostream>

    friend std::ostream& operator<<(std::ostream& os, const Pixel3d& dt) {
        os <<  "hsi:" <<dt.mColor.h << dt.mColor.s << dt.mColor.i << ", \t\tpotition:"<< dt.mPosition;
        return os;
    }
#endif
};