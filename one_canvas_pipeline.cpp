/*
 * One canvas pipeline.
 *
 * Input from terminal stream as text file. JPG output saved.
 *
 */


#include "./include/exhibit.h"
#include <string>
#include <vector>

using namespace exhibit;
using container = std::vector //or whatever else

int main(int argc, char** argv)
{
    // setup variables
    Parameters parameters;
    container<string> sources;
    container<Frame> frames;
    
    // process input from text file, text file via argv :-> update parameters and sources
    textProcessing(argv, parameters, sources);

    // photo sources :-> frame objects
    for (unsigned int k=0; k!=frames.size(); ++k) {
        Frame frame {sources.at(k), parameters};
        frames.push_back(frame);
        frames.at(k).make();
    }

    // frame objects :-> canvas
    Canvas canvas {frames, parameters};
    canvas.make();
    canvas.save("out.jpg");

    return 0;
}
