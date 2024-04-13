#pragma once

class DataPoint {
private:
    double x;
    double y;
    double z;
    int label;

public:
    DataPoint() : x(0), y(0), z(0), label(-1) {}
    DataPoint(double x, double y, double z, int label) : x(x), y(y), z(z), label(label) {}

    // Getters
    double getX() const { return x; }
    double getY() const { return y; }
    double getZ() const { return z; }
    int getLabel() const { return label; }

    // Setters
    void setX(double value) { x = value; }
    void setY(double value) { y = value; }
    void setZ(double value) { z = value; }
    void setLabel(int value) { label = value; }
};
