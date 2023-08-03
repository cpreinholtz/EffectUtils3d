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
        setRefpoint(refPoint);
        setNormal(normalVector);
    }


    void setNormal(float x, float y, float z){
      Vector3d normalVector(x, y, z);
      setNormal(normalVector);
    }

    void setNormal(Vector3d normalVector) {
        mNormalVector = normalVector;
        mNormalVector.constrianNonZero();
        mNormalVector.makeUnitVector();
    }

    void setRefpoint(float x, float y, float z){
      Vector3d refPoint(x, y, z);
      setRefpoint(refPoint);
    }
    void setRefpoint(Vector3d refPoint){
      mRefPoint = refPoint;
    }



    //**************************************************************
    // actions (Rotations about the three Axis)
    //**************************************************************
    //these are assuming +x is right, +y is back (further) and +z is up
    //https://stackoverflow.com/questions/14607640/rotating-a-vector-in-3d-space
    
    //rotate around the Z axis given theta in radians (+ is CW right, - is CCW left)
    void yaw(float theta) {
        mNormalVector.yaw(theta);
    }

    //rotate around x axis given theta in radians (+theta looks down(rotates forward for CW from + axis))
    void pitch(float theta) {
        mNormalVector.pitch(theta);
    }

    //rotate around Y axis given theta in radians(+theta rolls left, (left wing down is CW))
    void roll(float theta) {
        mNormalVector.roll(theta);
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


class AnimatedObject {
public: 


    const float kFramePeriodSeconds = 1/60.0;   //one frame period for all animated objs //might want to make this static but that would require modifying the initializer
    float mAnimationTimeSeconds;//total time for this "effect"
    bool mActive;

    int mCurrentStep;
    int mTotalSteps;

    //**************************************************************
    // Constructors
    //**************************************************************
    AnimatedObject() {
        mAnimationTimeSeconds = 0.0;
        mActive = false;
    }
    //**************************************************************
    // Actions
    //**************************************************************
    // Pure Virtual Functions
    virtual void prepare(float seconds) = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
virtual void step() = 0;
virtual void endOfAnimationCleanup() = 0;

//check current step vs total steps to see if animation is finised
bool checkIfDone() {
    if (mTotalSteps <= 0) {
        return false;
    }
    else if (mCurrentStep < mTotalSteps) {
        return false;
    }
    else {
        return true;
    }
}

//increment Step counter, then 
void endOfStepCleanup() {
    mCurrentStep = mCurrentStep + 1;
    if (checkIfDone()) {
        endOfAnimationCleanup();
        mActive = false;
    }
}



};



class AnimatedPlane3d :AnimatedObject {

    //the plane will be described using the point normal method (a reference point on the plane and a non-zero vector orthogonal to the plane)
    Plane3d mPlane;

    //the user describes the FINAL plane position
    Plane3d mDesiredPlane;

    enum eTranslationMode
    {
        TRANSLATE_LINEAR,
        TRANSLATE_PROPORTIONAL,
    };
    eTranslationMode mTranslationMode;

    //**************************************************************
    // Constructors
    //**************************************************************



    //**************************************************************
    // Setters
    //**************************************************************


    //**************************************************************
    // getters
    //**************************************************************

    //**************************************************************
    // Animations
    //**************************************************************
    //flip / strobe normal vector



    //translate ref point
    void setTranslation(Vector3d endPoint, eTranslationMode mode = TRANSLATE_LINEAR) {
        mTranslationMode = mode;
        mDesiredPlane.mRefPoint = endPoint;
    }



    // rotate ref point

    //translate normal vector

    // rotate normal vector


    //**************************************************************
    // Actions
    //**************************************************************
    void prepare(float seconds) {
        mTotalSteps = (int)round(seconds / kFramePeriodSeconds);
        mDesiredPlane = mPlane;
        //mCurrentStep = 1;
    }

    void start() {
        mActive = true;
        mCurrentStep = 0;
    }
    void stop() {
        mActive = false;
    }
    void step() {
        if (mActive == true) {
            //Do something HERE TODO

            if (mTranslationMode == TRANSLATE_LINEAR){
                //Vector3d detlaRef = (mDesiredPlane.mRefPoint - mPlane.mRefPoint) / (mTotalSteps - mCurrentStep);
            }
            else if (mTranslationMode == TRANSLATE_PROPORTIONAL) {
                //int stepsLeft = mTotalSteps - mCurrentStep;
                //float stepRatio = (stepsLeft / mTotalSteps ); // the more steps left to do, the "faster" this animation will run                
                //Vector3d detlaRef = (mDesiredPlane.mRefPoint - mPlane.mRefPoint) * 0.1 / mTotalSteps;
            }
            endOfStepCleanup();
        }
    }

    void endOfAnimationCleanup() {
        //TODO
        mPlane = mDesiredPlane;
    }
};


