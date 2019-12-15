#include <iostream>
#include <fstream>
#include "vec3.h"

int main(int argc, char *argv[]) {
    std::ofstream out("out.ppm");

	int nx = 200;
    int ny = 100;

    out << "P3\n" << nx << " " << ny << "\n255\n";
    
    for (int j = ny - 1 ; j >= 0 ; j--) {
        for (int i = 0 ; i < nx ; i++) {

            vec3 col(
                float(i) / float(nx),
                float(j) / float(ny),
                0.2
            );
          
            int ir = int(255.99*col.r());
            int ig = int(255.99*col.g());
            int ib = int(255.99*col.b());
          
            out << ir << " " << ig << " " << ib << "\n";
        }
    }

    out.close();
}