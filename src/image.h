#ifndef IMAGE_H
#define IMAGE_H
#include <png.h>
#include <math.h>
#include <QMessageBox>
#include <QString>
#include <stdlib.h>
#include <QImage>
#include <QColor>

class image
{
private:
    int width, height;
    png_byte color_type;
    png_byte bit_depth;

    png_structp png_ptr;
    png_infop info_ptr;
    int number_of_passes;
    png_bytep *pixels_arr;
    bool exist = false;
    void pixelSetColor(int x, int y, QColor color);
    void invertPixelColor(int x, int y);
public:
    void Copy(image other);
    bool doesExists();
    image();
    ~image();
    QImage toQimg();
    png_bytep* getPixels_arr();
    int getWidth();
    int getHeight();
    int readPngFile(QString path);
    void writePngFile(QString path);
    void drawLine(int x1, int y1, int x2, int y2, QColor color, int thikness);
    void invertCircle(int x0, int y0, int r);
    int invertCircle(int x1, int y1, int x2, int y2);
    void cutImage(int x1, int y1, int x2, int y2);

};

#endif // IMAGE_H
