#include "../include/exhibit.h"

exhibit::Data_t exhibit::utils::input(const std::string& path)
{
    Data_t src = cv::imread(cv::samples::findFile(path), cv::IMREAD_COLOR); // 3 channels
    return src;
}

void exhibit::utils::output(const exhibit::Data_t& src, const std::string& path)
{
    if (!cv::imwrite(path, src)) 
        std::cerr << "Saving failed\n";
}

exhibit::Scalar_t exhibit::utils::rgb2bgr(const std::vector<int>& rgb)
{
    double b = static_cast<double>(rgb.at(2));
    double g = static_cast<double>(rgb.at(1));
    double r = static_cast<double>(rgb.at(0));

    return Scalar_t {b,g,r};
}
