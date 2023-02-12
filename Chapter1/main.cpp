#include "pch.h"
#include <iostream>
#include <fstream>
#include "float.h"

#include "material.h"

#include "hitable_list.h"
#include "sphere.h"
#include "camera.h"




vec3 color(const ray& r,hitable *world,int depth)
{
	hit_record rec;
	if (world->hit(r, 0.001, FLT_MAX, rec)) {

		ray scattered;
		vec3 attenuation;
		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
		{
			return attenuation * color(scattered, world, depth + 1);//最多弹射50次
		}
		else
		{
			return vec3(0, 0, 0);
		}
	}
	else
	{
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5 * (unit_direction.y() + 1);
		return (1 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
	}
}






int main()
{
	std::fstream file;
	std::string filename = "C:\\Users\\Zz\\Desktop\\helloworld.ppm";
	file.open(filename);
	int nx = 200;
	int ny = 100;
	int ns = 10;

	file << "P3\n" << nx << " " << ny << "\n255\n";



	hitable* world_1_list[5];
	world_1_list[0] = new sphere(vec3(0, 0, -1), 0.5,new lambertian(vec3(0.8,0.3,0.3)));
	world_1_list[1] = new sphere(vec3(0, -100.5, -1), 100,new lambertian(vec3(0.8,0.8,0.0)));
	world_1_list[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2),0.0));
	world_1_list[3] = new sphere(vec3(-1, 0, -1), 0.5, new dielectric(1.5));
	world_1_list[4] = new sphere(vec3(-1, 0, -1), -0.45, new dielectric(1.5));//用一个相反的东西形成以一个玻璃空心球

	hitable* world_1 = new hitable_list(world_1_list, 5);

	
	float R = cos(M_PI / 4);
	
	hitable* world_2_list[2];
	world_2_list[0] = new sphere(vec3(-R, 0, -1), R, new lambertian(vec3(0, 0, 1)));
	world_2_list[1] = new sphere(vec3(R, 0, -1), R, new lambertian(vec3(1, 0, 0)));

	hitable* world_2 = new hitable_list(world_2_list, 2);

	vec3 lookfrom(5, 5, 2);
	vec3 lookat(0, 0, -1);
	float dist_to_focus = (lookfrom - lookat).length();
	camera cam = camera(lookfrom, lookat, vec3(0, 1, 0), 20, float(nx) / float(ny), 2.0, dist_to_focus);

	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			vec3 col(0, 0, 0);
			for (int s = 0; s < ns; s++) {
				float u = float(i + drand48()) / float(nx);
				float v = float(j + drand48()) / float(ny);


				ray r = cam.get_ray(u, v);
				vec3 p = r.point_at_parameter(2.0);
				col += color(r, world_1, 0);
			}
			col /= float(ns);
			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));//garmma矫正
			int ir = int(255.99 * col.r());
			int ig = int(255.99 * col.g());
			int ib = int(255.99 * col.b());
			file << ir << " " << ig << " " << ib << "\n";

		}
	}
	file.close();
	system("start C:\\Users\\Zz\\Desktop\\helloworld.ppm");
}
