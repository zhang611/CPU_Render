#include <cmath>
#include <opencv2/opencv.hpp>
#include <vector>

#include "draw.h"
#include "gl.h"
#include "model.h"
#include "tgaimage.h"
const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor green = TGAColor(0, 255, 0, 255);

Model *model = NULL;
float *zbuffer = NULL;

Vec3f camera(0, 0, 3);
Vec3f target(0, 0, 0);
Vec3f up(0, 1, 0);

const int width = 800;
const int height = 800;

Vec3f light_dir(0, 0, -1);

// class GouraudShader : IShader {
// private:
//     Vec3f varying_intensity; // written by vertex shader, read by fragment
//     shader
// public :
//     virtual Vec4f vertex(int iface, int nthvert) {
//         varying_intensity[nthvert] = std::max(0.f, model->normal(iface,
//         nthvert)*light_dir); // get diffuse lighting intensity Vec4f
//         gl_Vertex = embed<4>(model->vert(iface, nthvert)); // read the vertex
//         from .obj file return viewportM * projM * lookatM * modelM *
//         gl_Vertex; // transform it to screen coordinates
//     }

//     virtual bool fragment(Vec3f barycentric, TGAColor &color) {
//         float intensity = varying_intensity * barycentric;   // interpolate
//         intensity for the current pixel color = TGAColor(255, 255, 255, 255)
//         * intensity; // well duh color.a = 255; return false; // no, we do
//         not discard this pixel
//     }
// };

// class PhongShader : IShader {
// private:
//     Vec3f varying_intensity;
//     mat<2,3,float> varying_uv;

// public :
//     virtual Vec4f vertex(int iface, int nthvert) {
//         varying_uv.set_col(nthvert, model->uv(iface, nthvert));
//         varying_intensity[nthvert] = std::max(0.f, model->normal(iface,
//         nthvert)*light_dir); // get diffuse lighting intensity Vec4f
//         gl_Vertex = embed<4>(model->vert(iface, nthvert)); // read the vertex
//         from .obj file return viewportM * projM * lookatM * modelM *
//         gl_Vertex; // transform it to screen coordinates
//     }

//     virtual bool fragment(Vec3f barycentric, TGAColor &color) {
//         float intensity = varying_intensity * barycentric;   // interpolate
//         intensity for the current pixel Vec2f uv = varying_uv * barycentric;
//         color = model->diffuse(uv.x, uv.y) * intensity;
//         color.a = 255;
//         return false;                                       // no, we do not
//         discard this pixel
//     }
// }

// void drawmodel(TGAImage &image, Model *model, IShader & shader, float
// *zbuffer)
// {
//     for (int i = 0; i < model->nfaces(); i++)
//     {
//         Vec4f screen_coords[3];
//         for (int j=0; j<3; j++) screen_coords[j] = shader.vertex(i, j);
//         triangle(image, model, screen_coords, shader, zbuffer);
//     }
// }
void drawmodel(TGAImage &image, Model *model, Matrix &modelM, Matrix &viewM,
               Matrix &projM, Matrix &viewportM, float *zbuffer) {
    Matrix worldspace, viewspace, clipspace, viewportspace;
    for (int i = 0; i < model->nfaces(); i++) {
        std::vector<ids> face = model->face(i);
        Vec3f pts[3], modelpos[3];
        Vec2f coords[3];
        for (int j = 0; j < 3; j++) {
            modelpos[j] = model->vert(face[j].vidx);
            coords[j] = model->uv(face[j].uvidx);
            // pts -> point to screen
            // pts[j] = Vec3f(trunc((v.x + 1.f) * width / 2.f + .5f), trunc((v.y
            // + 1.f) * height / 2.f + .5f), v.z);
            worldspace = modelM * vertex2matrix(modelpos[j]);
            viewspace = viewM * worldspace;
            clipspace = projM * viewspace;
            viewportspace = viewportM * projdivision(clipspace);
            pts[j] = Vec3f(viewportspace[0][0], viewportspace[1][0],
                           viewportspace[2][0]);
            // pts[j] = matrix2vertex(viewportM * projM * viewM * modelM *
            // vertex2matrix(modelpos[j]));
        }
        Vec3f n = cross(modelpos[2] - modelpos[0], modelpos[1] - modelpos[0]);
        n.normalize();
        float intensity = n * light_dir;

        triangle(image, model, zbuffer, pts, coords, std::max(intensity, 0.1f));
    }
}

int main(int argc, char **argv) {
    if (2 == argc) {
        model = new Model(argv[1], nullptr);
    } else {
        model =
            new Model("obj/african_head.obj", "obj/african_head_diffuse.tga");
    }

    zbuffer = new float[width * height];
    TGAImage image(width, height, TGAImage::RGB);
    std::string mTitle = "image";
    cv::Mat img(width, height, CV_8UC3);  // 8 bit unsigned, 3 channels
    
    int key = -1;
    float angle = 0.0f;
    float step = 1.;
    Matrix viewportM = viewport(0, 0, width, height);
    float radius = 3.0f;
    float time = 0.0f;

    // GouraudShader shader;
    while (key != 27) {
        for (int i = width * height - 1; i >= 0; i--)
            zbuffer[i] = std::numeric_limits<float>::min();
        image.clear();
        radius = 0.1f * sin(time * 2.0f) + radius;
        float camX = sin(time) * radius;
        float camZ = cos(time) * radius;
        Matrix modelM = Matrix::identity(4);  // modelMatrix(angle, {0,1,0});
        Matrix viewM = lookAt({camX, 0, camZ}, target, up);
        Matrix projM = projection(45, 1, 0.1f, 50.0f);

        // shader.setModel(modelM); shader.setLookAt(viewM);
        // shader.setProj(projM); shader.setViewPort(viewportM);
        // drawmodel(image, model, shader, zbuffer);
        drawmodel(image, model, modelM, viewM, projM, viewportM, zbuffer);
        image.flip_vertically();  // i want to have the origin at the left
                                  // bottom corner of the image

        img.data = image.buffer();
        cv::imshow(mTitle, img);
        if (cv::getWindowProperty(mTitle, cv::WND_PROP_AUTOSIZE) < 1) break;
        key = cv::waitKey(10);
        angle += step;
        time += 0.1f;
        angle = std::fmodf(angle, 360.0f);
    }

    image.write_tga_file("image/output.tga");
    delete model;
    delete[] zbuffer;
    return 0;
}