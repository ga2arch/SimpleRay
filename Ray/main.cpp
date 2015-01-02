//
//  main.cpp
//  Ray
//
//  Created by Gabriele Carrettoni on 01/01/15.
//  Copyright (c) 2015 Gabriele Carrettoni. All rights reserved.
//

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/type_ptr.hpp>

using Vec = glm::dvec3;

float radians (float d) {
    return static_cast<float>(d * M_PI / 180);
}

inline float clamp(float x, float a, float b) {
    return x < a ? a : (x > b ? b : x);
}

inline bool quadratic(float A, float B, float C, float* t0, float* t1) {
    float d = B * B - 4.f * A * C;
    if (d <= 0) return false;
    
    float r_d = sqrtf(d);
    float q;
    
    if (B < 0) q = -.5f * (B - r_d);
    else       q = -.5f * (B + r_d);
    
    *t0 = q / A;
    *t1 = C / q;
    
    if (*t0 > *t1) std::swap(*t0, *t1);
    return true;
}

struct Ray {
    Vec o, d;
    
    Ray(Vec &o_, Vec &d_): o(o_), d(d_) {}
};

enum Refl_t { DIFF, SPEC, REFR };

struct Sphere {
    double radius;
    Vec position, emission, color;
    Refl_t refl;
    
    Sphere(double rad, Vec p, Vec e, Vec c, Refl_t r)
    : radius(rad), position(p), emission(e), color(c), refl(r) {};
    
    double intersect(const Ray &ray) const {
        float A = powf(ray.d.x, 2) + powf(ray.d.y, 2) + powf(ray.d.z, 2);
        float B = 2 * (ray.d.x*ray.o.x + ray.d.y*ray.o.y + ray.d.z*ray.o.z);
        float C = powf(ray.o.x, 2) + powf(ray.o.y, 2) + powf(ray.o.z, 2) - powf(radius, 2);
        
        float t0, t1;
        if (!quadratic(A, B, C, &t0, &t1))
            return false;
        
        return t0;
    };
};

Sphere spheres[] = {//Scene: radius, position, emission, color, material
    Sphere(1e5, Vec( 1e5+1,40.8,81.6), Vec(),Vec(.75,.25,.25),DIFF),//Left
    Sphere(1e5, Vec(-1e5+99,40.8,81.6),Vec(),Vec(.25,.25,.75),DIFF),//Rght
    Sphere(1e5, Vec(50,40.8, 1e5),     Vec(),Vec(.75,.75,.75),DIFF),//Back
    Sphere(1e5, Vec(50,40.8,-1e5+170), Vec(),Vec(),           DIFF),//Frnt
    Sphere(1e5, Vec(50, 1e5, 81.6),    Vec(),Vec(.75,.75,.75),DIFF),//Botm
    Sphere(1e5, Vec(50,-1e5+81.6,81.6),Vec(),Vec(.75,.75,.75),DIFF),//Top
    Sphere(16.5,Vec(27,16.5,47),       Vec(),Vec(1,1,1)*.999, SPEC),//Mirr
    Sphere(16.5,Vec(73,16.5,78),       Vec(),Vec(1,1,1)*.999, REFR),//Glas
    Sphere(600, Vec(50,681.6-.27,81.6),Vec(12,12,12),  Vec(), DIFF) //Lite
};

inline bool intersect(const Ray &ray, double &t, double &id) {
    double num = sizeof(spheres) / sizeof(Sphere);
    double distance;
    double inf = t = 1e20;
    
    for (int i=int(num); i != 0; i--) {
        if ((distance = spheres[i].intersect(ray)) && distance < t) {
            t = distance;
            id = i;
        }
    }
    
    return t < inf;
}



int main(int argc, const char * argv[]) {
    
    
}
