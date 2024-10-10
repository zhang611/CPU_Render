#include "gl.h"

constexpr float MY_PI = 3.1415926f;
Matrix vertex2matrix(Vec3f v) {
    Matrix m(4, 1);
    m[0][0] = v.x;
    m[1][0] = v.y;
    m[2][0] = v.z;
    m[3][0] = 1.f;
    return m;
}

Matrix modelMatrix(float rotation_angle, Vec3f axis)
{
    axis.normalize();
    rotation_angle = rotation_angle * MY_PI / 180.f;
    
    Matrix nnT = Matrix::identity(4), crossn(4,4);
    float cosAlpha = cos(rotation_angle);
    float sinAlpha = sin(rotation_angle);
    float x = axis.x, y = axis.y, z = axis.z;

    // nnT <<  x*x, x*y, x*z,0,
    //         y*x, y*y, y*z,0,
    //         z*x, z*y, z*z,0,
    //         0,0,0,1;
    nnT[0][0] = x*x, nnT[0][1] = x*y, nnT[0][2] = x*z;
    nnT[1][0] = y*x, nnT[1][1] = y*y, nnT[1][2] = y*z;
    nnT[2][0] = z*x, nnT[2][1] = z*y, nnT[2][2] = z*z;
    
    
    // crossn<<    0,-z, y,0,
    //             z, 0,-x,0,
    //             -y,x, 0,0,
    //             0,0,0,1;
                        crossn[0][1] = -z,  crossn[0][2] = y, 
    crossn[1][0] =  z,                      crossn[1][2] = -x,
    crossn[2][0] = -y,  crossn[2][1] = x,
                                                                crossn[3][3] =  1;

    Matrix rotate = Matrix::identity(4) * cosAlpha + (1 - cosAlpha) * nnT + sinAlpha * crossn;
    rotate[3][3] = 1;
    return rotate;
}

//右手系
// be like: glm::lookAt(camera pos，target pos, up)
/*
    NOTE: M是一个正交矩阵，其的Inverse即transpose
        转置之后：原来的列向量为基的正交矩阵就变成了行向量为基的正交矩阵
*/
Matrix lookAt(Vec3f eyePos, Vec3f& targetPos, Vec3f& up)
{
    Vec3f z = (eyePos - targetPos).normalize();
    Vec3f x = cross(up,z).normalize();
    Vec3f y = cross(z,x).normalize();
    Matrix invM = Matrix::identity(4);
    Matrix translate = Matrix::identity(4);
    for (int i = 0; i < 3; i++)
    {
        invM[0][i] = x[i];
        invM[1][i] = y[i];
        invM[2][i] = z[i];
        translate[i][3] = -eyePos[i];
    }
    return invM * translate; 
}

//将可见坐标映射入[-1,1]*[-1,1]*[-1,1]的NDC空间
Matrix projection(float eye_fov, float aspect_ratio,
                                      float zNear, float zFar) {
    Matrix proj = Matrix::identity(4);
    Matrix orth = Matrix::identity(4) ,orthTranslate = Matrix::identity(4),orthScale, pers2orth;
    float n = -zNear,                f = -zFar; // n and f all are negative
    float t = tan(eye_fov/2) * (-n),   b = -t;
    float r = aspect_ratio * t,     l = -r;     //aspect_ratio = width / height
    
    // pers2orth <<    n, 0, 0, 0,
    //                 0, n, 0, 0,
    //                 0, 0, n+f, -n*f,
    //                 0, 0, 1, 0;
    pers2orth[0][0] = n, pers2orth[1][1] = n, pers2orth[2][2] = n + f, pers2orth[2][3] = -n*f,  pers2orth[3][2] = 1;
    // orthScale <<    2/(r - l), 0, 0, 0,
    //                 0, 2/(t - b), 0, 0,
    //                 0, 0, 2/(n - f), 0,
    //                 0, 0, 0,         1;
    orthScale[0][0] = 2/(r - l), orthScale[1][1] = 2/(t - b), orthScale[2][2] = 2/(n - f), orthScale[3][3] = 1;
    // orthTranslate <<  1, 0, 0, -(r+l)/2, 
    //                     0, 1, 0, -(t+b)/2, 
    //                     0, 0, 1, -(n+f)/2, 
    //                     0, 0, 0, 1;
    orthTranslate[0][3] = -(r+l)/2, orthTranslate[1][3] = -(t+b)/2, orthTranslate[2][3] = -(n+f)/2;
    
    orth = orthScale * orthTranslate;
    proj = orth * pers2orth;
    return proj;
}

/*
    透视除法
*/
Matrix & projdivision(Matrix & clip)
{
    Matrix & ndc = clip;
    ndc[0][0] = clip[0][0] / clip[3][0];
    ndc[1][0] = clip[1][0] / clip[3][0];
    ndc[2][0] = clip[2][0] / clip[3][0];
    ndc[3][0] = 1.0f;
    return ndc;
}

/*
    相关解释：https://zhuanlan.zhihu.com/p/66384929
    Function：
        绘制的窗口位置及大小控制吗，
            Viewport矩阵：用于将目标从[-1,1]*[-1,1]*[-1,1]的单位空间转换到[x,x+w]*[y,y+h]*[0,d]的空间下
*/

const int depth  = 255;
Matrix viewport(int x, int y, int w, int h) {
    Matrix m = Matrix::identity(4);
    m[0][3] = x+w/2.f;
    m[1][3] = y+h/2.f;
    m[2][3] = depth/2.f;

    m[0][0] = w/2.f;
    m[1][1] = h/2.f;
    m[2][2] = depth/2.f;
    return m;
}