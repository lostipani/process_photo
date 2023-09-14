#include "../include/exhibit.h"

struct Parameters
{
    float canvasAspectRatio; // height/base
    float pictureAspectRatio; // height/base
    float hspaceRatio; // picture's base/horiz. spacing
    float vspaceRatio; // picture's base/vert. spacing
    float picture2canvasRatio; // picture's base/canvas' base
    int canvasBase; // [px]
    cv::Scalar canvasColor;
};

