#include "cadfile.h"
#include "../third_party/magic_enum.hpp"
#include <iostream>

void CadFile::usage()
{
    std::cout << "Usage: " << std::endl;
    std::cout << "   dwg2dxf <input> [-b] <-version> <output>" << std::endl << std::endl;
    std::cout << "   input      existing file to convert" << std::endl;
    std::cout << "   -b         optional, sets output as binary dxf" << std::endl;
    std::cout << "   -B         optional, batch mode reads a text file whit a list of full path input" << std::endl;
    std::cout << "               files and saves with the same name in the indicated folder as output" << std::endl;
    std::cout << "   -y -Y      optional, Warning! if output dxf exist overwrite without ask" << std::endl;
    std::cout << "   -version   version output of dxf file" << std::endl;
    std::cout << "   output     output file name" << std::endl << std::endl;
    std::cout << "     version can be:" << std::endl;
    std::cout << "        -R12   dxf release 12 version" << std::endl;
    std::cout << "        -v2000 dxf version 2000" << std::endl;
    std::cout << "        -v2004 dxf version 2004" << std::endl;
    std::cout << "        -v2007 dxf version 2007" << std::endl;
    std::cout << "        -v2010 dxf version 2010" << std::endl;
}


DRW::Version CadFile::checkVersion(std::string param){
    if (param == "-R12")
        return DRW::AC1009;
    else if (param == "-v2000")
        return DRW::AC1015;
    else if (param == "-v2004")
        return DRW::AC1018;
    else if (param == "-v2007")
        return DRW::AC1021;
    else if (param == "-v2010")
        return DRW::AC1024;
    return DRW::UNKNOWNV;
}


int CadFile::findIndexOfColorByEntity(DRW_Entity* ent)
{
    if(256 != ent->color)
        return ent->color;
    for (auto iter = rawData->layers.begin();iter != rawData->layers.end(); iter++)
    {
        if(ent->layer == iter->name)
            return iter->color;
    }
    return 255;
}

std::string CadFile::findLayerNameByEntity(DRW_Entity* ent)
{
    return ent->layer;
}

bool CadFile::readFile(std::string fileName)
{
    bool debug = false;

    dx_iface * inFile = new dx_iface;
    dx_data * data = new dx_data;
    badState = inFile->fileImport( fileName, data, debug);
    if (!badState) {
        delete inFile;
        delete data;
        return false;
    }
    if(nullptr != rawFile){
        delete rawFile;
    }
    if(nullptr != rawData){
        delete rawData;
    }
    rawFile = inFile;
    rawData = data;
    return true;
}


dx_iface * CadFile::getRawFile()
{
    return rawFile;
}

dx_data * CadFile::getRawData()
{
    return rawData;
}

std::string CadFile::getFileType()
{
    return fileType;
}

CadFile::COLORREF CadFile::getColorByIndex(int index)
{
    switch(index){
        case 0:
            return COLORREF(0,0,0);
        case 1:
            return COLORREF(255,0,0);
        case 2:
            return COLORREF(255,255,0);
        case 3:
            return COLORREF(0,255,0);
        case 4:
            return COLORREF(0,255,255);
        case 5:
            return COLORREF(0,0,255);
        case 6:
            return COLORREF(255,0,255);
        case 7:
            return COLORREF(255,255,255);
        case 8:
            return COLORREF(65,65,65);
        case 9:
            return COLORREF(128,128,128);
        case 10:
            return COLORREF(255,0,0);
        case 11:
            return COLORREF(255,255,255);
        case 12:
            return COLORREF(255,170,170);
        case 13:
            return COLORREF(189,0,0);
        case 14:
            return COLORREF(255,126,126);
        default:
            return COLORREF(255,255,255);
    }
}

CadFile::CadFile() {}
