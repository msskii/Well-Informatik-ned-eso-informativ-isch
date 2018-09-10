//
//  ConfigLoader.cpp
//  Informatik
//
//  Created by Aaron Hodel on 10.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "ConfigLoader.hpp"

std::map<std::string, std::string> generateDefaultValues()
{
    std::map<std::string, std::string> values;
    
    // For reference: https://wiki.libsdl.org/SDLKeycodeLookup
    
    values["button.inventory"] = std::to_string(SDLK_i);
    values["button.shoot"] = std::to_string(SDLK_e);

    return values;
}

void ConfigLoader::testValues()
{
    std::map<std::string, std::string> values = generateDefaultValues();
    bool needsSaving = false;
    for(auto it = values.begin(); it != values.end(); it++)
    {
        if(values[it->first].size() == 0)
        {
            values[it->first] = it->second; // Set default value
            needsSaving = true;
        }
    }
    
    if(needsSaving) save();
}

ConfigLoader::ConfigLoader(const char *path) : configFile(path)
{
    load();
}


void ConfigLoader::load()
{
    configData = readFile(configFile);
    if(configData.data == nullptr || configData.filesize == 0)
    {
        // File not found...
        values = generateDefaultValues();
        save();
    }
    parseConfig();
    testValues(); // Test if important values are missing... (& set Defaults if so)
}

void ConfigLoader::save()
{
    // TODO
    int fileLength = 0;
    for(auto iterator = values.begin(); iterator != values.end(); iterator++) fileLength += 2 + iterator->first.size() + iterator->second.size(); // first & second are key & value
    char *file = (char*) malloc(fileLength);
    int currentIndex = 0;
    for(auto iterator = values.begin(); iterator != values.end(); iterator++)
    {
        printf("Saving %s=%s\n", iterator->first.c_str(), iterator->second.c_str());
        size_t ni = iterator->first.size();
        memcpy(file + currentIndex, iterator->first.c_str(), ni);
        currentIndex += ni;
        file[currentIndex] = '=';
        ++currentIndex;
        ni = iterator->second.size();
        memcpy(file + currentIndex, iterator->second.c_str(), iterator->second.size());
        currentIndex += ni;
        file[currentIndex] = '\n';
        ++currentIndex;
    }
    writeFile(configFile, (uint8_t*) file, fileLength);
}

void ConfigLoader::reloadConfig()
{
    save();
    load();
}

void ConfigLoader::parseLine(const char* line)
{
}

void ConfigLoader::parseConfig()
{
    int linestart = 0;
    int lineend = 0;
    
    while(lineend < configData.filesize)
    {
        while(lineend < configData.filesize && configData.data[lineend] != '\n') ++lineend;
        
        int strlen = (lineend - linestart); // Actually plus one, but we remove '\n', so that doesnt matter
        char *line = (char*) malloc(strlen + 1);
        line[strlen] = 0; // Terminator
        memcpy(line, configData.data + linestart, strlen);
        
        std::string key, value;
        for(int i = 0; i < strlen; i++)
        {
            if(line[i] == '=')
            {
                key = std::string(line).substr(0, i);
                value = std::string(line).substr(i + 1, strlen);
                break;
            }
        }
        
        if(key.size() > 0) values[key] = value;
        
        linestart = lineend + 1;
        ++lineend;
    }
}

std::string ConfigLoader::get(const char *key)
{
    return values[key];
}

void ConfigLoader::set(const char *key, const char *value)
{
    values[key] = std::string(value);
}

int ConfigLoader::getInt(const char *key)
{
    std::string value = values[key];
    return atoi(value.c_str());
}

void ConfigLoader::setInt(const char *key, int value)
{
    values[key] = std::to_string(value);
}
