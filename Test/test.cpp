#include <cstdint>
#include <iostream>
using namespace std;

typedef uint8_t byte;
float constrain(float f1, float min, float max) {
    if (f1 < min) return min;
    else if (f1 < max) return max;
    else return f1;
}


#define TEST_CONFIG 1


//include direcories

/*
C:\Users\clark\Documents\Arduino\libraries\EffectUtils3d\src;
C:\Users\clark\Documents\Arduino\libraries\EffectUtils3d\dependencies\ColorUtilsHsi\include;
C:\Users\clark\Documents\Arduino\libraries\EffectUtils3d\test;
C:\Users\clark\Documents\Arduino\libraries\EffectUtils3d\src;C:\Users\clark\Documents\Arduino\libraries\EffectUtils3d\dependencies\ColorUtilsHsi\include;C:\Users\clark\Documents\Arduino\libraries\EffectUtils3d\test;

NOT INCLUDED
C:\Program Files(x86)\Arduino183Teensy153\hardware\tools\avr\lib\gcc\avr\5.4.0\include;
C:\Program Files(x86)\Arduino183Teensy153\hardware\arduino\avr\cores\arduino;
C:\Program Files(x86)\Arduino183Teensy153\hardware\arduino\avr\variants\standard;
C:\Program Files(x86)\Arduino183Teensy153;
*/

#include <plane3d.h>
#include <pixel3d.h>





int run_tests() {

    //**************************************************************
    // Coordinates
    //**************************************************************
    //create 2 objects using both constructors
    Vector3d testCoord(0,0,0);
    Vector3d testCoord2;
    cout << testCoord << testCoord2 << endl;//expect (000)(000)

    //set one using set(x,y,z)
    testCoord.set(1, 2, 3);
    cout << testCoord << testCoord2 << endl;//expect (123)(000)

  
    //set using = operator
    testCoord = testCoord2;
    cout << testCoord << testCoord2 << endl;//expect (123)(123)


    //set one using set(Coord3d), the other with set(x,y,z)
    testCoord.set(7,8,9);    
    testCoord2= testCoord;
    testCoord.set(4, 5, 6);
    cout << testCoord << testCoord2 << endl;//expect (456)(789)

    cout << endl;
    cout << endl;


    //**************************************************************
    // Vectors
    //**************************************************************
    //create 3 objects using all constructors
    Vector3d testVector1;
    Vector3d testVector2(1,2,3);
    Vector3d testVector3(testCoord2);
    cout << testVector1 << testVector2 << testVector3 << endl;//expect (000)(123)(789)


    //operator overloads
    testVector1 = testVector2;
    testVector2 = testVector2 * 3 ;
    testVector3 = testVector3 / 2.5;
    cout << testVector1 << testVector2 << testVector3 << endl;//expect (123)(369)(2.8,3.2,3.6)

    cout << testVector1 + testVector2 << testVector3 - testVector1 << endl; //expect (4,8,12)(1.8,1.2,0.6)


    testVector1 = testCoord2;
    testVector2.set(0, 0, 0);
    testVector3.set(-1, 2, -3);
    cout << testVector1 << testVector2 << testVector3 << endl;//expect (789)(000)(-1,2,-3)

    cout << testVector1.length() << endl;  //expect 13.928
    cout << testVector2.length() << endl;  //expect 0
    cout << testVector3.length() << endl;  //expect 3.742

    testVector1.set(0, 0, 1);
    testVector1.roll(PI / 2);//roll left
    cout << testVector1 << endl;  //expect <0,-1,0> //
    testVector1.yaw(PI / 2);//yaw right
    cout << testVector1 << endl;  //expect <1,0,0>
    testVector1.pitch(PI / 2);//pitch down
    cout << testVector1 << endl;  //expect <0,0,1> //got 1


    //**************************************************************
    // Planes
    //**************************************************************
    testCoord2.set(1, -2, 3);
    testVector3.set(-1, 2, -3);
    Plane3d p1;
    Plane3d p2(testCoord2, testVector3);

    cout << p1.getRefPoint() << p1.getNormalVector() << endl; //expect (0,0,0)<1,0,0>
    cout << p2.getRefPoint() << p2.getNormalVector() << endl; //expect (1,-2,3)<-0.267,0.534,-0.802>


    testCoord2.set(0, 2, -156);
    testVector3.set(-0.001, 2, 0);
    p1.set(testCoord2, testVector3);
    cout << p1.getRefPoint() << p1.getNormalVector() << endl; //expect (0,2,-156)<-0.000Something,.9999,0>

    testCoord2.set(0, 2, -156);
    testVector3.set(0.0, 0.0, 0.0);
    p2.set(testCoord2, testVector3);
    cout << p2.getRefPoint() << p2.getNormalVector() << endl; //expect (0,2,-156)<1,0,0>



    //test distance functions
    testCoord2.set(1,2, 3);
    testVector3.set(1, 0, 0);
    p1.set(testCoord2, testVector3);
    cout << p1.getRefPoint() << p1.getNormalVector() << endl; //expect (1,2,3)<1,0,0>
    cout << p1.distance(2,2,3)  << endl; //expect 1
    cout << p1.distance(2, 248, -83) << endl; // xpect 1

    //test distance functions
    testCoord2.set(1, 2, 3);
    testVector3.set(1, 0, 0);
    p1.set(testCoord2, testVector3);
    cout << p1.getRefPoint() << p1.getNormalVector() << endl; //expect (1,2,3)<1,0,0>
    cout << p1.distance(10, 2, 3) << endl; //expect 9
    cout << p1.distance(100, 248, -83) << endl; // xpect 99

    //test distance functions
    testCoord2.set(-1, -1, -1);
    testVector3.set(1, 1, 1);
    p1.set(testCoord2, testVector3);
    cout << p1.distance(0, 0, 0) << endl; //expect 1.732

    testCoord2.set(-1, -1, -1);
    testVector3.set(-1, -1, -1);
    p1.set(testCoord2, testVector3);
    cout << p1.distance(0, 0, 0) << endl; //expect 1.732

    testCoord2.set(1, 1, 1);
    testVector3.set(-1, -1, -1);
    p1.set(testCoord2, testVector3);
    cout << p1.distance(0, 0, 0) << endl; //expect 1.732


    testCoord2.set(10, 10, 10);
    testVector3.set(-99, 1, 1);
    p1.set(testCoord2, testVector3);
    cout << p1.distance(0, 0, 0) << endl; //nearly 10

    cout << "press enter to continue\n";
    while (cin.get() != '\n');
    return 0;


}


const int nPix1d = 2; 
const int nPix = nPix1d * nPix1d * nPix1d;
Pixel3d  testPixels[nPix];





void printAnimation() {

    cout << "*************************************" << endl;
    int index = 0;
    for (int i = 0; i < nPix1d; i++) {
        cout << "X = " << i <<endl;
        cout << "_" <<endl;
        for (int j = 0; j < nPix1d; j++) {
            cout << "y = " << j << " | ";
            for (int k = 0; k < nPix1d; k++, index++) {

                cout << testPixels[index].mColor.h << ",";
            }
            cout << "|" <<endl;
        }
        cout << "_" <<endl << endl ;
    }
    cout << "*************************************" << endl;

}


void testAnimation() {
    int index = 0;
    for (int i = 0; i < nPix1d; i++) {
        for (int j = 0; j < nPix1d; j++) {
            for (int k = 0; k < nPix1d; k++, index++) {
                testPixels[index].mPosition = Vector3d(i, j, k);
            }
        }
    }
    printAnimation();


}



int main(int argc, char **argv){
    cout << "Beggining test sequence\n";
    testAnimation();
    return 0;
    //return run_tests();
}