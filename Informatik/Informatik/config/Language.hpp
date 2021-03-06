//
//  Language.hpp
//  Informatik
//
//  Created by Aaron Hodel on 03.12.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef Language_hpp
#define Language_hpp

#include "ConfigLoader.hpp"

class Language
{
private:
    ConfigLoader loader;
public:
    Language(const char *filepath);
    std::string translate(const char *key);
    std::string translate(std::string key);
};

#endif /* Language_hpp */
