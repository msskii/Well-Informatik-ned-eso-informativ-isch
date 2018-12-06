//
//  FileReader.cpp
//  Informatik
//
//  Created by Aaron Hodel on 21.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "FileReader.hpp"

filedata readFile(const char *filePath)
{
    FILE *f;

#if defined(__APPLE__) || defined(__linux__)
    f = fopen(filePath, "rb"); // Apple has the insecure version here
#else
    fopen_s(&f, filePath, "rb"); // Windows has secure
#endif

    if(f == nullptr)
    {
        ERROR("File not found");
        printf("\t%s\n", filePath);
        return {nullptr, 0}; // File not found
    }

    fseek(f, 0, SEEK_END);
    size_t fileSize = ftell(f);
    fseek(f, 0, SEEK_SET);
    uint8_t *data = (uint8_t *) malloc(fileSize);
    fread(data, 1, fileSize, f); // Read data

    fclose(f);
    
    return {data, fileSize};
}

void writeFile(const char *filePath, uint8_t *dataToWrite, int size)
{
    FILE *f;

#if defined(__APPLE__) || defined(__linux__)
    f = fopen(filePath, "wb"); // Apple has the insecure version here, <3 linux
#else
    fopen_s(&f, filePath, "wb"); // Windows has secure
#endif

    if(f == nullptr)
    {
        ERROR("File not found");
        printf("\t%s\n", filePath);
        return; // File not found
    }

    fwrite(dataToWrite, 1, size, f); // Write data
    
    fclose(f);
}

std::vector<std::string> listFiles(std::string dir) // Recursively finds all files inside a folder
{
    std::vector<std::string> files;
    
    DIR *dp;
    dp = opendir(dir.c_str());
    
    if(!dp) return files; // No directory found
    
    struct dirent *dirp;
    while((dirp = readdir(dp)))
    {
        if(dirp->d_type == DT_REG) files.push_back(std::string(dirp->d_name));
        else if(dirp->d_type == DT_DIR && strcmp(dirp->d_name, ".") && strcmp(dirp->d_name, ".."))
        {
            std::vector<std::string> subDirFiles = listFiles(dir + "/" + std::string(dirp->d_name));
            for(size_t i = 0; i < subDirFiles.size(); i++)
            {
                files.push_back(std::string(dirp->d_name) + "/" + subDirFiles[i]);
            }
        }
    }
    
    closedir(dp);
    
    return files;
}
