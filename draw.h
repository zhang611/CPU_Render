#ifndef DRAW_H_
#define DRAW_H_

#include "geometry.h"
<<<<<<< HEAD

void line(TGAImage &image, int x0, int y0, int x1, int y1, const TGAColor &color) {
    // 保证斜率在0-1之间
    bool steep = false;
    if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
=======
#include "model.h"
#include "tgaimage.h"
void line(TGAImage &image, int x0, int y0, int x1, int y1, TGAColor color) {
    bool steep = false;
    if (std::abs(x0 - x1) <
        std::abs(y0 - y1)) {  // if the line is steep, we transpose the image
>>>>>>> 5635777f0a4afb69f01ea09271810eee1500cd0d
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
<<<<<<< HEAD

    // 保证x0 < x1
    if (x0 > x1) { // make it left−to−right
=======
    if (x0 > x1) {  // make it left−to−right
>>>>>>> 5635777f0a4afb69f01ea09271810eee1500cd0d
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    int dx = x1 - x0, dy = y1 - y0;
    int derror2 = std::abs(dy) * 2, error2 = 0;
    int y = y0;
    for (int x = x0; x < x1; x++) {
<<<<<<< HEAD
        if (steep) image.set(y, x, color);
        else image.set(x, y, color);
=======
        if (steep)
            image.set(y, x, color);
        else
            image.set(x, y, color);
>>>>>>> 5635777f0a4afb69f01ea09271810eee1500cd0d
        error2 += derror2;
        if (error2 > dx) {
            y += (y1 > y0 ? 1 : -1);
            error2 -= dx + dx;
        }
    }
<<<<<<< HEAD
=======

    return;
}

static Vec3f barycentric(const Vec2i *v, const Vec2i &point) {
    Vec3f vec1 =
        Vec3f((float)v[2].x - (float)v[0].x, (float)v[1].x - (float)v[0].x,
              (float)v[0].x - (float)point.x);
    Vec3f vec2 =
        Vec3f((float)v[2].y - (float)v[0].y, (float)v[1].y - (float)v[0].y,
              (float)v[0].y - (float)point.y);

    Vec3f u = cross(vec1, vec2);
    if (std::abs(u.z) < 1) return Vec3f(-1, 1, 1);
    return Vec3f(1.f - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z);
>>>>>>> 5635777f0a4afb69f01ea09271810eee1500cd0d
}

// TODO: 重心坐标的理解,试试看面积法
static Vec3f barycentric(const Vec3f *v, const Vec3f &point) {
    Vec3f vec1 = Vec3f(v[2].x - v[0].x, v[1].x - v[0].x, v[0].x - point.x);
    Vec3f vec2 = Vec3f(v[2].y - v[0].y, v[1].y - v[0].y, v[0].y - point.y);

    Vec3f u = cross(vec1, vec2);
<<<<<<< HEAD
    if (std::abs(u.z) < 1) return {-1, 1, 1};
    return {1.f - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z};
}

static Vec2f
interpolate(float alpha, float beta, float gamma, Vec2f &vert1, Vec2f &vert2, Vec2f &vert3, float weight = 1.0f) {
=======
    if (std::abs(u.z) < 1)
        return Vec3f(-1, 1, 1);  // 三角形退化，返回一个不合法的重心坐标
    return Vec3f(1.f - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z);
}

template <class T>
static T min(T x, T y, T z) {
    return std::min<T>(std::min<T>(x, y), z);
}

template <class T>
static T max(T x, T y, T z) {
    return std::max<T>(std::max<T>(x, y), z);
}

static Vec2f interpolate(float alpha, float beta, float gamma, Vec2f &vert1,
                         Vec2f &vert2, Vec2f &vert3, float weight = 1.0f) {
>>>>>>> 5635777f0a4afb69f01ea09271810eee1500cd0d
    auto u = (alpha * vert1[0] + beta * vert2[0] + gamma * vert3[0]);
    auto v = (alpha * vert1[1] + beta * vert2[1] + gamma * vert3[1]);
    u /= weight;
    v /= weight;
<<<<<<< HEAD

    return {u, v};
}

void triangle(TGAImage &image, Model *model, float *zbuffer, Vec3f *v, Vec2f *coords, float intensity) {
    int width = image.get_width(), height = image.get_height();
    int minX = (int) std::floor(min(v[0].x, v[1].x, v[2].x));
    minX = std::max(minX, 0);
    int maxX = (int) std::ceil(max(v[0].x, v[1].x, v[2].x));
    maxX = std::min(maxX, width);
    int minY = (int) std::floor(min(v[0].y, v[1].y, v[2].y));
    minY = std::max(minY, 0);
    int maxY = (int) std::ceil(max(v[0].y, v[1].y, v[2].y));
    maxY = std::min(maxY, height);

=======
    return Vec2f(u, v);
}

void triangle(TGAImage &image, Model *model, float *zbuffer, Vec3f *v,
              Vec2f *tri_uv, float intensity) {
    // 超出屏幕的部分不绘制，裁剪操作
    int width = image.get_width(), height = image.get_height();
    int minX = (int)std::floor(min(v[0].x, v[1].x, v[2].x));
    minX = std::max(minX, 0);
    int maxX = (int)std::ceil(max(v[0].x, v[1].x, v[2].x));
    maxX = std::min(maxX, width);
    int minY = (int)std::floor(min(v[0].y, v[1].y, v[2].y));
    minY = std::max(minY, 0);
    int maxY = (int)std::ceil(max(v[0].y, v[1].y, v[2].y));
    maxY = std::min(maxY, height);

    // TODO增加背面剔除，测试一下


>>>>>>> 5635777f0a4afb69f01ea09271810eee1500cd0d
    Vec3f p;
    Vec2f uv;
    for (int y = minY; y < maxY; y++) {
        for (int x = minX; x < maxX; x++) {
<<<<<<< HEAD
            p.x = (float) x + 0.5f;
            p.y = (float) y + 0.5f;
            p.z = 0.f;
            Vec3f bc_screen = barycentric(v, p);  // 屏幕空间插值
            // 重心坐标系数，如果有一个小于0，说明在外部
            if (bc_screen.x < 0 || bc_screen.y < 0 || bc_screen.z < 0) continue;

            for (int i = 0; i < 3; i++) p.z += v[i].z * bc_screen[i];

            uv = interpolate(bc_screen.x, bc_screen.y, bc_screen.z, coords[0], coords[1], coords[2]);

            int idx = int(x + y * width);
            if (p.z <= zbuffer[idx]) continue;
            zbuffer[idx] = p.z;
            TGAColor diffuse = model->diffuse(uv.x, uv.y);
            image.set(x, y, TGAColor((unsigned char) (intensity * diffuse.r), (unsigned char) (intensity * diffuse.g),
                                     (unsigned char) (intensity * diffuse.b), 255));

=======
            p.x = (float)x + 0.5f;
            p.y = (float)y + 0.5f;
            p.z = 0.f;
            Vec3f bc_screen = barycentric(v, p);  // 重心坐标
            if (bc_screen.x < 0 || bc_screen.y < 0 || bc_screen.z < 0)
                continue;  // 像素超出三角形范围

            // TODO 思考一下，这里是不是不需要裁剪了，不可能出现少一个面的情况
            for (int i = 0; i < 3; i++) p.z += v[i].z * bc_screen[i];
            // TODO 这里有没有做纹理的深度矫正
            uv = interpolate(bc_screen.x, bc_screen.y, bc_screen.z, tri_uv[0],
                             tri_uv[1], tri_uv[2]);

            int idx = int(x + y * width);
            if (p.z <= zbuffer[idx]) continue;  // 深度测试
            zbuffer[idx] = p.z;
            TGAColor diffuse = model->diffuse(uv.x, uv.y);
            image.set(x, y,
                      TGAColor((unsigned char)(intensity * diffuse.r),
                               (unsigned char)(intensity * diffuse.g),
                               (unsigned char)(intensity * diffuse.b), 255));
>>>>>>> 5635777f0a4afb69f01ea09271810eee1500cd0d
        }
    }
}

<<<<<<< HEAD
#endif //DRAW_H_
=======
#endif  //__DRAW_H__
>>>>>>> 5635777f0a4afb69f01ea09271810eee1500cd0d
