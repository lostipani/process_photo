#include "../include/exhibit.h"

using namespace std;

int main(int argc, char** argv)
{
    // Check input
    assert(argc>1);

    // Declarations
    exhibit::Parameters parameters;
    int nrows, ncols;
    string save_name;
    vector<string> sources;
    vector<exhibit::Frame> frames;
    exhibit::Canvas* canvas;


    // Parse input
    if (exhibit::utils::parser(argc, argv, parameters, nrows, ncols, sources, save_name))
        return 0;
    assert(sizeof(parameters)!=0);

    // Frame(s)
    for (std::size_t k=0; k!=sources.size(); ++k) {
        frames.push_back(exhibit::Frame {sources.at(k), parameters});
        frames.at(k).make();
    }

    // Canvas
    canvas = exhibit::Canvas::getCanvas(frames, parameters, nrows, ncols);
    canvas->make();
    canvas->save(save_name);

    return 0;
}
