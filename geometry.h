#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

<<<<<<< HEAD
template<class T>
static T min(T x, T y, T z) { return std::min<T>(std::min<T>(x, y), z); }

template<class T>
static T max(T x, T y, T z) { return std::max<T>(std::max<T>(x, y), z); }


template<class t>
=======
template <class t>
>>>>>>> 5635777f0a4afb69f01ea09271810eee1500cd0d
struct Vec2 {
    t x, y;

    Vec2<t>() : x(t()), y(t()) {}

    Vec2<t>(t _x, t _y) : x(_x), y(_y) {}

    Vec2<t>(const Vec2<t> &v) : x(t()), y(t()) { *this = v; }
<<<<<<< HEAD

=======
>>>>>>> 5635777f0a4afb69f01ea09271810eee1500cd0d
    Vec2<t> &operator=(const Vec2<t> &v) {
        if (this != &v) {
            x = v.x;
            y = v.y;
        }
        return *this;
    }
<<<<<<< HEAD

    Vec2<t> operator+(const Vec2<t> &V) const { return Vec2<t>(x + V.x, y + V.y); }

    Vec2<t> operator-(const Vec2<t> &V) const { return Vec2<t>(x - V.x, y - V.y); }

    Vec2<t> operator*(float f) const { return Vec2<t>(x * f, y * f); }

    t &operator[](const int i) { if (i <= 0) return x; else return y; }

    template<class>
    friend std::ostream &operator<<(std::ostream &s, Vec2<t> &v);
};

template<class t>
struct Vec3 {
    t x, y, z;

    Vec3<t>() : x(t()), y(t()), z(t()) {}

    Vec3<t>(t _x, t _y, t _z) : x(_x), y(_y), z(_z) {}

    template<class u>
    explicit Vec3<t>(const Vec3<u> &v);

    Vec3<t>(const Vec3<t> &v) : x(t()), y(t()), z(t()) { *this = v; }

=======
    Vec2<t> operator+(const Vec2<t> &V) const {
        return Vec2<t>(x + V.x, y + V.y);
    }
    Vec2<t> operator-(const Vec2<t> &V) const {
        return Vec2<t>(x - V.x, y - V.y);
    }
    Vec2<t> operator*(float f) const { return Vec2<t>(x * f, y * f); }
    t &operator[](const int i) {
        if (i <= 0)
            return x;
        else
            return y;
    }
    template <class>
    friend std::ostream &operator<<(std::ostream &s, Vec2<t> &v);
};

template <class t>
struct Vec3 {
    t x, y, z;
    Vec3<t>() : x(t()), y(t()), z(t()) {}
    Vec3<t>(t _x, t _y, t _z) : x(_x), y(_y), z(_z) {}
    template <class u>
    Vec3<t>(const Vec3<u> &v);
    Vec3<t>(const Vec3<t> &v) : x(t()), y(t()), z(t()) { *this = v; }
>>>>>>> 5635777f0a4afb69f01ea09271810eee1500cd0d
    Vec3<t> &operator=(const Vec3<t> &v) {
        if (this != &v) {
            this->x = v.x;
            this->y = v.y;
            this->z = v.z;
        }
        return *this;
    }
<<<<<<< HEAD

    Vec3<t> operator^(const Vec3<t> &v) const {
        return Vec3<t>(this->y * v.z - this->z * v.y,
                       this->z * v.x - this->x * v.z,
                       this->x * v.y - this->y * v.x);
    }

    Vec3<t> operator+(const Vec3<t> &v) const { return Vec3<t>(this->x + v.x, this->y + v.y, this->z + v.z); }

    Vec3<t> operator-(const Vec3<t> &v) const { return Vec3<t>(x - v.x, y - v.y, z - v.z); }

    Vec3<t> operator*(float f) const { return Vec3<t>(x * f, y * f, z * f); }

    t operator*(const Vec3<t> &v) const { return x * v.x + y * v.y + z * v.z; }

    [[nodiscard]] float norm() const { return std::sqrt(x * x + y * y + z * z); }

=======
    Vec3<t> operator^(const Vec3<t> &v) const {
        return Vec3<t>(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
    }
    Vec3<t> operator+(const Vec3<t> &v) const {
        return Vec3<t>(x + v.x, y + v.y, z + v.z);
    }
    Vec3<t> operator-(const Vec3<t> &v) const {
        return Vec3<t>(x - v.x, y - v.y, z - v.z);
    }
    Vec3<t> operator*(float f) const { return Vec3<t>(x * f, y * f, z * f); }
    t operator*(const Vec3<t> &v) const { return x * v.x + y * v.y + z * v.z; }
    float norm() const { return std::sqrt(x * x + y * y + z * z); }
>>>>>>> 5635777f0a4afb69f01ea09271810eee1500cd0d
    Vec3<t> &normalize(t l = 1) {
        *this = (*this) * (l / norm());
        return *this;
    }
<<<<<<< HEAD

    t &operator[](const int i) { if (i <= 0) return x; else if (i == 1) return y; else return z; }

    template<class>
    friend std::ostream &operator<<(std::ostream &s, Vec3<t> &v);
};

template<class t>
struct Vec4 {
    t x, y, z, w;

    Vec4<t>() : x(t()), y(t()), z(t()), w(t()) {}

    Vec4<t>(t _x, t _y, t _z, t _w) : x(_x), y(_y), z(_z), w(_w) {}

    template<class u>
    explicit Vec4<t>(const Vec4<u> &v);

    Vec4<t>(const Vec4<t> &v) : x(t()), y(t()), z(t()), w(t()) { *this = v; }

=======
    t &operator[](const int i) {
        if (i <= 0)
            return x;
        else if (i == 1)
            return y;
        else
            return z;
    }
    template <class>
    friend std::ostream &operator<<(std::ostream &s, Vec3<t> &v);
};

template <class t>
struct Vec4 {
    t x, y, z, w;
    Vec4<t>() : x(t()), y(t()), z(t()), w(t()) {}
    Vec4<t>(t _x, t _y, t _z, t _w) : x(_x), y(_y), z(_z), w(_w) {}
    template <class u>
    Vec4<t>(const Vec4<u> &v);
    Vec4<t>(const Vec4<t> &v) : x(t()), y(t()), z(t()), w(t()) { *this = v; }
>>>>>>> 5635777f0a4afb69f01ea09271810eee1500cd0d
    Vec4<t> &operator=(const Vec4<t> &v) {
        if (this != &v) {
            x = v.x;
            y = v.y;
            z = v.z;
            w = v.w;
        }
        return *this;
    }
<<<<<<< HEAD

    Vec4<t> operator+(const Vec4<t> &v) const { return Vec4<t>(x + v.x, y + v.y, z + v.z, w + v.w); }

    Vec4<t> operator-(const Vec4<t> &v) const { return Vec4<t>(x - v.x, y - v.y, z - v.z, w - v.w); }

    Vec4<t> operator*(float f) const { return Vec3<t>(x * f, y * f, z * f, w * f); }

    t operator*(const Vec4<t> &v) const { return x * v.x + y * v.y + z * v.z + w * v.w; }

    [[nodiscard]] float norm() const { return std::sqrt(x * x + y * y + z * z + w * w); }

=======
    Vec4<t> operator+(const Vec4<t> &v) const {
        return Vec4<t>(x + v.x, y + v.y, z + v.z, w + v.w);
    }
    Vec4<t> operator-(const Vec4<t> &v) const {
        return Vec4<t>(x - v.x, y - v.y, z - v.z, w - v.w);
    }
    Vec4<t> operator*(float f) const {
        return Vec3<t>(x * f, y * f, z * f, w * f);
    }
    t operator*(const Vec4<t> &v) const {
        return x * v.x + y * v.y + z * v.z + w * v.w;
    }
    float norm() const { return std::sqrt(x * x + y * y + z * z + w * w); }
>>>>>>> 5635777f0a4afb69f01ea09271810eee1500cd0d
    Vec4<t> &normalize(t l = 1) {
        *this = (*this) * (l / norm());
        return *this;
    }
<<<<<<< HEAD

    t &operator[](const int i) {
        if (i <= 0) return x;
        else if (i == 1) return y;
        else if (i == 2)
            return z;
        else return w;
    }

    template<class>
    friend std::ostream &operator<<(std::ostream &s, Vec4<t> &v);
};

template<class t>
=======
    t &operator[](const int i) {
        if (i <= 0)
            return x;
        else if (i == 1)
            return y;
        else if (i == 2)
            return z;
        else
            return w;
    }
    template <class>
    friend std::ostream &operator<<(std::ostream &s, Vec4<t> &v);
};

template <class t>
>>>>>>> 5635777f0a4afb69f01ea09271810eee1500cd0d
std::ostream &operator<<(std::ostream &s, Vec2<t> &v) {
    s << "(" << v.x << ", " << v.y << ")\n";
    return s;
}

<<<<<<< HEAD
template<class t>
=======
template <class t>
>>>>>>> 5635777f0a4afb69f01ea09271810eee1500cd0d
std::ostream &operator<<(std::ostream &s, Vec3<t> &v) {
    s << "(" << v.x << ", " << v.y << ", " << v.z << ")\n";
    return s;
}

<<<<<<< HEAD
template<class t>
=======
template <class t>
>>>>>>> 5635777f0a4afb69f01ea09271810eee1500cd0d
std::ostream &operator<<(std::ostream &s, Vec4<t> &v) {
    s << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")\n";
    return s;
}
<<<<<<< HEAD

template<typename T>
Vec3<T> cross(Vec3<T> v1, Vec3<T> v2) {
    return Vec3<T>(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
=======
template <typename T>
Vec3<T> cross(Vec3<T> v1, Vec3<T> v2) {
    return Vec3<T>(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z,
                   v1.x * v2.y - v1.y * v2.x);
>>>>>>> 5635777f0a4afb69f01ea09271810eee1500cd0d
}

typedef Vec2<float> Vec2f;
typedef Vec2<int> Vec2i;
typedef Vec3<float> Vec3f;
typedef Vec3<int> Vec3i;
typedef Vec4<float> Vec4f;

//////////////////////////////////////////////////////////////////////////////////////////////

const int DEFAULT_ALLOC = 4;

class Matrix {
    std::vector<std::vector<float>> m;
    int rows, cols;

<<<<<<< HEAD
public:
    explicit Matrix(int r = DEFAULT_ALLOC, int c = DEFAULT_ALLOC);

    explicit Matrix(std::vector<float> nums);

    explicit Matrix(Vec3f v);

=======
   public:
    Matrix(int r = DEFAULT_ALLOC, int c = DEFAULT_ALLOC);
>>>>>>> 5635777f0a4afb69f01ea09271810eee1500cd0d
    inline int nrows();

    inline int ncols();

    static Matrix identity(int dimensions);

    std::vector<float> &operator[](int i);

    Matrix operator*(const Matrix &a);

    Matrix operator+(const Matrix &a);

    Matrix operator*(float b);

    Matrix transpose();

    Matrix inverse();

    friend std::ostream &operator<<(std::ostream &s, Matrix &m);
<<<<<<< HEAD

=======
>>>>>>> 5635777f0a4afb69f01ea09271810eee1500cd0d
    friend Matrix operator*(float b, Matrix &m);
};

/////////////////////////////////////////////////////////////////////////////////////////////

<<<<<<< HEAD
#endif //GEOMETRY_H_
=======
#endif  //__GEOMETRY_H__
>>>>>>> 5635777f0a4afb69f01ea09271810eee1500cd0d
