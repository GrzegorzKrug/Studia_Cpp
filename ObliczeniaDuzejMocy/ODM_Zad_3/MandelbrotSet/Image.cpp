#include "Image.h"

Image::Image(std::string fileName, int width, int height, int maxColor)
    : width(width), height(height), maxval(maxColor)
{
    // open the file
    file = openFile(fileName);

    // create file header string
    this->fileHeader = "P3 "       
        + std::to_string(width)    
        + " "                      
        + std::to_string(height)   
        + " "                      
        + std::to_string(maxval)   
        + '\n';                    

    // save the header to the file
    file << fileHeader;

    // allocate memory
    content = new Pixel[width * height];
}

void Image::saveFile()
{
    for (int i = 0; i < width * height; i++)
    {
        file << content[i].toString() << (i % width == 0 ? '\n' : ' ');
    }
}

void Image::setPixel(int x, int y, int r, int g, int b)
{
    content[x + y * width] = Pixel(r, g, b);
}

Image::~Image() 
{ 
    file.close(); 
    delete[] content;
}

std::ofstream Image::openFile(std::string fileName)
{
    std::ofstream file;

    // check file extension in lower case
    std::string extension;
    if (fileName.size() > 4)
    {
        extension = fileName.substr(fileName.size() - 5, 4);
        std::transform(extension.begin(), extension.end(), extension.begin(),
            [](char c) { return std::tolower(c); }
        );
    }
    else
        extension = fileName;

    // if not included in file name fix it
    if (extension != ".ppm")
        fileName += ".ppm";

    // open the file
    file.open(fileName, std::ofstream::out);

    if (!file)
    {
        std::cout << "Cannot open file: " << fileName << std::endl;
        exit(0);
    }

    return file;
}
