#include "../include/exhibit.h"

cv::Mat exhibit::utils::input(const std::string& path)
{
    cv::Mat src = cv::imread(cv::samples::findFile(path), cv::IMREAD_COLOR); // 3 channels
    return src;
}

void exhibit::utils::output(const cv::Mat& src, const std::string& path)
{
    if (!cv::imwrite(path, src)) 
        std::cerr << "Saving failed\n";
}

cv::Scalar exhibit::utils::rgb2bgr(const std::vector<int>& rgb)
{
    double b = static_cast<double>(rgb.at(2));
    double g = static_cast<double>(rgb.at(1));
    double r = static_cast<double>(rgb.at(0));

    return cv::Scalar {b,g,r};
}
