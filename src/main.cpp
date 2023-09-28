#include "../include/exhibit.h"
#include <cassert>
#include <new>

using namespace std;

int main(int argc, char** argv)
{
    // check input
    assert(argc>1);

    // instantiate Parameters
    exhibit::Parameters parameters;
     parameters.canvasAspectRatio = 16./9.;
    parameters.frameAspectRatio = 1.4;
    parameters.hspaceRatio = 5./52.;
    parameters.vspaceRatio = 5./52.;
    parameters.frame2canvasRatio = 0.3;
    parameters.photo2frameRatio = 30./52.;
    parameters.frameThickRatio = vector<float> (4, 3.5/52.);
     parameters.canvasBase = 1920;
     parameters.canvasColor = vector<int> {255, 255, 255};
    parameters.frameColor = vector<int> {10, 10, 10};
    parameters.passpartoutColor = vector<int> {250, 250, 250};


    // instantiate container of Frame(s)
    vector<exhibit::Frame> frames;
    for (int k=0; k!=argc-1; ++k) 
        frames.push_back(exhibit::Frame {argv[k+1], parameters});
    assert(frames.size()==argc-1);


    // instantiate Canvas
    exhibit::Canvas *canvas = exhibit::Canvas::getCanvas(frames, parameters, 1, 3);
    canvas->make();
    canvas->save("test.jpg");

    return 0;
}
