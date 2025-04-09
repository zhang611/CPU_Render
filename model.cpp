#include "model.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

<<<<<<< HEAD
Model::Model(const char *filename, const char *diffuseFilename) : verts_(), uvs_(), faces_() {
=======
Model::Model(const char *filename, char *diffusefilename)
    : verts_(), uvs_(), faces_() {
>>>>>>> 5635777f0a4afb69f01ea09271810eee1500cd0d
    std::ifstream in;
    in.open(filename, std::ifstream::in);
    if (in.fail()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (!in.eof()) {
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        char trash;
        if (!line.compare(0, 2, "v ")) {
            iss >> trash;
            Vec3f v;
            for (int i = 0; i < 3; i++) iss >> v[i];
            verts_.push_back(v);
        } else if (!line.compare(0, 3, "vt ")) {
            iss >> trash >> trash;
            Vec3f uv;
            for (int i = 0; i < 3; i++) iss >> uv[i];
<<<<<<< HEAD
            uvs_.emplace_back(uv.x, uv.y);
=======
            uvs_.push_back(Vec2f(uv.x, uv.y));
>>>>>>> 5635777f0a4afb69f01ea09271810eee1500cd0d
        } else if (!line.compare(0, 3, "vn ")) {
            iss >> trash >> trash;
            Vec3f normal;
            for (int i = 0; i < 3; i++) iss >> normal[i];
            normals_.push_back(normal);
        } else if (!line.compare(0, 2, "f ")) {
            std::vector<ids> f;
            int vidx, uvidx, nmidx;
            iss >> trash;
            while (iss >> vidx >> trash >> uvidx >> trash >> nmidx) {
                vidx--;  // in wavefront obj all indices start at 1, not zero
                uvidx--;
                nmidx--;
                f.emplace_back(vidx, uvidx, nmidx);
            }
            faces_.push_back(f);
        }
    }

<<<<<<< HEAD
    if (diffuseFilename != nullptr) {
        diffuseMap.read_tga_file(diffuseFilename);
=======
    if (diffusefilename != nullptr) {
        diffuseMap.read_tga_file(diffusefilename);
>>>>>>> 5635777f0a4afb69f01ea09271810eee1500cd0d
        diffuseMap.flip_vertically();
        diffuseMapSize = Vec2i(diffuseMap.get_width(), diffuseMap.get_height());
    }

<<<<<<< HEAD
    std::cerr << "# v# " << verts_.size() << " uv# " << uvs_.size() << " f# " << faces_.size() << std::endl;
}

Model::~Model() = default;

int Model::nverts() {
    return (int) verts_.size();
}

int Model::nuvs() {
    return (int) uvs_.size();
}

int Model::nfaces() {
    return (int) faces_.size();
}

int Model::nnormals() {
    return (int) normals_.size();
}
=======
    std::cerr << "# v# " << verts_.size() << " uv# " << uvs_.size() << " f# "
              << faces_.size() << std::endl;
}

Model::~Model() {}

int Model::nverts() { return (int)verts_.size(); }
int Model::nuvs() { return (int)uvs_.size(); }
int Model::nnormals() { return (int)normals_.size(); }
int Model::nfaces() { return (int)faces_.size(); }
>>>>>>> 5635777f0a4afb69f01ea09271810eee1500cd0d

std::vector<ids> Model::face(int idx) { return faces_[idx]; }

<<<<<<< HEAD
Vec3f Model::vert(int idx) {
    return verts_[idx];
}

=======
Vec3f Model::vert(int idx) { return verts_[idx]; }
>>>>>>> 5635777f0a4afb69f01ea09271810eee1500cd0d
Vec3f Model::vert(int iface, int nthvert) {
    auto idx = faces_[iface][nthvert].vidx;
    return verts_[idx];
}
<<<<<<< HEAD

Vec2f Model::uv(int idx) {
    return uvs_[idx];
}

=======
Vec2f Model::uv(int idx) { return uvs_[idx]; }
>>>>>>> 5635777f0a4afb69f01ea09271810eee1500cd0d
Vec2f Model::uv(int iface, int nthvert) {
    auto idx = faces_[iface][nthvert].uvidx;
    return uvs_[idx];
}

<<<<<<< HEAD
Vec3f Model::normal(int idx) {

    return normals_[idx];
}

=======
Vec3f Model::normal(int idx) { return normals_[idx]; }
>>>>>>> 5635777f0a4afb69f01ea09271810eee1500cd0d
Vec3f Model::normal(int iface, int nthvert) {
    auto idx = faces_[iface][nthvert].nmidx;
    return normals_[idx];
}
<<<<<<< HEAD

=======
>>>>>>> 5635777f0a4afb69f01ea09271810eee1500cd0d
TGAColor Model::diffuse(float u, float v) {
    return diffuseMap.get(int(diffuseMapSize.x * u), int(diffuseMapSize.y * v));
}