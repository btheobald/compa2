#ifndef STORE_DEF_GUARD
#define STORE_DEF_GUARD

#include <stdint.h>

#include "body.h"

// Body array management functions
// Allocate memory for body array, return base pointer
body** allocateBodyArray(int cbc);
// Free memory used by body storage array
int freeBodyArray(body** arrayBase, int cbc);

#endif//STORE_DEF_GUARD
