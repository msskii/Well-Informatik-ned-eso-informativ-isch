//
//  Logger.hpp
//  Informatik
//
//  Created by Aaron Hodel on 20.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef Logger_hpp
#define Logger_hpp

#define ERROR(msg) printf("[ERROR] %s\n", msg)
#define INFO(msg) printf("[INFO] %s\n", msg)
#define INFO_VAR(msg) printf("[INFO] %s", msg)

#define PRINT_INT(i) printf("%d\n", i);
#define PRINT_HEX(i) printf("%X\n", i);
#define PRINT_STRING(i) printf("%s\n", i);

#define NEW_LINE() printf("\n");

#endif /* Logger_hpp */
