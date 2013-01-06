#ifndef JAZLIB_VEC3_HPP
#define JAZLIB_VEC3_HPP

#include <iostream>
#include <cmath>

using namespace std;

template <class T>
struct vec3
{
    friend ostream& operator<<(ostream &out, const vec3<T> &v) {
        out << '<' << v.x << ',' << v.y << ',' << v.z << '>';
        return out;
    }
    
    union {
        struct { T x, y, z; };
        T v[3];
    };
    
                vec3() : x(0), y(0), z(0) { }
                vec3(T x_, T y_, T z_) : x(x_), y(y_), z(z_) { }
    
                operator T*() { return v; }
                
    T&          operator[](unsigned int i) { return v[i]; }
    const T&    operator[](unsigned int i) const { return v[i]; }
    
    bool        operator==(const vec3<T> &rhs) const { return x == rhs.x && y == rhs.y && z == rhs.z; }
    bool        operator!=(const vec3<T> &rhs) const { return x != rhs.x || y != rhs.y || z != rhs.z; }

    vec3<T>     operator+(const vec3<T> &rhs) const { return vec3<T>(x + rhs.x, y + rhs.y, z + rhs.z); }
    vec3<T>     operator-(const vec3<T> &rhs) const { return vec3<T>(x - rhs.x, y - rhs.y, z - rhs.z); }
    vec3<T>     operator*(const T &rhs) const { return vec3<T>(x * rhs, y * rhs, z * rhs); }
    vec3<T>     operator/(const T &rhs) const { return vec3<T>(x / rhs, y / rhs, z / rhs); }
    
    vec3<T>&    operator+=(const vec3<T> &rhs) { x += rhs.x; y += rhs.y; z+= rhs.z; return *this; }
    vec3<T>&    operator-=(const vec3<T> &rhs) { x -= rhs.x; y -= rhs.y; z-= rhs.z; return *this; }
    vec3<T>&    operator*=(const T &rhs) { x *= rhs; y *= rhs; z *= rhs; return *this; }
    vec3<T>&    operator/=(const T &rhs) { x /= rhs; y /= rhs; z /= rhs; return *this; }

    bool        zero() const { return x == 0 && y == 0 && z == 0; }

    T           magnitude() const
                {
                    return sqrt((T) (x * x + y * y + z * z));
                }
                
    T           magnitude_sq() const
                {
                    return x * x + y * y + z * z;
                }

    vec3<T>     normalised() const
                {
                    T m = magnitude();
                    return vec3<T>(x / m, y / m, z / m);
                }
    
    vec3<T>     limited_to(T max) const
                {
                    T m = magnitude();
                    if (m > max) {
                        T div = m / max;
                        return vec3<T>(x / div, y / div, z / div);
                    } else {
                        return *this; 
                    }
                }

    T           distance(const vec3<T> &rhs) const
                {
                    return sqrt(
                        (T) ((rhs.x - x) * (rhs.x - x)
                            + (rhs.y - y) * (rhs.y - y)
                            + (rhs.z - z) * (rhs.z - z))
                    );
                }

    T           dot(const vec3<T> &rhs) const
                {
                    return x * rhs.x + y * rhs.y + z * rhs.z;
                }
    
    vec3<T>     cross(const vec3<T> &rhs) const
                {
                    return vec3<T>(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
                }
    
};

typedef vec3<float>     vec3f;
typedef vec3<double>    vec3d;

#endif