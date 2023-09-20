#include "../include/exhibit.h"


/* constructors */
exhibit::Canvas::Canvas(const std::vector<exhibit::Frame>& frames_, const exhibit::Parameters& params_):
    frames{frames_}, params{params_}
{
    // canvas is always landscape oriented
    int canvasHeight = static_cast<int>(std::round(params.canvasBase/params.canvasAspectRatio));
    Size_t canvas_size(params.canvasBase, canvasHeight);
    Scalar_t canvas_color = utils::rgb2bgr(params.canvasColor); 
    this->dst = Data_t(canvas_size, 16, canvas_color);
}

exhibit::Canvas::~Canvas()
{
}


exhibit::Matrix::Matrix(const std::vector<exhibit::Frame>& frames_, const exhibit::Parameters& params_, int nrows_, int ncols_):
    Canvas::Canvas(frames_, params_), nrows{nrows_}, ncols{ncols_}
{
    assert(frames.size() == nrows*ncols);
}

exhibit::Cross::Cross(const std::vector<exhibit::Frame>& frames_, const exhibit::Parameters& params_):
    Canvas::Canvas(frames_, params_)
{
    assert(frames.size() == 4);
}


/* members definitions */
exhibit::FrameLayout_t exhibit::Cross::framesLayout
{
    {0, {2,1,0,0}},
    {1, {1,3,0,0}},
    {2, {1,3,0,2}},
    {3, {2,1,1,0}}
};


void exhibit::Canvas::save(const std::string &path) const
{
    utils::output(this->dst, path);
}


exhibit::Coord_t exhibit::Canvas::getOrigin(int nrows, int ncols, int row, int col) const
{
    Coord_t origin;

    // aliases for the sake of semplicity
    int A = params.canvasBase;
    float r = params.canvasAspectRatio;
    float p = params.frameAspectRatio;
    float h = params.hspaceRatio;
    float v = params.vspaceRatio;
    float f2c = params.frame2canvasRatio;

    origin.x = std::round( (A/2)*(1 - f2c*ncols - f2c*h*(ncols-1)) + (col-1)*A*f2c*(1 + h) );
    origin.y = std::round( (A/2)*(r - f2c*p*nrows - f2c*v*(nrows-1)) + (row-1)*A*f2c*(p + v) );

    return origin;
}


void exhibit::Matrix::make()
{
    Mask_t mask;
    std::size_t k;
    
    for (std::size_t row=0; row!=this->nrows; ++row) {
        for (std::size_t col=0; col!=this->ncols; ++col) {
            k = row*this->ncols + col; // flattening of matrix
            frames.at(k).resize(std::round(params.canvasBase*params.frame2canvasRatio));
            mask = Mask_t(this->getOrigin(nrows, ncols, row, col), frames.at(k).getSize());
            
            // DBG
            std::cerr << "frame: " << k << std::endl;
            frames.at(k).info();
            std::cerr << "mask origin: " << mask.x << "\t" << mask.y << std::endl;
            std::cerr << "dst: " << dst.size() << std::endl;
            
            frames.at(k).copyTo(this->dst, mask);
        }
    }
}


void exhibit::Cross::make()
{
    Mask_t mask;
    int nrows, ncols, row, col;

    for (std::size_t k=0; k!=4; ++k) {
        frames.at(k).resize(std::round(params.canvasBase*params.frame2canvasRatio));
        std::tie(nrows, ncols, row, col) = Cross::framesLayout[k]; // assign to a tuple of 4 int
        mask = Mask_t(this->getOrigin(nrows, ncols, row, col), frames.at(k).getSize());
        frames.at(k).copyTo(this->dst, mask);
    }
}
