#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"

class sphere: public hitable
{
public:
    sphere() {}
    sphere(vec3 center_, float radius_, material *m): center(center_), radius(radius_), mat_ptr(m) {}
    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const;

private:
    vec3 center;
    float radius;
    material *mat_ptr;
};

bool sphere::hit(const ray &r, float t_min, float t_max, hit_record &rec) const
{
    vec3 oc = r.origin() - center;
    float a = r.direction().dot(r.direction());
    float b = 2.0*oc.dot(r.direction());
    float c = oc.dot(oc) - radius*radius;
    float discriminant = b*b - 4*a*c;
    if(discriminant > 0)
    {
        float temp = (-b - sqrt(discriminant)) / (2.0*a);
        if(temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }
        temp = (-b + sqrt(discriminant)) / (2.0*a);
        if(temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }
        return false;
    }
    return false;
}

#endif // SPHEREH