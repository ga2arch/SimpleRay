#include <cmath>

// MATH
struct Vec {
    double x, y, z;
    
    Vec(double x_=0, double y_=0, double z_=0): x(x_), y(y_), z(z_) {}
    
    Vec operator+(const Vec &v) const {
        return Vec(x + v.x,
                   y + v.y,
                   z + v.z);
    }
    
    Vec operator-(const Vec &v) const {
        return Vec(x - v.x,
                   y - v.y,
                   z - v.z);
    }
    
    Vec operator*(const Vec &v) const {
        return Vec(x * v.x,
                   y * v.y,
                   z * v.z);
    }
    
    Vec operator/(const Vec &v) const {
        return Vec(x / v.x,
                   y / v.y,
                   z / v.z);
    }
};

inline double dot(const Vec &v1, const Vec &v2)  {
    return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

inline Vec cross(const Vec &v1, const Vec &v2) {
    return Vec(v1.y*v2.z - v1.z*v2.y,
               v1.z*v2.x - v1.x*v2.z,
               v1.x*v2.y - v1.y*v2.x);
}

inline double length(const Vec &v) {
    return sqrt(dot(v, v));
}

inline Vec norm(const Vec &v) {
    auto l = length(v);
    return v / Vec(l, l, l);
}

struct Ray {
    Vec o, d;
    
    Ray(Vec o_, Vec d_): o(o_), d(d_) {};
};

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

// SHAPES

struct Sphere {
    double rad;
    Vec pos, emission, color;
    
    Sphere(Vec p, Vec e, Vec c, double r): pos(p), emission(e), color(c), rad(r) {}
    
    bool intersect(const Ray &ray, float *pos) {
        float A = powf(ray.d.x, 2) + powf(ray.d.y, 2) + powf(ray.d.z, 2);
        float B = 2 * (ray.d.x*ray.o.x + ray.d.y*ray.o.y + ray.d.z*ray.o.z);
        float C = powf(ray.o.x, 2) + powf(ray.o.y, 2) + powf(ray.o.z, 2) - powf(rad, 2);
        
        float t0, t1;
        if (!quadratic(A, B, C, &t0, &t1))
            return false;
        
        *pos = t0;
        return true;
    }
};


int main() {
    int w = 800, h = 600;
    
    
    
}


