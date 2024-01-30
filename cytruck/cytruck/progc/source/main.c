#include <stdio.h>
#include <string.h>

#include "../header/d1.h"
#include "../header/d2.h"
#include "../header/l.h"
#include "../header/t.h"
#include "../header/s.h"

int main(int argc, char const *argv[])
{
    if (strcmp(argv[2], "-l") == 0)
    {
        l(argv[1]);
    }
    else if (strcmp(argv[2], "-t") == 0)
    {
    }
    else
    {
    }
}
