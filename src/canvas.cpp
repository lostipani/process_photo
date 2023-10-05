#include "../include/exhibit.h"


/* constructors */

exhibit::Canvas::~Canvas()
{
}


exhibit::Matrix::Matrix(const std::vector<exhibit::Frame>& frames_, const exhibit::Parameters& params_, int nrows_, int ncols_)
{
    this->frames = frames_;
    this->params = params_;
    this->verbose = true;
    this->nrows = nrows_;
    this->ncols = ncols_;

    assert(frames.size() == nrows*ncols);

    int canvasHeight = static_cast<int>(std::round(params.canvasBase/params.canvasAspectRatio));
    Size_t canvas_size(params.canvasBase, canvasHeight);
    Scalar_t canvas_color = utils::rgb2bgr(params.canvasColor); 
    this->dst = Data_t(canvas_size, 16, canvas_color);

    if (verbose)
        std::cout << "Matrix canvas generated with size: " << this->dst.size() << std::endl;
}


exhibit::Cross::Cross(const std::vector<exhibit::Frame>& frames_, const exhibit::Parameters& params_)
{
    this->frames = frames_;
    this->params = params_;
    this->verbose = true;
    
    assert(frames.size() == 4);
    
    int canvasHeight = static_cast<int>(std::round(params.canvasBase/params.canvasAspectRatio));
    Size_t canvas_size(params.canvasBase, canvasHeight);
    Scalar_t canvas_color = utils::rgb2bgr(params.canvasColor); 
    this->dst = Data_t(canvas_size, 16, canvas_color);

    if (verbose)
        std::cout << "Cross canvas generated with size: " << this->dst.size() << std::endl;
}


/* members definitions */
exhibit::Canvas* exhibit::Canvas::getCanvas(const std::vector<exhibit::Frame>& frames_, const exhibit::Parameters& params_, int nrows_, int ncols_)
{
    if (nrows_==0 || ncols_==0)
        return new Cross {frames_, params_};
    else
        return new Matrix {frames_, params_, nrows_, ncols_};
}


exhibit::FrameLayout_t exhibit::Cross::framesLayout
{
    {0, {2,1,0,0}},
    {1, {1,3,0,0}},
    {2, {1,3,0,2}},
    {3, {2,1,1,0}}
};


void exhibit::Canvas::verboseOff()
{
    this->verbose = false;
}


void exhibit::Canvas::verboseOn()
{
    this->verbose = true;
}


void exhibit::Canvas::resizeFrames()
{
    int frameBase = static_cast<int> (std::round(params.canvasBase*params.frame2canvasRatio));
    for (std::size_t k=0; k!=this->frames.size(); ++k) {
        if (frames.at(k).getSize() != Size_t {frameBase, frames.at(k).getHeight(frameBase)}) {
            frames.at(k).resize(frameBase);
            if (verbose)
                std::cout << "Resized frame n. " << k+1 << " with size: " << frames.at(k).getSize() << std::endl;
        }
    }
}


void exhibit::Canvas::save(const std::string &path) const
{
    utils::output(this->dst, path);
}


exhibit::Coord_t exhibit::Canvas::getOrigin(int nrows, int ncols, int row, int col, const std::string& orientation) const
{
    Coord_t origin;

    // aliases for the sake of semplicity
    int A = params.canvasBase;
    float r = 1./params.canvasAspectRatio;
    float p = params.frameAspectRatio;
    float h = params.hspaceRatio;
    float v = params.vspaceRatio;
    float f2c = params.frame2canvasRatio;

    // fix aspect ratio depending on orientation
    if (orientation=="landscape") {
        p = 1./p;
    }

    origin.x = std::round( (A/2)*(1 - f2c*ncols - f2c*h*(ncols-1)) + col*A*f2c*(1+h) );
    origin.y = std::round( (A/2)*(r - f2c*p*nrows - f2c*v*(nrows-1)) + row*A*f2c*(p+v) );

    return origin;
}


void exhibit::Matrix::make()
{
    Mask_t mask;
    std::size_t k;

    this->resizeFrames();

    for (std::size_t row=0; row!=this->nrows; ++row) {
        for (std::size_t col=0; col!=this->ncols; ++col) {
            k = row*this->ncols + col; // flattening of matrix
            mask = Mask_t(this->getOrigin(nrows, ncols, row, col, frames.at(k).getOrientation()), frames.at(k).getSize());
            if (verbose) {
                std::cout << "Frame n. " << k+1 << " of size: " << mask.size() << std::endl;
                std::cout << "Frame n. " << k+1 << " to be inserted in position (x=" << mask.x << ", y=" << mask.y << ")\n";
            }
            frames.at(k).copyTo(this->dst, mask);
            if (verbose)
                std::cout << "Frame n. " << k+1 << " inserted\n";
        }
    }
}


void exhibit::Cross::make()
{
    Mask_t mask;
    int nrows, ncols, row, col;

    this->resizeFrames();

    for (std::size_t k=0; k!=4; ++k) {
        std::tie(nrows, ncols, row, col) = Cross::framesLayout[k]; // assign to a tuple of 4 int
        mask = Mask_t(this->getOrigin(nrows, ncols, row, col, frames.at(k).getOrientation()), frames.at(k).getSize());
        if (verbose) {
            std::cout << "Frame n. " << k+1 << " of size: " << mask.size() << std::endl;
            std::cout << "Frame n. " << k+1 << " to be inserted in position (x=" << mask.x << ", y=" << mask.y << ")\n";
        }
        frames.at(k).copyTo(this->dst, mask);
        if (verbose)
            std::cout << "Frame n. " << k+1 << " inserted\n";
    }
}
