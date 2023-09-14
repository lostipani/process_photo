#include "opencv2/core.hpp"
#include "opencv2/imgcodecs.hpp" // for cv:imwrite, cv::imread
#include "opencv2/imgproc.hpp" // for cv::resize
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <utility>



namespace exhibit {

    namespace utils 
    {
        cv::Mat input(const std::string&);
        void output(const cv::Mat&, const std::string&);
        cv::Scalar rgb2bgr(const std::vector<int>&);
    };


    class Frame
    {
        public:
        
        Frame(const std::string&);
        void resize(int); // set base size, keep aspect ratio fixed
        void resize(int, double); // set base and aspect ratio
        void resize(int, int); // set base and height size
        void make();
        void info() const;
        void save(const std::string&) const;

        private:
        
        cv::Mat src;
        std::string getOrientation() const;
        float getAspectRatio() const;
        int getHeight(int, double) const;
    };
    
    
    struct Parameters
    {
        float canvasAspectRatio; // height/base
        float frameAspectRatio; // height/base
        float hspaceRatio; // picture's base/horiz. spacing
        float vspaceRatio; // picture's base/vert. spacing
        float frame2canvasRatio; // picture's base/canvas' base
        float photo2frameRatio; // wrt. base
        std::vector<float> frameThickRatio; // frame's thickness to base ratio

        int canvasBase; // [px]

        std::vector<int> canvasColor;
        std::vector<int> frameColor;
        std::vector<int> passpartoutColor;
    };

};
