#ifndef TEST_H
#define TEST_H

#include "../tetris.h"
#include "../backend.h"
#include "../frontend.h"

#include "check.h"

#define SUCCESS 0
#define FAILURE 1


Suite * test_frontend(void);
Suite * test_backend(void);




#endif