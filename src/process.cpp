#include "../include/exhibit.h"

int main(int argc, char** argv)
{
    exhibit::Frame frame {argv[1]};
    frame.info();

    frame.resizePhoto(1080, 16.0/9.0);
    frame.info();

    return 0;
}
