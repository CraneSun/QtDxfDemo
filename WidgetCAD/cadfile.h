#ifndef CADFILE_H
#define CADFILE_H
#include "dx_iface.h"
#include "dx_data.h"

//libdxfrw version

class __declspec(dllexport) CadFile
{
public:

    CadFile();

    struct COLORREF{
        public:
        COLORREF(unsigned char r, unsigned char g, unsigned char b){
            this->r = r;
            this->g = g;
            this->b = b;
        }
        unsigned char r = 0;
        unsigned char g = 0;
        unsigned char b = 0;
    };

    void usage();
    DRW::Version checkVersion(std::string param);
    int findIndexOfColorByEntity(DRW_Entity* ent);
    std::string findLayerNameByEntity(DRW_Entity* ent);
    bool readFile(std::string fileName);

    COLORREF getColorByIndex(int index);
    bool getFileState(){return badState;}
    dx_iface * getRawFile();
    dx_data * getRawData();
    std::string getFileType();

private:
    bool badState = false;
    dx_iface * rawFile = nullptr;
    dx_data * rawData = nullptr;
    std::string fileType = "DXF";
};

#endif // CADFILE_H
