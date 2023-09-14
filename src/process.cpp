#include "../include/exhibit.h"

int main(int argc, char** argv)
{

    exhibit::Parameters parameters{};
    parameters.frameAspectRatio = 1.4;
    parameters.photo2frameRatio = 30./52.;
    parameters.frame2canvasRatio = 0.5;
    parameters.frameThickRatio = std::vector<float> (4, 3.5/52.);
    parameters.canvasBase = 1920;
    parameters.frameColor = std::vector<int> {10, 10, 10};
    parameters.passpartoutColor = std::vector<int> {250, 250, 250};

    exhibit::Frame frame {argv[1], parameters};
    frame.info();
    frame.make();
    frame.info();
    frame.save("test.jpg");

    return 0;
}
