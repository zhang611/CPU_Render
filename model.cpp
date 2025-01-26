#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "model.h"



Model::Model(const char *filename, char * diffusefilename) : verts_(), uvs_(), faces_() {
    std::ifstream in;
    in.open (filename, std::ifstream::in);
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
            for (int i=0;i<3;i++) iss >> v[i];
            verts_.push_back(v);
        } else if (!line.compare(0, 3, "vt ")) {
            iss >> trash >> trash;
            Vec3f uv;
            for (int i=0;i<3;i++) iss >> uv[i];
            uvs_.push_back(Vec2f(uv.x,uv.y));
        } else if (!line.compare(0, 3, "vn ")) {
            iss >> trash >> trash;
            Vec3f normal;
            for (int i=0;i<3;i++) iss >> normal[i];
            normals_.push_back(normal);
        } else if (!line.compare(0, 2, "f ")) {
            std::vector<ids> f;
            int vidx, uvidx, nmidx;
            iss >> trash;
            while (iss >> vidx >> trash >> uvidx >> trash >> nmidx) {
                vidx--; // in wavefront obj all indices start at 1, not zero
                uvidx--;
                nmidx--;
                f.push_back(ids(vidx, uvidx, nmidx));
            }
            faces_.push_back(f);
        }
    }

    if(diffusefilename != nullptr)
    {
        diffuseMap.read_tga_file(diffusefilename);
        diffuseMap.flip_vertically();
        diffuseMapSize = Vec2i(diffuseMap.get_width(), diffuseMap.get_height());
    }
    
    std::cerr << "# v# " << verts_.size() << " uv# "  << uvs_.size() << " f# "  << faces_.size() << std::endl;
}

Model::~Model() {
}

int Model::nverts() {
    return (int)verts_.size();
}
int Model::nuvs() {
    return (int)uvs_.size();
}
int Model::nfaces() {
    return (int)faces_.size();
}
int Model::nnormals() {
    return (int)normals_.size();
}

std::vector<ids> Model::face(int idx) {
    return faces_[idx];
}

Vec3f Model::vert(int idx) {
    return verts_[idx];
}
Vec3f Model::vert(int iface, int nthvert) {
    auto idx = faces_[iface][nthvert].vidx;
    return verts_[idx];
}
Vec2f Model::uv(int idx) {
    return uvs_[idx];
}
Vec2f Model::uv(int iface, int nthvert) {
    auto idx = faces_[iface][nthvert].uvidx;
    return uvs_[idx];
}

Vec3f Model::normal(int idx) {

    return normals_[idx];
}
Vec3f Model::normal(int iface, int nthvert) {
    auto idx = faces_[iface][nthvert].nmidx;
    return normals_[idx];
}
TGAColor Model::diffuse(float u, float v)
{
    return diffuseMap.get(int(diffuseMapSize.x * u), int(diffuseMapSize.y * v));
}