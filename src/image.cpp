#include "image.h"

image::image() {}

image::~image() {}

int image::readPngFile(QString path){
    std::string tmp_str = path.toStdString();
    const char *fileName = tmp_str.c_str();

    int headerLen = 8;
    char header[headerLen];

    FILE *file = fopen(fileName, "rb");
    if(!file){
        QMessageBox::critical(nullptr, "Ошбика", "Файл с таким именем не найден или путь к файлу содержит недопустимые символы");
        return 1;
    }
    fread(header, sizeof(char), headerLen, file);

    if(png_sig_cmp((png_const_bytep)header, 0, headerLen)){
        QMessageBox::critical(nullptr, "Ошибка", "Файл не явлется png");
        return 1;
    }

    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if(!png_ptr){
        QMessageBox::critical(nullptr, "Ошибка", "ошибка в создании png_ptr");
        return 1;
    }

    info_ptr = png_create_info_struct(png_ptr);
    if(!info_ptr){
        png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
        fclose(file);
        QMessageBox::critical(nullptr, "Ошибка", "Ошибка в создании info_ptr");
        return 1;
    }

    if(setjmp(png_jmpbuf(png_ptr))){
        png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
        fclose(file);
        QMessageBox::critical(nullptr, "Ошибка", "Не удалось получить информацию об изображении");
        return 1;
    }

    png_init_io(png_ptr, file); // Initialize the default input/output functions
    png_set_sig_bytes(png_ptr, headerLen);

    png_read_info(png_ptr, info_ptr);

    //проверяем что файл png RGBA
    if (png_get_color_type(png_ptr, info_ptr) != PNG_COLOR_TYPE_RGB_ALPHA){
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);//очистка структуры
        fclose(file);

        QMessageBox::critical(nullptr,"Ошибка","У этого png файла тип цвета не RGBA\n\nДанная программа работает только с файлами png  , с типом цвета  RGBA!!!");
        return 1;
    }


    width = png_get_image_width(png_ptr, info_ptr);
    height = png_get_image_height(png_ptr, info_ptr);
    color_type = png_get_color_type(png_ptr, info_ptr);
    bit_depth = png_get_bit_depth(png_ptr, info_ptr);

    number_of_passes = png_set_interlace_handling(png_ptr);
    png_read_update_info(png_ptr, info_ptr);

    if (setjmp(png_jmpbuf(png_ptr))){
        png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
        fclose(file);
        QMessageBox::critical(nullptr, "Ошибка", "Не удалось считать изображение");
        return 1;
    }

    pixels_arr = (png_bytep*) malloc(sizeof(png_bytep) * height);
    for(int y = 0; y < height; y++)
        pixels_arr[y] = (png_byte *) malloc(png_get_rowbytes(png_ptr, info_ptr));

    png_read_image(png_ptr, pixels_arr);

    fclose(file);
    exist = true;
    return 0;
}

bool image::doesExists(){
    return exist;
}

void image::writePngFile(QString path){
    std::string tmp_str =   path.toStdString();
    const char *fileName = tmp_str.c_str();

    //открываем файл
    FILE *file = fopen(fileName, "wb");
    if(!file){
        QMessageBox::critical(nullptr, "Ошбика", "Файл с таким именем не найден или путь к файлу содержит недопустимые символы");
        return;
    }

    //выделяем память
    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if(!png_ptr){
        QMessageBox::critical(nullptr, "Ошибка", "ошибка в создании png_ptr");
        return;
    }

    info_ptr = png_create_info_struct(png_ptr);
    if(!info_ptr){
        png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
        fclose(file);
        QMessageBox::critical(nullptr, "Ошибка", "Ошибка в создании info_ptr");
        return;
    }


    if (setjmp(png_jmpbuf(png_ptr))){
        png_destroy_write_struct(&png_ptr, &info_ptr);
        fclose(file);
        QMessageBox::critical(nullptr, "Ошибка", "Не удалось записать данные о файле");
        return;
    }

    png_init_io(png_ptr, file);

    if (setjmp(png_jmpbuf(png_ptr))){
        png_destroy_write_struct(&png_ptr, &info_ptr);
        fclose(file);
        QMessageBox::critical(nullptr, "Ошибка", "Не удалось записать header");
        return;
    }

    png_set_IHDR(png_ptr, info_ptr, width, height,
                 bit_depth, color_type, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
    png_write_info(png_ptr, info_ptr);

    if (setjmp(png_jmpbuf(png_ptr))){
        png_destroy_write_struct(&png_ptr, &info_ptr);
        fclose(file);
        QMessageBox::critical(nullptr, "Ошибка", "Не удалось записать изображение");
        //return;
    }

    png_write_image(png_ptr, pixels_arr);

    if (setjmp(png_jmpbuf(png_ptr))){
        png_destroy_write_struct(&png_ptr, &info_ptr);
        fclose(file);
        QMessageBox::critical(nullptr, "Ошибка", "Не удалось записать конец файла");
    }

    png_write_end(png_ptr, NULL);

    for(int y = 0; y < height; y++){
        free(pixels_arr[y]);
    }

    fclose(file);
}

void image::pixelSetColor(int x, int y, QColor color){ // возвращает 0 если всё хорошо, 1 если введены неверные координаты пикселя

    if (x >= 0 && x < width && y >= 0 && y < height){ // проверяем правильно ли введены данные о пикселе
        pixels_arr[y][x*4] = color.red();
        pixels_arr[y][x*4 + 1] = color.green();
        pixels_arr[y][x*4 + 2] = color.blue();
        pixels_arr[y][x*4 + 3] = color.alpha();
    }
}


QImage image::toQimg(){
    QImage imgForShow(width, height, QImage::Format_RGBA8888);
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            imgForShow.setPixel(i, j, qRgba(pixels_arr[j][i * 4], pixels_arr[j][i * 4 + 1], pixels_arr[j][i * 4 + 2], pixels_arr[j][i * 4 + 3]));
        }
    }

    return imgForShow;
}

void image::drawLine(int x1, int y1, int x2, int y2, QColor color, int thikness){
    int topThik = trunc((float)(thikness - 1) / 2);
    int botThick = round((float)(thikness - 1) / 2);


    if(x1 == x2){ // вертикальная линия
        if(y2 > y1){
            for(int y = y1; y < y2; y++)
                for(int x = x1 - botThick; x <= x1 + topThik; x++)
                    pixelSetColor(x, y, color);

        }else{
            for(int y = y2; y < y1; y++)
                for(int x = x1 - botThick; x <= x1 + topThik; x++)
                    pixelSetColor(x, y , color);

        }
    }else{ // иначе находим tg
        float tg = ((float)(y2 - y1)) / (x2 - x1); // a = tg
        float b = y1 - tg * x1;
        if(abs(tg) <= 1){
            if(x2 > x1){//y = a*x
                for(int x = x1; x <= x2; x++){
                    int yBase = round(tg * x + b); // находим значение по "графику"
                    for(int y = yBase - botThick; y <= yBase + topThik; y++) // создаем толщину
                        pixelSetColor(x, y, color);
                }
            }else{
                for(int x = x2; x <= x1; x++){
                    int yBase = round(tg * x + b); // находим значение по "графику"
                    for(int y = yBase - botThick; y <= yBase + topThik; y++) // создаем толщину
                        pixelSetColor(x, y, color);
                }
            }
        }else{
            if(y2 > y1){
                for(int y = y1; y <= y2; y++){
                    int xBase = round((y - b) / tg);
                    for(int x = xBase - botThick; x <= xBase + topThik; x++)
                        pixelSetColor(x, y, color);
                }
            }else{
                for(int y = y2; y <= y1; y++){
                    int xBase = round((y - b) / tg);
                    for(int x = xBase - botThick; x <= xBase + topThik; x++)
                        pixelSetColor(x, y, color);
                }
            }
        }
    }
}

void image::invertPixelColor(int x, int y){

    if (x >= 0 && x < width && y >= 0 && y < height){ // проверяем правильно ли введены данные о пикселе
        pixels_arr[y][x*4] = 255 - pixels_arr[y][x*4];
        pixels_arr[y][x*4 + 1] = 255 - pixels_arr[y][x*4 + 1];
        pixels_arr[y][x*4 + 2] = 255 - pixels_arr[y][x*4 + 2];
    }
}

void image::invertCircle(int x0, int y0, int r){

    for(int x = x0 - r; x <= x0 + r; x++){
        int y = y0;
        while(pow(x - x0, 2) + pow(y - y0, 2) <= pow(r, 2)){
            invertPixelColor(x, y);
            y++;
        }
        y = y0 - 1;
        while(pow(x - x0, 2) + pow(y - y0, 2) <= pow(r, 2)){
            invertPixelColor(x, y);
            y--;
        }
    }

}

int image::getWidth(){
    return width;
}

int image::getHeight(){
    return height;
}

png_bytep* image::getPixels_arr(){
    return pixels_arr;
}

int image::invertCircle(int x1, int y1, int x2, int y2){
    if(abs(x1 - x2) == abs(y1 - y2)){
        int x0 = ceil(float(x2 + x1) / 2);
        int y0 = ceil(float(y2 + y1) / 2);
        int r = floor(float(abs(x2 - x1)) / 2);
        invertCircle(x0, y0, r);
        return 0;
    }

    return 1;
}

void image::cutImage(int x1, int y1, int x2, int y2){

    if(x1 < 0)
        x1 = 0;
    if(y1 < 0)
        y1 = 0;
    if(x2 > width)
        x2 = width - 1;
    if(y2 > height)
        y2 = height - 1;

    png_bytep *tmp = (png_bytep*)malloc(sizeof(png_bytep) * (y2 - y1 + 1));
    for(int i = 0; i < y2 - y1 + 1; i++){
        tmp[i] = (png_byte*)malloc(sizeof(png_byte) * (x2 - x1 + 1) * 4);
    }



    for(int y = 0; y < y2 - y1 + 1; y++){
        for(int x = 0; x < (x2 - x1 + 1) * 4; x++){
            tmp[y][x] = pixels_arr[y + y1][x + x1 * 4];
        }
    }

    for(int y = 0; y < height; y++)
        free(pixels_arr[y]);
    free(pixels_arr);

    height = y2 - y1 + 1;
    width = x2 - x1 + 1;

    pixels_arr = tmp;
}

void image::Copy(image other){
    width = other.width;
    height = other.height;
    color_type = other.color_type;
    bit_depth = other.bit_depth;
    png_ptr = other.png_ptr;
    info_ptr = other.info_ptr;
    number_of_passes = other.number_of_passes;
    exist = other.exist;

    pixels_arr = (png_bytep *) malloc(sizeof(png_bytep) * height);
    for (int i = 0; i < height; i++)
        pixels_arr[i] = (png_byte *) malloc(sizeof(png_byte) * width * 4);// так как канолов 4


    for (int y = 0; y < height; y++) {
        for (int x = 0; x < (width*4); x++) {//4 - количество каналов (в RGBA их 4)
            pixels_arr[y][x] = other.pixels_arr[y][x];
        }
    }
}
