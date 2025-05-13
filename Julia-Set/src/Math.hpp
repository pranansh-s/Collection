#pragma once

struct Vector2f{
    Vector2f():x(0.0f), y(0.0f){}
    Vector2f(float posX, float posY):x(posX), y(posY){}

    float x, y;
};

struct Color{
    Color():r(0), g(0), b(0), a(0){}
    Color(int red, int green, int blue, int ap):r{red}, g(green), b(blue), a(ap){}

    int r, g, b, a;
};