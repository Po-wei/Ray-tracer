#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable
{
public:
    sphere();
    sphere(point3 p, double r, shared_ptr<material> m);
    virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;

private:
    point3 center;
    double radius;
    shared_ptr<material> mat_ptr;
};

sphere::sphere()
{
}

sphere::sphere(point3 p, double r, shared_ptr<material> m)
    : center(p), radius(r), mat_ptr(m)
{
}

bool sphere::hit(const ray &r, double t_min, double t_max, hit_record &rec) const
{
    vec3 oc = r.origin() - this->center;
    double a = dot(r.direction(), r.direction());
    double half_b = dot(oc, r.direction());
    double c = dot(oc, oc) - radius * radius;
    double discriminant = half_b * half_b - a * c;

    if (discriminant > 0)
    {
        double t = (-half_b - std::sqrt(discriminant)) / a;
        if (t > t_min && t < t_max)
        {
            rec.t = t;
            rec.p = r.at(t);
            vec3 outward_normal = (rec.p - this->center) / this->radius;
            rec.set_face_normal(r, outward_normal);
            rec.mat_ptr = mat_ptr;
            return true;
        }
    }
    return false;
}

#endif