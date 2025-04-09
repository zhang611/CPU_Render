#include <vector>
#include <cmath>
#include "tgaimage.h"
#include "model.h"
#include "draw.h"
#include <opencv2/opencv.hpp>
#include "mvp.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor green = TGAColor(0, 255, 0, 255);

Model *model = nullptr;
float *zbuffer = nullptr;

Vec3f camera(0, 0, 3);
Vec3f target(0, 0, 0);
Vec3f up(0, 1, 0);

const int width = 800;
const int height = 800;

Vec3f light_dir(0, 0, -1);


void drawModel(TGAImage &image, Model *model, Matrix &modelM, Matrix &viewM, Matrix &projM, Matrix &viewportM) {
    Matrix worldSpace, viewSpace, clipSpace, viewportspace;
    for (int i = 0; i < model->nfaces(); i++) {
        std::vector<ids> face = model->face(i);
        Vec3f pts[3], modelpos[3];
        Vec2f coords[3];
        for (int j = 0; j < 3; j++) {
            modelpos[j] = model->vert(face[j].vidx);
            coords[j] = model->uv(face[j].uvidx);
            // pts -> point to screen
            //pts[j] = Vec3f(trunc((v.x + 1.f) * width / 2.f + .5f), trunc((v.y + 1.f) * height / 2.f + .5f), v.z);
//            worldSpace = modelM * vertex2matrix(modelpos[j]);
            worldSpace = modelM * Matrix(modelpos[j]);
            viewSpace = viewM * worldSpace;
            clipSpace = projM * viewSpace;
            viewportspace = viewportM * projdivision(clipSpace);
            pts[j] = Vec3f(viewportspace[0][0], viewportspace[1][0], viewportspace[2][0]);
            // pts[j] = matrix2vertex(viewportM * projM * viewM * modelM * vertex2matrix(modelpos[j]));
        }
        Vec3f n = cross(modelpos[2] - modelpos[0], modelpos[1] - modelpos[0]);
        n.normalize();
        float intensity = n * light_dir;

        triangle(image, model, zbuffer, pts, coords, std::max(intensity, 0.1f));
    }
}


void renderModel() {
    model = new Model("../assets/obj/african_head.obj",
                      "../assets/obj/african_head_diffuse.tga");

    zbuffer = new float[width * height];

    TGAImage image(width, height, TGAImage::RGB);

    std::string mTitle = "image";

    cv::Mat img(width, height, CV_8UC3);
    int key = -1;

    float angle = 0.0f;
    float step = 1.;
    Matrix viewportM = viewport(0, 0, width, height);
    float radius = 3.0f;
    float time = 0.0f;
    // GouraudShader shader;
    while (key != 27) {
        for (int i = width * height - 1; i >= 0; i--) zbuffer[i] = std::numeric_limits<float>::infinity();
        image.clear();
        radius = 0.1f * sin(time * 2.0f) + radius;
        float camX = sin(time) * radius;
        float camZ = cos(time) * radius;
        Matrix modelM = Matrix::identity(4);// modelMatrix(angle, {0,1,0});
        Matrix viewM = lookAt({camX, 0, camZ}, target, up);
        Matrix projM = projection(45, 1, 0.1f, 50.0f);

        // shader.setModel(modelM); shader.setLookAt(viewM); shader.setProj(projM); shader.setViewPort(viewportM);
        // drawModel(image, model, shader, zbuffer);
        drawModel(image, model, modelM, viewM, projM, viewportM);
        image.flip_vertically(); // i want to have the origin at the left bottom corner of the image

        img.data = image.buffer();
        cv::imshow(mTitle, img);
        if (cv::getWindowProperty(mTitle, cv::WND_PROP_AUTOSIZE) < 1)
            break;
        key = cv::waitKey(10);
        angle += step;
        time += 0.1f;
        angle = std::fmodf(angle, 360.0f);
    }

    image.write_tga_file("output.tga");

    delete model;
    delete[] zbuffer;
}


void drawLine() {
    TGAImage image(width, height, TGAImage::RGB);
    std::string mTitle = "image";
    cv::namedWindow(mTitle, cv::WINDOW_AUTOSIZE);
    cv::Mat img(height, width, CV_8UC3);
    int key = -1;
    while (key != 27) {
        key = cv::waitKey(10);
        image.clear();

        line(image, 0, 0, 500, 500, TGAColor(0, 0, 255, 255));

        img.data = image.buffer();
        cv::imshow(mTitle, img);
    }
}


int main(int argc, char **argv) {
    renderModel();

//    drawLine();

    return 0;
}