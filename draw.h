#ifndef __DRAW_H__
#define __DRAW_H__

#include "tgaimage.h"
#include "geometry.h"
#include "model.h"
void line(TGAImage & image, int x0, int y0, int x1, int y1, TGAColor color)
{
    bool steep = false;
	if (std::abs(x0-x1)<std::abs(y0-y1)) { // if the line is steep, we transpose the image 
        std::swap(x0, y0); 
        std::swap(x1, y1); 
        steep = true; 
    }
    if (x0>x1) { // make it left−to−right 
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    int dx = x1 - x0, dy = y1 - y0;
	int derror2 = std::abs(dy)*2, error2 = 0;
	int y = y0;
	for(int x = x0; x < x1; x++)
	{
		if(steep) image.set(y, x , color);
		else image.set(x, y, color);
		error2 += derror2;
		if(error2 > dx)
		{
			y += (y1 > y0 ? 1: -1);
			error2 -= dx + dx;
		}
	}

	return ;
}

static Vec3f barycentric(const Vec2i *v, const Vec2i &point) {

    Vec3f vec1 = Vec3f((float)v[2].x - (float)v[0].x, (float)v[1].x - (float)v[0].x, (float)v[0].x - (float)point.x);
    Vec3f vec2 = Vec3f((float)v[2].y - (float)v[0].y, (float)v[1].y - (float)v[0].y, (float)v[0].y - (float)point.y);

    Vec3f u = cross(vec1, vec2);
    if (std::abs(u.z)<1) return Vec3f(-1,1,1);
    return Vec3f(1.f-(u.x+u.y)/u.z, u.y/u.z, u.x/u.z); 
}

static Vec3f barycentric(const Vec3f *v, const Vec3f &point) {

    Vec3f vec1 = Vec3f(v[2].x - v[0].x, v[1].x - v[0].x, v[0].x - point.x);
    Vec3f vec2 = Vec3f(v[2].y - v[0].y, v[1].y - v[0].y, v[0].y - point.y);

    Vec3f u = cross(vec1, vec2);
    if (std::abs(u.z)<1) return Vec3f(-1,1,1);
    return Vec3f(1.f-(u.x+u.y)/u.z, u.y/u.z, u.x/u.z); 
}

template <class T>
static T min(T x, T y, T z) { return std::min<T>(std::min<T>(x,y),z); }

template <class T>
static T max(T x, T y, T z) { return std::max<T>(std::max<T>(x,y),z); }

static Vec2f interpolate(float alpha, float beta, float gamma, Vec2f& vert1, Vec2f& vert2, Vec2f& vert3, float weight = 1.0f)
{
    auto u = (alpha * vert1[0] + beta * vert2[0] + gamma * vert3[0]);
    auto v = (alpha * vert1[1] + beta * vert2[1] + gamma * vert3[1]);

    u /= weight;
    v /= weight;
    
    return Vec2f(u, v);
}

void triangle(TGAImage & image, Model * model, float * zbuffer, Vec3f * v, Vec2f * coords, float intensity)
{
    int width = image.get_width(), height = image.get_height();
    int minX = (int)std::floor(min(v[0].x, v[1].x, v[2].x));    minX = std::max(minX, 0);
    int maxX = (int)std::ceil (max(v[0].x, v[1].x, v[2].x));    maxX = std::min(maxX, width);
    int minY = (int)std::floor(min(v[0].y, v[1].y, v[2].y));    minY = std::max(minY, 0);
    int maxY = (int)std::ceil (max(v[0].y, v[1].y, v[2].y));    maxY = std::min(maxY, height);
    
    Vec3f p;
    Vec2f uv;
    for(int y = minY; y < maxY; y++)
    {
        for(int x = minX; x < maxX; x++)
        {
            p.x = (float)x + 0.5f; p.y = (float)y + 0.5f; p.z = 0.f;
            Vec3f bc_screen  = barycentric(v, p);
            if(bc_screen.x < 0 || bc_screen.y < 0 || bc_screen.z < 0) continue;
            
            for (int i=0; i<3; i++) p.z += v[i].z * bc_screen[i];

            uv = interpolate(bc_screen.x, bc_screen.y, bc_screen.z, coords[0], coords[1],coords[2]);

            int idx = int(x + y * width);
            if ( p.z <= zbuffer[idx]) continue;
            zbuffer[idx] = p.z;
            TGAColor diffuse = model->diffuse(uv.x, uv.y);
            image.set(x, y, TGAColor((unsigned char)(intensity * diffuse.r), (unsigned char)(intensity * diffuse.g), (unsigned char)(intensity * diffuse.b), 255));

        }
    }
}

#endif //__DRAW_H__