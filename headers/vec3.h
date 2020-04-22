#ifndef VEC3H
#define VEC3H

#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

class vec3
{
public:
    vec3() {}
    vec3(float e0, float e1, float e2) { e[0] = e0; e[1] = e1; e[2] = e2; }
    inline float x() const { return e[0]; }
    inline float y() const { return e[1]; }
    inline float z() const { return e[2]; }
    inline float r() const { return e[0]; }
    inline float g() const { return e[1]; }
    inline float b() const { return e[2]; }

    inline const vec3& operator+ () const { return *this; }
    inline vec3 operator- () const { return vec3(-e[0], -e[1], -e[2]); }
    inline float operator[] (int i) const { return e[i]; }
    inline float& operator[](int i) { return e[i]; }

    inline vec3 operator+ (const vec3 &v2) const { return vec3(e[0] + v2.e[0], e[1] + v2.e[1], e[2] + v2.e[2]); }
    inline vec3 operator- (const vec3 &v2) const { return vec3(e[0] - v2.e[0], e[1] - v2.e[1], e[2] - v2.e[2]); }
    inline vec3 operator* (const vec3 &v2) const { return vec3(e[0] * v2.e[0], e[1] * v2.e[1], e[2] * v2.e[2]); }
    inline vec3 operator/ (const vec3 &v2) const { return vec3(e[0] / v2.e[0], e[1] / v2.e[1], e[2] / v2.e[2]); }
    inline vec3 operator* (float t) const { return vec3(e[0]*t, e[1]*t, e[2]*t); }
    inline friend vec3 operator* (float t, const vec3 &v) { return vec3(v.e[0]*t, v.e[1]*t, v.e[2]*t); }
    inline vec3 operator/ (float t) const { return vec3(e[0]/t, e[1]/t, e[2]/t); }
    inline vec3& operator+= (const vec3 &v2);
    inline vec3& operator-= (const vec3 &v2);
    inline vec3& operator*= (const vec3 &v2);
    inline vec3& operator/= (const vec3 &v2);
    inline vec3& operator*= (const float t);
    inline vec3& operator/= (const float t);

    inline float dot(const vec3 &v2) const;
    inline vec3 cross(const vec3 &v2) const;

    inline float length() const { return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]); }
    inline float squared_length() const { return e[0]*e[0] + e[1]*e[1] + e[2]*e[2]; }
    inline void make_unit_vector();
    inline vec3 unit_vector() const { return vec3(e[0] / this->length(), e[1] / this->length(), e[2] / this->length()); }

    inline friend istream& operator>> (istream &is, vec3 &t);
    inline friend ostream& operator<< (ostream &os, const vec3 &t);

private:
    float e[3];
};

inline vec3& vec3::operator+= (const vec3 &v2)
{
    e[0] += v2.e[0];
    e[1] += v2.e[1];
    e[2] += v2.e[2];
    return *this;
}

inline vec3& vec3::operator-= (const vec3 &v2)
{
    e[0] -= v2.e[0];
    e[1] -= v2.e[1];
    e[2] -= v2.e[2];
    return *this;
}

inline vec3& vec3::operator*= (const vec3 &v2)
{
    e[0] *= v2.e[0];
    e[1] *= v2.e[1];
    e[2] *= v2.e[2];
    return *this;
}

inline vec3& vec3::operator/= (const vec3 &v2)
{
    e[0] /= v2.e[0];
    e[1] /= v2.e[1];
    e[2] /= v2.e[2];
    return *this;
}

inline vec3& vec3::operator*= (const float t)
{
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}

inline vec3& vec3::operator/= (const float t)
{
    e[0] /= t;
    e[1] /= t;
    e[2] /= t;
    return *this;
}

inline float vec3::dot(const vec3 &v2) const
{
    return e[0] * v2.e[0] + e[1] * v2.e[1] + e[2] * v2.e[2];
}

inline vec3 vec3::cross(const vec3 &v2) const
{
    return vec3( (e[1]*v2.e[2] - e[2]*v2.e[1]),
                 (-(e[0]*v2.e[2] - e[2]*v2.e[0])),
                 (e[0]*v2.e[1] - e[1]*v2.e[0]));
}

inline void vec3::make_unit_vector()
{
    e[0] = e[0] / this->length();
    e[1] = e[1] / this->length();
    e[2] = e[2] / this->length();
}

inline istream& operator>> (istream &is, vec3 &t)
{
    is >> t.e[0] >> t.e[1] >> t.e[2];
    return is;
}

inline ostream& operator<< (ostream &os, const vec3 &t)
{
    os << t.e[0] << " " << t.e[1] << " " << t.e[2];
    return os;
}

#endif // VEC3H
