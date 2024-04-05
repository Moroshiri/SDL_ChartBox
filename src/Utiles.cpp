#include "Utiles.hpp"
#include <fstream>

FPoint* loadDataCSV(const char* file, unsigned int* count)
{
    FPoint* out;
    std::fstream fs;
    fs.open(file, std::ios::in | std::ios::binary);
    if(fs.fail()) return nullptr;
    
    // Count file length
    fs.seekg(0, fs.end);
    unsigned int fileLength = 1 + (unsigned int)fs.tellg();
    fs.seekg(0, fs.beg);

    if(fileLength <= 1)
    {
        fs.close();
        return nullptr;
    }

    char* fileContent = new char[fileLength];
    fileContent = (char*)memset(fileContent, 0, fileLength);
    fs.read(fileContent, fileLength);

    fs.close();

    // Count lines
    unsigned int lines = 1;
    for(unsigned int n = 0; n < fileLength; n++)
    {    
        if(fileContent[n] == '\n') lines++;
    }
    *count = lines;

    // Allocate memory for points
    // out = (FPoint*)malloc(sizeof(FPoint[lines]));
    out = new FPoint[lines];

    // Read data
    const int bufSize = 64;
    char* buf = new char[bufSize];
    bool endOfFile = false;
    char* c = fileContent;
    int n = 0;
    do
    {
        float x, y;
        buf = (char*)memset(buf, 0, bufSize);
        for(int m = 0; m < bufSize; m++)
        {
            // Check for current position, if file ends, leave the loop
            if(c >= fileContent + fileLength)
            {
                endOfFile = true;
                break;
            }

            // If it's end of value, leave the loop
            if(*c == ',' || *c == '\r' || *c == '\n') break;

            buf[m] = *c;
            c++;
        }

        if(*c == ',')
        {
            x = (float)atof(buf);
        }
        if(*c == '\r' || *c == '\n' || endOfFile)
        {
            y = (float)atof(buf);

            out[n] = FPoint(x, y);
            n++;
        }

        // If file ends, leave the loop
        if(endOfFile) break;

        // One extra shift after \r for avoid \n
        if(*c == '\r') c++;
        c++;
    } while(n < lines);

    return out;
}

int SDL_SetRenderDrawColor(SDL_Renderer* rend, Color color)
{
    return SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);
}

float mean(float* values, unsigned int count)
{
    if(values == nullptr || count == 0) return 0.0;

    float sum = 0;
    for(unsigned int n = 0; n < count; n++)
        sum += values[n];

    return sum / count;
}

FPoint mean(FPoint* pts, unsigned int count)
{
    if(pts == nullptr || count == 0) return FPoint();

    float xSum = 0;
    float ySum = 0;
    for(unsigned int n = 0; n < count; n++)
    {
        xSum += pts[n].x;
        ySum += pts[n].y;
    }

    return FPoint(xSum / count, ySum / count);
}
