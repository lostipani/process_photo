#include "opencv2/core.hpp"
#include "opencv2/imgcodecs.hpp" // for cv:imwrite, cv::imread
#include "opencv2/imgproc.hpp" // for cv::resize
#include <iostream>
#include <string>
#include <cmath>
#include <vector>


namespace utils 
{
    cv::Mat input(const std::string& path);
    void output(const cv::Mat& src, const std::string& path);
    cv::Scalar rgb2bgr(const std::vector<int>& rgb);
};


class Picture 
{
    public:
    
    Picture(const std::string&);
    void resizePhoto(int, double);
    void resizeFrame(int, double);
    void toFrame(int, double, double, const std::vector<double>&, const std::vector<int>&, const std::vector<int>&);
    void info() const;
    void save(const std::string&) const;

    private:
    
    cv::Mat src; //photo
    cv::Mat dst; //final picture
    std::string orientation;
    double photoAspectRatio;
    void getOrientation();
    void getPhotoAspectRatio();
    void resize(cv::Mat&, int, int);
    void resize(cv::Mat&, int, double);
    int getHeight(int, double) const;
};
