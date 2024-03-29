#include <iostream>
#include <fstream>
#include <cmath>
#include <cfloat>
#include <cstdlib>
#include <ctime>

#include "vec3.h"
#include "ray.h"
#include "hitable.h"
#include "hitable_list.h"
#include "sphere.h"
#include "camera.h" 

vec3 random_in_unit_sphere() {
    vec3 p;
    while (p.squared_length() >= 1.0) {
        p = 2.0*vec3(float(rand()) / RAND_MAX, float(rand()) / RAND_MAX, float(rand()) / RAND_MAX) - vec3(1, 1, 1);
    }
    return p;
}

vec3 color(const ray &r, hitable *world) {
    hit_record rec;
    if (world->hit(r, 0.0, FLT_MAX, rec)) {
        vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        return 0.5*color(ray(rec.p, target - rec.p), world);
    } else {
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5*(unit_direction.y() + 1.0);
        return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
    }
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    std::ofstream out("out.ppm");

	int nx = 800;
    int ny = 400;
    int ns = 100;

    out << "P3\n" << nx << " " << ny << "\n255\n";
    
    hitable *list[2];
    list[0] = new sphere(vec3(0, 0, -1), 0.5);
    list[1] = new sphere(vec3(0, -100.5, -1), 100);
    hitable *world = new hitable_list(list, 2);
    
    camera cam;
    for (int j = ny - 1 ; j >= 0 ; j--) {
        for (int i = 0 ; i < nx ; i++) {
            vec3 col(0, 0, 0);

            for (int s = 0 ; s < ns ; s++) {
                float u = float(i + float(rand()) / RAND_MAX) / float(nx);
                float v = float(j + float(rand()) / RAND_MAX) / float(ny);

                ray r = cam.get_ray(u, v);
                vec3 p = r.point_at_parameter(2.0);
                col += color(r, world);
            }
            col /= float(ns);

            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

            int ir = int(255.99*col.r());
            int ig = int(255.99*col.g());
            int ib = int(255.99*col.b());
          
            out << ir << " " << ig << " " << ib << "\n";
        }
    }
    out.close();
    std::getchar();
}