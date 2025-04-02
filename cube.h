#ifndef CUBE_H
#define CUBE_H

#include "hittable.h"
#include "rtweekend.h"

class cube : public hittable {
  public:
    cube(const point3& center, double side_length) : center(center), half_length(side_length / 2.0) {}

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        point3 min_point = center - vec3(half_length, half_length, half_length);
        point3 max_point = center + vec3(half_length, half_length, half_length);

        double t_min = ray_t.min;
        double t_max = ray_t.max;
        
        vec3 normal;

        for (int a = 0; a < 3; a++) {
            double inv_d = 1.0f / r.direction()[a];
            double t0 = (min_point[a] - r.origin()[a]) * inv_d;
            double t1 = (max_point[a] - r.origin()[a]) * inv_d;

            if (inv_d < 0.0f) {
                std::swap(t0, t1);
            }

            if (t0 > t_min) {
                t_min = t0;
                normal = vec3(0, 0, 0);
                normal[a] = inv_d < 0 ? 1 : -1;
            }

            t_max = std::min(t_max, t1);

            if (t_min > t_max) return false;
        }

        if (!ray_t.surrounds(t_min)) {
            return false;
        }

        rec.t = t_min;
        rec.p = r.at(rec.t);
        rec.set_face_normal(r, normal);
        
        return true;
    }

  private:
    point3 center;
    double half_length;
};

#endif