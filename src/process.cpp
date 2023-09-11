#include "../include/frame.h"

int main(int argc, char** argv)
{
    Picture pict {argv[1]};
    pict.info();

    return 0;
}
