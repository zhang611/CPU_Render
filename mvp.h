#ifndef GL_H_
#define GL_H_

#include <utility>

#include "geometry.h"
#include "tgaimage.h"
Matrix vertex2matrix(Vec3f v);

/*
    Matrix:
        Model Matrix
        View Matrix
        Proj Matrix
        Proj division
        ViewPort Matrix
*/
Matrix modelMatrix(float rotation_angle, Vec3f axis = {0, 0, 1});
Matrix lookAt(Vec3f eyePos, Vec3f& targetPos, Vec3f& up);
Matrix projection(float eye_fov, float aspect_ratio, float zNear, float zFar);
Matrix& projdivision(Matrix& clip);
Matrix viewport(int x, int y, int w, int h);

struct fragment_shader_payload {
    fragment_shader_payload() {
        // texture = nullptr;
    }

    fragment_shader_payload(const Vec3f& col, const Vec3f& nor, const Vec2f& tc)
        : color(col), normal(nor), tex_coords(tc) /*, texture(tex)*/ {}

    Vec3f view_pos;
    Vec3f color;
    Vec3f normal;
    Vec2f tex_coords;
    // Texture* texture;
};

struct vertex_shader_payload {
    Vec3f position;
};

class IShader {
<<<<<<< HEAD:mvp.h
public:
    void setModel(Matrix model) { modelM = std::move(model); }
    void setLookAt(Matrix lookat) { lookatM = std::move(lookat); }
    void setProj(Matrix proj) { projM = std::move(proj); }
    void setViewPort(Matrix viewport) { viewportM = std::move(viewport); }
=======
   public:
    void setModel(Matrix model) { modelM = model; }
    void setLookAt(Matrix lookat) { lookatM = lookat; }
    void setProj(Matrix proj) { projM = proj; }
    void setViewPort(Matrix viewport) { viewportM = viewport; }
>>>>>>> 5635777f0a4afb69f01ea09271810eee1500cd0d:gl.h
    virtual ~IShader();
    // 1. transform the coordinates of the vertices
    // 2. prepare data for fragment
    virtual Vec4f vertex(int iface, int nthvert) = 0;
    // 1. determine the color of the current pixel.
    // 2. discard pixel that we don't want
    virtual bool fragment(Vec3f bar, TGAColor& color) = 0;

   private:
    Matrix modelM;
    Matrix lookatM;
    Matrix projM;
    Matrix viewportM;
};
#endif