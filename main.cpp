#include <iostream>
#include <fstream>
#include "headers/camera.h"
#include "headers/hitable_list.h"
#include "headers/material.h"
#include "headers/sphere.h"

using namespace std;

vec3 color(const ray &r, hitable *world, int depth)
{
    hit_record rec;
    if(world->hit(r, 0.001, 0x3f3f3f3f, rec))
    {
        ray scattered;
        vec3 attenuation;
        if(depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation*color(scattered, world, depth+1);
        else
            return vec3(0, 0, 0);
    }
    else
    {
        vec3 unit_direction = r.direction().unit_vector();
        float t = 0.5*(unit_direction.y() + 1.0);
        return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
    }
}

hitable* random_scene()
{
    int n = 500;
    hitable **llist = new hitable* [n];
    llist[0] = new sphere(vec3(0, -1000, 0), 1000, new lambertian(vec3(0.5, 0.5, 0.5)));
    int i = 1;
    for(int a = -10; a < 10; ++a)
    {
        for(int b = -10; b < 10; ++b)
        {
            float material_choice = randfloat();
            vec3 center(a+0.9*randfloat(), 0.2, b+0.9*randfloat());
            if((center - vec3(4, 1.3, 2)).length() > 1.3 &&
               (center - vec3(-4, 1.0, 0)).length() > 1.0 &&
               (center - vec3(0, 1.2, 0)).length() > 1.2)
            {
                if(material_choice < 0.8)
                    llist[i++] = new sphere(center, 0.2, new lambertian(vec3(randfloat()*randfloat(),
                                                                             randfloat()*randfloat(),
                                                                             randfloat()*randfloat())));
                else if(material_choice < 0.95)
                    llist[i++] = new sphere(center, 0.2, new metal(vec3(0.5*(1 + randfloat()), 0.5*(1 + randfloat()), 0.5*(1 + randfloat())), 0.5*randfloat()));
                else
                    llist[i++] = new sphere(center, 0.2, new dielectric(1.5));
            }
        }
    }

    llist[i++] = new sphere(vec3(0, 1.2, 0), 1.2, new dielectric(1.5));
    llist[i++] = new sphere(vec3(-4, 1.0, 0), 1.0, new lambertian(vec3(0.9, 0.9, 0.0)));
    llist[i++] = new sphere(vec3(4, 1.3, 2), 1.3, new metal(vec3(0.2, 0.5, 0.8), 0.0));

    return new hitable_list(llist, i);
}

int main()
{
	int nx = 1280;
    int ny = 720;
    int ns = 100;

    hitable *world = random_scene();

    vec3 lookfrom(8, 2, 10);
    vec3 lookat(0, 0, 0);
    float vfov = 30;
    float dist_to_focus = 10.0;
    float aperture = 0.2;
    camera cam(lookfrom, lookat, vec3(0, 1, 0), vfov, float(nx)/float(ny), aperture, dist_to_focus);

    ofstream outfile;
    outfile.open("result.ppm", ios::out | ios::trunc);
    outfile << "P3\n" << nx << " " << ny << "\n255\n";
    cout << "Start!" << endl;
    for(int j = ny - 1; j >= 0; j--)
    {
        if((ny - j) % 10 == 0) cout << "iteration: " << ny - j << endl;
        for(int i = 0; i < nx; i++)
        {
            vec3 col(0, 0, 0);
            for(int s = 0; s < ns; ++s)
            {
                float u = float(i + randfloat()) / float(nx);
                float v = float(j + randfloat()) / float(ny);
                ray r = cam.get_ray(u, v);
                col += color(r, world, 0);
            }
            col /= float(ns);
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
            int ir = int(col[0]*255);
            int ig = int(col[1]*255);
            int ib = int(col[2]*255);
            outfile << ir << " " << ig << " " << ib << "\n";
        }
    }
    cout << "Finished!" << endl;
    outfile.close();
	return 0;
}
