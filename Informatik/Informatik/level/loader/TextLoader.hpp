//
//  TextLoader.hpp
//  Informatik
//
//  Created by Aaron Hodel on 27.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef TextLoader_hpp
#define TextLoader_hpp

#include <vector>
#include "../../util/FileReader.hpp"

namespace Loader
{
    class TextLoader
    {
    private:
        std::vector<std::string> loadedText;
        
    public:
        TextLoader(const char *path);
    };
}

#endif /* TextLoader_hpp */
