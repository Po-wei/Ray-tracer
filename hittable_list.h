#ifndef HITTABLE_LIST
#define HITTABLE_LIST

#include "hittable.h"
#include <memory>
#include <vector>

using std::make_shared;
using std::shared_ptr;

class hittable_list : public hittable
{
public:
    hittable_list();
    hittable_list(shared_ptr<hittable> object);
    void add(shared_ptr<hittable> object);
    void clear();

    virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;

private:
    std::vector<shared_ptr<hittable>> objects;
};

hittable_list::hittable_list()
{
}

hittable_list::hittable_list(shared_ptr<hittable> object)
{
    add(object);
}

void hittable_list::add(shared_ptr<hittable> object)
{
    objects.push_back(object);
}

void hittable_list::clear()
{
    objects.clear();
}

bool hittable_list::hit(const ray &r, double t_min, double t_max, hit_record &rec) const
{
    hit_record temp;
    bool hit_anthing = false;
    double closet_so_far = t_max;

    for (const auto &obj : objects)
    {
        if (obj->hit(r, t_min, closet_so_far, temp))
        {
            closet_so_far = temp.t;
            hit_anthing = true;
            rec = temp;
        }
    }
    return hit_anthing;
}

#endif