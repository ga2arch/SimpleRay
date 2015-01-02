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

int main(int argc, const char * argv[]) {
    
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
        
        double intersect(const Ray &r) const {
            
        }
    };
    
    
}
