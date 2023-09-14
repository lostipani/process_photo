#include "./exhibit.h"

using Coord = std::pair<int, int>;

class Canvas
{

    public:
        Canvas(int, int);
        void make();

    private:
        std::vector<exhibit::Frame> frames;
        cv::Mat dst;
        int nrows;
        int ncols;
        Parameters params;
        Coord getOrigin(int, int);

};


Canvas::Canvas(Parameters params_, int nrows_, int ncols_):
    params{params_}, nrows{nrows_}, ncols{cols_}
{
    this->src = cv::Mat {cv::Size {params.canvasBase, std::round(params.canvasBase/params.canvasAspectRatio)}, 
                         16, // type 16 == CV_8UC3 i.e. 8 bit x 3 channels BGR
                         params.canvasColor};
}

Coord Canvas::getOrigin(int row, int col)
{
    Coord origin;
    
    // aliases for the sake of semplicity in algebra
    int& A = params.canvasBase;
    float& r = params.canvasAspectRatio;
    float& p = params.pictureAspectRatio;
    float& h = params.hspaceRatio;
    float& v = params.vspaceRatio;
    float& p2c = params.picture2canvasRatio;

    origin.first = std::round( (A/2)*(1 - ncols*p2c - (ncols-1)*p2c*h) + (col-1)*A*p2c*(1 + h) );
    origin.second = std::round( (A/2)*(r - nrows*p*p2c - (nrows-1)*p2c*v) + (row-1)*A*p2c*(p + v) );

    return origin;

}




void Canvas::makeSeries()
{
    cv::Rect mask;
    std::size_t k;

    for (std::size_t i=0; i!=nrows; ++i) {
        for (std::size_t j=0; j!=ncols; ++j) {
            k = i*nrows + j; // flattening of matrix
            this->frames.at(k).resize(std::round(this->params.canvasBase*this->params.frame2canvasRatio));
            mask = cv::Rect {this->getOrigin(i,j), this->frames.at(k).size}; // TBI in exhibit::Frame as public method
            this->frames.at(k).cv_copyTo(cv::Mat {this->dst, mask}); // TBI in exhibit::Frame as public method wrapping cv::copyTo()
        }
    }

}



