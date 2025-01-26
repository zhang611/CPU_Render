#ifndef __MODEL_H__
#define __MODEL_H__

#include <vector>
#include "geometry.h"
#include "tgaimage.h"
#include <opencv2/opencv.hpp>

struct ids {
    ids() : vidx(), uvidx(), nmidx() {}
    ids(int v, int uv, int other) : vidx(v), uvidx(uv), nmidx(other) {}
    int vidx, uvidx, nmidx;
};

class Model {
private:
	std::vector<Vec3f> verts_;
	std::vector<Vec2f> uvs_;
	std::vector<Vec3f> normals_;
	std::vector<std::vector<ids> > faces_;

	// cv::Mat diffuseMap;  漫反射贴图
	TGAImage diffuseMap;
	// cv::Vec2i diffuseMapSize;
	Vec2i diffuseMapSize;
public:
	Model(const char *filename, char * diffusefilename);
	~Model();
	int nverts();
	int nfaces();
	int nuvs();
	int nnormals();
	Vec3f vert(int idx);
	Vec3f vert(int iface, int nthvert);
	Vec2f uv(int idx);
	Vec2f uv(int iface, int nthvert);
	Vec3f normal(int idx);
	Vec3f normal(int iface, int nthvert);
	std::vector<ids> face(int idx);
	TGAColor diffuse(float u, float v);
};

#endif //__MODEL_H__