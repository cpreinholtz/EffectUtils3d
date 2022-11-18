# EffectUtils3d
Open source under the MIT License

A resource for 3d effects usefull for animation and light displays

Inspired by https://github.com/Aerokeith/EffectUtils.git

TODO
### Inputs
- Sound reactivity
- User input
### Effects
- Sparkle
- gradient
- 
### Merging Effects
- Mixing
    - overlay. One layer takes priority over others with configurable opacity
    - addition. Weighted addition
    - modulation. one level modulates another
    -
### Geometry
- vector (can be used as a XYZ coordinate as well)
    - X Y Z components / coordinates
    - length
    - cross and dot prod
    - overloaded + - * / operators  (distance is just -)(translation is just +)
    - roll pitch yaw rotations WRT axis
    - can be made into unit vector
- plane (done)
    - refpoint
    - unit normal line
    - distance
- line (done)
    - refPoint
    - directionVector
    - distance
- sphere (done)
    - center
    - radias
    - is inside
    - distance
- cylinder (done)
    - center line
    - radias
    - distance (negative is inside)
 
- circle ?
    - center (of circle)
    - radias
    - distance
- cone
    - circle (bottom circle)
    - top point
    - normal vector
    - height (distance from center to apex)
    - todo
        - add "plane" for bottom circle, used in distance and determening "height" by distance from top point
- line segment
    - refPoint
    - refPoint2? Length + directionVector?
    - directionVector?
    - distance




- //CONSIDER MAKING A BASE CLASS FOR ALL GEOMETRIC OBJS AND PLACING THIS IN THERE
    //overload distance function for dicrete coordinates
    float getDistance(float x, float y, float z) {
        Vector c(x, y, z);
        return getDistance(c);
    }


Making visial studio project
- make new project I suggest placing in VS folder
- header files> add existing > src/\*.h
- source files> add existing > test/test.cpp
- right click project in solution explorer > properties > c/c++ > general > additional include dirs> add /src/
