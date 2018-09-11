//
//  Math_Util.hpp
//  Informatik
//
//  Created by Aaron Hodel on 04.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef Math_Util_hpp
#define Math_Util_hpp

#include <cmath>

#define PI 3.1415926535897932384626

#define TO_DEG(rad) (rad/PI*180.0)
#define TO_RAD(deg) (deg*PI/180.0)

#define SIGN(x) (x<0?-1:1)

// The length of the position vector (x|y)
#define LENGTH(x, y) sqrt((x) * (x) + (y) * (y))

typedef struct vector2d
{
    float x, y;
    
    inline void operator -= (vector2d other) {x -= other.x; y -= other.y;}
    inline void operator += (vector2d other) {x += other.x; y += other.y;}
    
    inline void operator *= (float a) {x *= a; y *= a;}
    inline vector2d operator * (float a) { return {x * a, y * a}; }
    
    inline float len() { return sqrt(x * x + y * y); }
    inline vector2d norm() { return {x / len(), y / len()}; }
    inline float dir() { return atan2(y, x); }
} vector2d;

#endif /* Math_Util_hpp */
