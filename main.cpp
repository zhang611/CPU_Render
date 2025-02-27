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

void drawmodel(TGAImage &image, Model *model, Matrix &modelM, Matrix &viewM,
               Matrix &projM, Matrix &viewportM, float *zbuffer) {
    Matrix worldspace, viewspace, clipspace, viewportspace;
    for (int i = 0; i < model->nfaces(); i++) {
        std::vector<ids> face = model->face(i);
        Vec3f scr_v[3], tri_v[3];
        Vec2f tri_uv[3];
        for (int j = 0; j < 3; j++) {
            tri_v[j] = model->vert(face[j].vidx);
            tri_uv[j] = model->uv(face[j].uvidx);

            // MVP div viewport
            worldspace = modelM * vertex2matrix(tri_v[j]);
            viewspace = viewM * worldspace;
            clipspace = projM * viewspace;
            viewportspace = viewportM * projdivision(clipspace);
            scr_v[j] = Vec3f(viewportspace[0][0], viewportspace[1][0],
                             viewportspace[2][0]);
        }
        Vec3f n = cross(tri_v[2] - tri_v[0], tri_v[1] - tri_v[0]);
        n.normalize();
        float intensity = n * light_dir;
        intensity = std::max(intensity, 0.1f);
        triangle(image, model, zbuffer, scr_v, tri_uv, intensity);
    }
}

int main(int argc, char **argv) {
    if (2 == argc) {
        model = new Model(argv[1], nullptr);
    } else {
        model = new Model("assert/african_head.obj",
                          "assert/african_head_diffuse.tga");
        // new Model("assert/qiyana/qiyanahair.obj",
        // "assert/qiyana/qiyanahair_diffuse.tga");
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

    // TODO 为什么fov变大，图片会翻转
    float eye_fov = 45.0f;
    // float eye_fov = 50.0f;
    float aspect_ratio = 1.0f;
    float zNear = 0.1f;
    float zFar = 50.0f;
    while (key != 27) {
        for (int i = width * height - 1; i >= 0; i--)
            zbuffer[i] = std::numeric_limits<float>::min();
        image.clear();
        // radius = 0.1f * sin(time * 2.0f) + radius;
        // float camX = sin(time) * radius;
        // float camZ = cos(time) * radius;
        float camX = 0;
        float camZ = 3;
        Matrix modelM = Matrix::identity(4);
        Matrix tranM = Matrix::identity(4);
        tranM[1][3] = 0;
        tranM[2][3] = -0;
        modelM = tranM * modelM;

        // Matrix modelM = modelMatrix(90, {0, 1, 0});
        Matrix viewM = lookAt({camX, 0, camZ}, target, up);
        Matrix projM = projection(eye_fov, aspect_ratio, zNear, zFar);

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
        // angle += step;
        // time += 0.1f;
        // angle = std::fmodf(angle, 360.0f);  // 浮点数取余
    }

    image.write_tga_file("image/output.tga");
    delete model;
    delete[] zbuffer;
    return 0;
}