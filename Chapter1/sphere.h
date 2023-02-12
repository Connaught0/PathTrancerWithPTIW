#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"

class sphere :public hitable {
public :
	sphere(){}
	sphere(vec3 cen, float r,material *m) :center(cen), radius(r), mtr_ptr(m) {};
	virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
	vec3 center;
	float radius;
	material *mtr_ptr;
};

bool sphere :: hit(const ray& r, float tmin, float tmax, hit_record& rec) const {
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = dot(oc, r.direction());//这里没乘2
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - a * c;//这后面也可以不乘4
	if (discriminant > 0) {
		float temp = (-b - sqrt(b * b - a * c)) / a;//因此这边也可以少个2
		if (temp<tmax && temp>tmin)
		{
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = mtr_ptr;
			return true;
		}
		temp = (-b + sqrt(b * b - a * c)) / a;//因此这边也可以少个2
		if (temp<tmax && temp>tmin)
		{
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = mtr_ptr;
			return true;
		}
	}
	return false;
}

#endif