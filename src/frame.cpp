#include "../include/exhibit.h"


exhibit::Frame::Frame(const std::string& path, const Parameters& params_):
    params{params_}
{
    this->src = utils::input(path);
}



std::string exhibit::Frame::getOrientation() const
{
    return (this->src.rows < this->src.cols) ? "landscape" : "portrait";
}



exhibit::Size_t exhibit::Frame::getSize() const
{
    return this->src.size();
}



float exhibit::Frame::getAspectRatio() const
{
    if (this->getOrientation()=="landscape")
        return static_cast<float>(this->src.cols)/static_cast<float>(this->src.rows);
    else
        return static_cast<float>(this->src.rows)/static_cast<float>(this->src.cols);
}



int exhibit::Frame::getHeight(int base, float aspectRatio) const
{
    if (this->getOrientation()=="portrait")
        return static_cast<int>(std::round(base*aspectRatio));
    else // =="landscape"
        return static_cast<int>(std::round(base/aspectRatio));
}



void exhibit::Frame::resize(int base, int height)
{
    cv::resize(this->src, this->src, Size_t {base, height}, 0, 0, cv::INTER_AREA);
}



void exhibit::Frame::resize(int base, float aspectRatio)
{
    int height = this->getHeight(base, aspectRatio);
    this->resize(base, height);
}



void exhibit::Frame::resize(int base)
{
    this->resize(base, this->getAspectRatio());
}
 


void exhibit::Frame::make()
{
    // base and height of frame
    int fr_base = std::round(params.frame2canvasRatio*params.canvasBase);
    int fr_height = this->getHeight(fr_base, params.frameAspectRatio);

    // resize photo accordingly to frame2photoRatio
    int ph_base = std::round(fr_base*params.photo2frameRatio);
    int ph_height = this->getHeight(ph_base, this->getAspectRatio());
    this->resize(ph_base, ph_height);

    // mind BGR order in opencv
    Scalar_t fr_color {utils::rgb2bgr(params.frameColor)};
    Scalar_t pp_color {utils::rgb2bgr(params.passpartoutColor)};
    
    // frame's thickness [px]
    int fr_top = std::round(params.frameThickRatio.at(0)*fr_base);
    int fr_bot = std::round(params.frameThickRatio.at(1)*fr_base);
    int fr_lft = std::round(params.frameThickRatio.at(2)*fr_base);
    int fr_rgt = std::round(params.frameThickRatio.at(3)*fr_base);
    
    // passpartout's thickness [px]
    int pp_top = std::round(0.5*(fr_height - fr_top - fr_bot - ph_height));
    int pp_bot = pp_top;
    int pp_lft = std::round(0.5*(fr_base - fr_lft - fr_rgt - ph_base));
    int pp_rgt = pp_lft;
    
    // copy image in larger image so as to get the padding
    cv::copyMakeBorder(this->src, this->src, pp_top, pp_bot, pp_lft, pp_rgt, cv::BORDER_CONSTANT, pp_color);
    cv::copyMakeBorder(this->src, this->src, fr_top, fr_bot, fr_lft, fr_rgt, cv::BORDER_CONSTANT, fr_color);
}



void exhibit::Frame::copyTo(exhibit::Data_t& dst, const exhibit::Mask_t& mask) const
{
    this->src.copyTo(Data_t {dst, mask});
}



void exhibit::Frame::info() const
{
    std::cout << this->getOrientation() << std::endl;
    std::cout << this->getSize() << std::endl;
}



void exhibit::Frame::save(const std::string &path) const
{
    utils::output(this->src, path);
}
