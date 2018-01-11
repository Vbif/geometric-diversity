#include "stdafx.h"

#include "WireFrameRender.h"

namespace Render {

void DrawWireframeRect(const FRect& rect, float width)
{
    std::array<FPoint, 4> points;
    points[0] = rect.LeftBottom();
    points[1] = rect.LeftTop();
    points[2] = rect.RightTop();
    points[3] = rect.RightBottom();

    FPoint prev = points.back();
    for (size_t i = 0; i < points.size(); i++) {
        DrawWireframeLine(prev, points[i], width);
        prev = points[i];
    }
}

// Скопировано из интернета и вырезано лишнее
// https://www.codeproject.com/Articles/199525/Drawing-nearly-perfect-D-line-segments-in-OpenGL
void CalcTriangles(const FPoint& p1, const FPoint& p2, float w, FPoint* out)
{
    double t;
    double R;
    double f = w - static_cast<int>(w);
    float A = 1.0f;

    //determine parameters t,R
    /*   */ if (w >= 0.0 && w < 1.0) {
        t = 0.05;
        R = 0.48 + 0.32 * f;
    } else if (w >= 1.0 && w < 2.0) {
        t = 0.05 + f * 0.33;
        R = 0.768 + 0.312 * f;
    } else if (w >= 2.0 && w < 3.0) {
        t = 0.38 + f * 0.58;
        R = 1.08;
    } else if (w >= 3.0 && w < 4.0) {
        t = 0.96 + f * 0.48;
        R = 1.08;
    } else if (w >= 4.0 && w < 5.0) {
        t = 1.44 + f * 0.46;
        R = 1.08;
    } else if (w >= 5.0 && w < 6.0) {
        t = 1.9 + f * 0.6;
        R = 1.08;
    } else if (w >= 6.0) {
        double ff = w - 6.0;
        t = 2.5 + ff * 0.50;
        R = 1.08;
    }

    //determine angle of the line to horizontal
    float tx = 0, ty = 0; //core thinkness of a line
    float Rx = 0, Ry = 0; //fading edge of a line
    float cx = 0, cy = 0; //cap of a line
    float ALW = 0.01;
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;

    if (std::abs(dx) < ALW) {
        //vertical
        tx = t;
        ty = 0;
        Rx = R;
        Ry = 0;
        if (w > 0.0 && w < 1.0)
            tx *= 8;
        else if (w == 1.0)
            tx *= 10;
    } else if (std::abs(dy) < ALW) {
        //horizontal
        tx = 0;
        ty = t;
        Rx = 0;
        Ry = R;
        if (w > 0.0 && w < 1.0)
            ty *= 8;
        else if (w == 1.0)
            ty *= 10;
    } else {
        if (w < 3) { //approximate to make things even faster
            double m = dy / dx;
            //and calculate tx,ty,Rx,Ry
            if (m > -0.4142 && m <= 0.4142) {
                // -22.5< angle <= 22.5, approximate to 0 (degree)
                tx = t * 0.1;
                ty = t;
                Rx = R * 0.6;
                Ry = R;
            } else if (m > 0.4142 && m <= 2.4142) {
                // 22.5< angle <= 67.5, approximate to 45 (degree)
                tx = t * -0.7071;
                ty = t * 0.7071;
                Rx = R * -0.7071;
                Ry = R * 0.7071;
            } else if (m > 2.4142 || m <= -2.4142) {
                // 67.5 < angle <=112.5, approximate to 90 (degree)
                tx = t;
                ty = t * 0.1;
                Rx = R;
                Ry = R * 0.6;
            } else if (m > -2.4142 && m < -0.4142) {
                // 112.5 < angle < 157.5, approximate to 135 (degree)
                tx = t * 0.7071;
                ty = t * 0.7071;
                Rx = R * 0.7071;
                Ry = R * 0.7071;
            } else {
                // error in determining angle
                //printf( "error in determining angle: m=%.4f\n",m);
            }
        } else { //calculate to exact
            dx = p1.y - p2.y;
            dy = p2.x - p1.x;
            float L = math::sqrt(dx * dx + dy * dy);
            dx /= L;
            dy /= L;
            cx = -0.6 * dy;
            cy = 0.6 * dx;
            tx = t * dx;
            ty = t * dy;
            Rx = R * dx;
            Ry = R * dy;
        }
    }

    //draw the line by triangle strip
    float line_vertex[] = {
        //x1 - tx - Rx, y1 - ty - Ry, //fading edge1
        //x2 - tx - Rx, y2 - ty - Ry,
        p1.x - tx, p1.y - ty, //core
        p2.x - tx, p2.y - ty,
        p1.x + tx, p1.y + ty,
        p2.x + tx, p2.y + ty,
        //x1 + tx + Rx, y1 + ty + Ry, //fading edge2
        //x2 + tx + Rx, y2 + ty + Ry
    };

    for (size_t i = 0; i < 4; i++)
        out[i] = FPoint(line_vertex[i * 2], line_vertex[i * 2 + 1]);
}

void DrawWireframeLine(const FPoint& p0, const FPoint& p1, float width)
{
    FPoint v[4];
    CalcTriangles(p0, p1, width, v);

    Render::DrawTriangle(v[0], v[1], v[2]);
    Render::DrawTriangle(v[1], v[2], v[3]);

    //Render::PushColor c(Color::BLUE);
    //Render::DrawLine()
}
}
