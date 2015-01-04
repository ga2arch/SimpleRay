#include <cmath>
#include <cstdio>

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

inline bool quadratic(double A, double B, double C, double* t0, double* t1) {
    double d = B * B - 4.0 * A * C;
    if (d <= 0) return false;
    
    double r_d = sqrt(d);
    double q;
    
    if (B < 0) q = -.5f * (B - r_d);
    else       q = -.5f * (B + r_d);
    
    *t0 = q / A;
    *t1 = C / q;
    
    if (*t0 > *t1) std::swap(*t0, *t1);
    return true;
}

inline double clamp(double x, double a=0, double b=1) {
    return x < a ? a : (x > b ? b : x);
}

// SHAPES

struct Sphere {
    double rad;
    Vec pos, emission, color;
    
    Sphere(Vec p, Vec e, Vec c, double r): pos(p), emission(e), color(c), rad(r) {}
    
    double intersect(const Ray &ray, double *t) {
        auto A = dot(ray.d, ray.d);
        auto B = 2 * dot(ray.d, ray.o);
        auto C = dot(ray.o, ray.o) - rad*rad;
        
        double t0, t1;
        if (!quadratic(A, B, C, &t0, &t1))
            return false;
        
        *t = t0;
        return true;
    }
};

inline int to_int(double f) {
    return clamp(f) * 255;
}

int main() {
    int w = 800, h = 600;
    
    Ray cam(Vec(0, 0, -3), norm(Vec(0,0,0)));
    Vec *c = new Vec[w*h];
    
    Sphere s(Vec(0,2,0), Vec(), Vec(.6, 0, .2), 1);
    
    for(int y=0; y < h; y++) {
        for (int x=0; x < w; x++) {
            int i = (h-y-1)*w+x;
            
            auto fovDist = .557;
            auto xx = (2 * ((x + 0.5) * 1.0/w) - 1) * fovDist * w/h;
            auto yy = (1 - 2 * ((y + 0.5) * 1.0/h)) * fovDist;
            
            Ray r(cam.o, norm(Vec(xx,yy,-1)));
            
            double t;
            if (s.intersect(r, &t) && t <= 1000)
                c[i] = s.color;
            else
                c[i] = Vec();
        }
    }
    
    FILE *f = fopen("image.ppm", "w");         // Write image to PPM file.
    fprintf(f, "P3\n%d %d\n%d\n", w, h, 255);
    for (int i=0; i<w*h; i++)
        fprintf(f,"%d %d %d ", to_int(c[i].x), to_int(c[i].y), to_int(c[i].z));
}


