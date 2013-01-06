#ifndef JAZLIB_VEC2_HPP
#define JAZLIB_VEC2_HPP

#include <iostream>
#include <cmath>

using namespace std;

template <class T>
struct vec2
{
    friend ostream& operator<<(ostream &out, const vec2<T> &v) {
        out << '<' << v.x << ',' << v.y << '>';
        return out;
    }
    
    union {
        struct { T x, y; };
        T v[2];
    };
    
                vec2() : x(0), y(0) { }
                vec2(T x_, T y_) : x(x_), y(y_) { }
    
                operator T*() { return v; }
                
    T&          operator[](unsigned int i) { return v[i]; }
    const T&    operator[](unsigned int i) const { return v[i]; }
    
    bool        operator==(const vec2<T> &rhs) const { return x == rhs.x && y == rhs.y; }
    bool        operator!=(const vec2<T> &rhs) const { return x != rhs.x || y != rhs.y; }

    vec2<T>     operator+(const vec2<T> &rhs) const { return vec2<T>(x + rhs.x, y + rhs.y); }
    vec2<T>     operator-(const vec2<T> &rhs) const { return vec2<T>(x - rhs.x, y - rhs.y); }
    vec2<T>     operator*(const T &rhs) const { return vec2<T>(x * rhs, y * rhs); }
    vec2<T>     operator/(const T &rhs) const { return vec2<T>(x / rhs, y / rhs); }
    
    vec2<T>&    operator+=(const vec2<T> &rhs) { x += rhs.x; y += rhs.y; return *this; }
    vec2<T>&    operator-=(const vec2<T> &rhs) { x -= rhs.x; y -= rhs.y; return *this; }
    vec2<T>&    operator*=(const T &rhs) { x *= rhs; y *= rhs; return *this; }
    vec2<T>&    operator/=(const T &rhs) { x /= rhs; y /= rhs; return *this; }

    bool        zero() const { return x == 0 && y == 0; }

    T           magnitude() const
                {
                    return sqrt((T) (x * x + y * y));
                }
                
    T           magnitude_sq() const
                {
                    return x * x + y * y;
                }

    vec2<T>     normalised() const
                {
                    T m = magnitude();
                    return vec2<T>(x / m, y / m);
                }
    
    vec2<T>     limited_to(T max) const
                {
                    T m = magnitude();
                    if (m > max) {
                        T div = m / max;
                        return vec2<T>(x / div, y / div);
                    } else {
                        return *this; 
                    }
                }

    T           distance(const vec2<T> &rhs) const
                {
                    return sqrt(
                        (T) ((rhs.x - x) * (rhs.x - x)
                            + (rhs.y - y) * (rhs.y - y))
                    );
                }

    T           dot(const vec2<T> &rhs) const
                {
                    return x * rhs.x + y * rhs.y;
                }
    
};

typedef vec2<float>     vec2f;
typedef vec2<double>    vec2d;

#endif