#include "../include/frame.h"

cv::Mat utils::input(const std::string& path)
{
    cv::Mat src = cv::imread(cv::samples::findFile(path), cv::IMREAD_COLOR); // 3 channels
    return src;
}

void utils::output(const cv::Mat& src, const std::string& path)
{
    if (!cv::imwrite(path, src)) 
        std::cerr << "Saving failed\n";
}

cv::Scalar utils::rgb2bgr(const std::vector<int>& rgb)
{
    double b = static_cast<double>(rgb.at(2));
    double g = static_cast<double>(rgb.at(1));
    double r = static_cast<double>(rgb.at(0));

    return cv::Scalar {b,g,r};
}


Picture::Picture(const std::string& path)
{
    this->src = utils::input(path);
    // some setup for the instantiated object:
    this->getOrientation();
    this->getPhotoAspectRatio();
}

void Picture::getOrientation()
{
    this->orientation = (this->src.rows < this->src.cols) ? "landscape" : "portrait";
}

void Picture::getPhotoAspectRatio()
{
    if (this->orientation=="landscape")
        this->photoAspectRatio = static_cast<double>(this->src.cols)/static_cast<double>(this->src.rows);
    else
        this->photoAspectRatio = static_cast<double>(this->src.rows)/static_cast<double>(this->src.cols);
}

int Picture::getHeight(int base, double aspectRatio) const
{
    int height;

    if (this->orientation=="portrait")
        height = std::round(base*aspectRatio);
    else // =="landscape"
        height = std::round(base/aspectRatio);

    return height;
}

void Picture::resize(cv::Mat& img, int base, int height)
{
    cv::resize(img, img, cv::Size(base, height), 0, 0, cv::INTER_AREA);
}

void Picture::resize(cv::Mat& img, int base, double aspectRatio)
{
    int height = this->getHeight(base, aspectRatio);
    this->resize(img, base, height);
} 

void Picture::resizePhoto(int base, double aspectRatio)
{
    this->resize(src, base, aspectRatio);
} 

void Picture::resizeFrame(int base, double aspectRatio)
{
    this->resize(dst, base, aspectRatio);
} 

void Picture::toFrame(int base, double aspectRatio, double frame2photoRatio, const std::vector<double>& frameThickRatio, const std::vector<int> &frameColor, const std::vector<int> &passpartoutColor)
{
    /* Start from a photo to make a picture, i.e. picture = photo + passpartout + frame. Absolute size is the frame's base.
     * 
     * Parameters:
     * ----------
     * frame's base [int]
     * frame's aspectRatio [double]
     * frame to photo base ratio [double]
     * frame's thickness to base ratio [vector<double> x4; top bot lft rgt]
     * frame's colour RGB [vector<int> x3]
     * passpartout's colour RGB [vector<int> x3]
     *
     */

    // base and height of frame
    int fr_base   = base;
    int fr_height = this->getHeight(fr_base, aspectRatio);

    // resize photo accordingly to frame2photoRatio
    int ph_base   = std::round(base/frame2photoRatio);
    int ph_height = this->getHeight(ph_base, this->photoAspectRatio);
    this->resizePhoto(ph_base, this->photoAspectRatio);

    // mind BGR order in opencv
    cv::Scalar fr_color {utils::rgb2bgr(frameColor)};
    cv::Scalar pp_color {utils::rgb2bgr(passpartoutColor)};
    
    // frame's thickness [px]
    int fr_top = std::round(frameThickRatio.at(0)*base);
    int fr_bot = std::round(frameThickRatio.at(1)*base);
    int fr_lft = std::round(frameThickRatio.at(2)*base);
    int fr_rgt = std::round(frameThickRatio.at(3)*base);
    
    // passpartout's thickness [px]
    int pp_top = std::round(0.5*(fr_height - fr_top - fr_bot - ph_height));
    int pp_bot = pp_top;
    int pp_lft = std::round(0.5*(fr_base - fr_lft - fr_rgt - ph_base));
    int pp_rgt = pp_lft;
    
    // copy image in larger image so as to get the padding
    cv::copyMakeBorder(src, dst, pp_top, pp_bot, pp_lft, pp_rgt, cv::BORDER_CONSTANT, pp_color);
    cv::copyMakeBorder(dst, dst, fr_top, fr_bot, fr_lft, fr_rgt, cv::BORDER_CONSTANT, fr_color);
}


void Picture::info() const
{
    std::cout << this->orientation << std::endl;
    std::cout << this->src.cols << " x " << this->src.rows  << std::endl;
}


void Picture::save(const std::string &path) const
{
    utils::output(this->dst, path);
}
