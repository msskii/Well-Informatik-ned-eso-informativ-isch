//
//  ConfigLoader.hpp
//  Informatik
//
//  Created by Aaron Hodel on 10.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef ConfigLoader_hpp
#define ConfigLoader_hpp

#include "../util/FileReader.hpp"
#include "../util/SDL_Util.hpp"
#include <map>

extern std::map<std::string, std::string> generateDefaultValues();

class ConfigLoader
{
private:
    const char *configFile = nullptr;
    filedata configData;
    
    std::map<std::string, std::string> values;
    
    void parseLine(const char* line);
    void parseConfig();
    
    void testValues();
    
public:
    ConfigLoader(const char* file);
    
    std::string get(const char* key);
    void set(const char* key, const char* value);
    
    int getInt(const char* key);
    void setInt(const char* key, int value);
    
    void reloadConfig();
    void save();
    void load();
};

#endif /* ConfigLoader_hpp */
