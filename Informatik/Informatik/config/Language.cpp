//
//  Language.cpp
//  Informatik
//
//  Created by Aaron Hodel on 03.12.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Language.hpp"

Language::Language(const char* path) : loader(GET_FILE_PATH(LANGUAGE_PATH, path + ".lang"), false)
{
    printf("Itemname for infinity: %s\n", loader.get("item.infinity.name").c_str());
}

std::string Language::translate(const char *key)
{
    return translate(std::string(key));
}

std::string Language::translate(std::string key)
{
    std::string val = loader.get(key.c_str());
    return val == "" ? key : val;
}
