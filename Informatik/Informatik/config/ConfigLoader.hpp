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
#include "../config.h"

class Language;

extern std::map<std::string, std::string> generateDefaultValues();

enum CONFIG_KEYS
{
    BUTTON_LEFT,
    BUTTON_RIGHT,
    BUTTON_UP,
    BUTTON_DOWN,
    
    BUTTON_INVENTORY,
    BUTTON_SHOOT,
    BUTTON_INTERACT,
    BUTTON_CHAT,
    
    BUTTON_CAST_1,
    BUTTON_CAST_2,
    BUTTON_CAST_3,
    BUTTON_CAST_4
};

extern int *GLOBAL_KEY_CONFIG;
extern Language *lang;

class ConfigLoader
{
protected:
    char *configFile = nullptr;
    filedata configData;
    
    void parseConfig();
    
    bool isGlobalConfig = true;
    virtual void testValues();
    
public:
    std::map<std::string, std::string> values;
    
    ConfigLoader(const char* file);
    ConfigLoader(const char* file, bool global);

    std::string get(const char* key);
    void set(const char* key, const char* value);
    
    int getInt(const char* key);
    void setInt(const char* key, int value);
    
    void reloadConfig();
    void save();
    void load();
};

#endif /* ConfigLoader_hpp */
