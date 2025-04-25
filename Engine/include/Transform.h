// Transform.h
#pragma once
#include <cmath>

struct Mat3 {
    float m[3][3];

    static Mat3 Translate(float tx, float ty) {
        return Mat3{ {
          {1, 0, tx},
          {0, 1, ty},
          {0, 0, 1 }
        } };
    }

    static Mat3 Rotate(float radians) {
        float c = std::cos(radians), s = std::sin(radians);
        return Mat3{ {
          { c, -s, 0 },
          { s,  c, 0 },
          { 0,  0, 1 }
        } };
    }

    static Mat3 Scale(float sx, float sy) {
        return Mat3{ {
          { sx,  0,  0 },
          {  0, sy,  0 },
          {  0,  0,  1 }
        } };
    }

    Mat3 operator*(const Mat3& o) const {
        Mat3 r{};
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                r.m[i][j] = m[i][0] * o.m[0][j]
                + m[i][1] * o.m[1][j]
                + m[i][2] * o.m[2][j];
        return r;
    }
};

// Add this so M * Vector2 works:
inline Vector2 operator*(const Mat3& M, const Vector2& v) {
    return {
      M.m[0][0] * v.x + M.m[0][1] * v.y + M.m[0][2],
      M.m[1][0] * v.x + M.m[1][1] * v.y + M.m[1][2]
    };
}
