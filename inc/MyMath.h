#include <math.h>

template <class T>
struct Vector2 // 二维向量
{
    T x, y;
    Vector2() : x(0), y(0){}; // 构造函数重载
    Vector2(T x) : x(x), y(x){};
    Vector2(T x, T y) : x(x), y(y){};
    Vector2 operator+(Vector2 &v) { return Vector2(x + v.x, y + v.y); }; // 运算符重载
    Vector2 operator-(Vector2 &v) { return Vector2(x - v.x, y - v.y); };
    Vector2 operator*(float a) { return Vector2(x * a, y * a); };
    void operator+=(Vector2 &v) { x += v.x, y += v.y; };
    void operator-=(Vector2 &v) { x -= v.x, y -= v.y; };
    void operator*=(Vector2 &v) { x *= v.x, y *= v.y; };
    T norm()
    {
        T dis;
        dis = sqrt(x * x + y * y);
        return dis;
    }                                                                            // 二范数
    T dot(Vector2 &v) { return x * v.x + y * v.y; };                             // 点积
    T projection(Vector2 &v) { return this->dot(v) / v.norm(); };                // 投影
    Vector2 normalize() { return Vector2(x / this->norm(), y / this->norm()); }; // 标准化值
    void normalized()                                                            // 标准化
    {
        T norm = this->norm();
        x /= norm, y /= norm;
    }
};

template <class T>
struct Vector3 // 三维向量
{
    T x, y, z;
    Vector3() : x(0), y(0), z(0){}; // 构造函数重载
    Vector3(T x, T y, T z) : x(x), y(y), z(z){};
    Vector3 operator+(Vector3 &v) { return Vector3(x + v.x, y + v.y, z + v.z); }; // 运算符重载
    Vector3 operator-(Vector3 &v) { return Vector3(x - v.x, y - v.y, z - v.z); };
    Vector3 operator*(float a) { return Vector3(x * a, y * a, z * a); };
    void operator+=(Vector3 &v) { x += v.x, y += v.y, z += v.z; };
    void operator-=(Vector3 &v) { x -= v.x, y -= v.y, z -= v.z; };
};

static const double PI = 3.1415926535;
static const int INF = 0x3f3f3f3f;

long int Factorial(int n) // 阶乘
{
    if (n == 0)
        return 1;
    long int result = n;
    for (n--; n > 0; n--)
        result *= n;
    return result;
}

long int CombinatorialNum(int i, int n) // 组合数Cni
{
    if (i > n)
        return 0;
    return Factorial(n) / (Factorial(i) * Factorial(n - i));
}

float BernsteinNum(int i, int n, float t) // 伯恩斯坦多项式
{
    return CombinatorialNum(i, n) * pow(t, i) * pow(1.0f - t, n - i);
}

float RadToDeg(float x) // 弧度转角度
{
    return x * 180.0f / PI;
}

float DegToRag(float x) // 角度转弧度
{
    return x * PI / 180.0f;
}

float ConstrainValue(float val, float min, float max) // 约束值在最小最大之间
{
    return val < min ? min : (val > max ? max : val);
}

void Rotate(float *x, float *y, float x0, float y0, float a) // 将二维点(x,y)以参考点(x0,y0)为圆心逆时针旋转a(弧度)
{
    float x1 = *x;
    float y1 = *y;
    *x = (x1 - x0) * cos(a) - (y1 - y0) * sin(a) + x0;
    *y = (y1 - y0) * cos(a) + (x1 - x0) * sin(a) + y0;
}
