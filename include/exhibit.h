#include "opencv2/core.hpp"
#include "opencv2/imgcodecs.hpp" // for cv:imwrite, cv::imread
#include "opencv2/imgproc.hpp" // for cv::resize
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <map>
#include <utility>
#include <cassert>


namespace exhibit {

    /* Data types and declarations*/
    using Data_t = cv::Mat;
    using Size_t = cv::Size;
    using Scalar_t = cv::Scalar;
    using Mask_t = cv::Rect;
    using Coord_t = cv::Point_<int>;
    using FrameLayout_t = std::map<int, std::tuple<int, int, int, int>>;
    class Frame;
    class Canvas;
    class Matrix;
    class Cross;
    struct Parameters;
    

    /*Namespace and class member declarations*/
    namespace utils 
    {
        Data_t input(const std::string&);
        void output(const Data_t&, const std::string&);
        Scalar_t rgb2bgr(const std::vector<int>&);
    };


    struct Parameters
    {
        float canvasAspectRatio; // height/base
        float frameAspectRatio; // height/base
        float hspaceRatio; // frame's base/horiz. spacing
        float vspaceRatio; // frame's base/vert. spacing
        float frame2canvasRatio; // frame's base/canvas' base
        float photo2frameRatio; // wrt. base
        std::vector<float> frameThickRatio; // frame's thickness to base ratio

        int canvasBase; // [px]

        std::vector<int> canvasColor;
        std::vector<int> frameColor;
        std::vector<int> passpartoutColor;
    };

    
    class Frame
    {
        public:
        Frame(const std::string&, const Parameters&);
        void resize(int); // set base size, keep aspect ratio fixed
        void resize(int, float); // set base and aspect ratio
        void resize(int, int); // set base and height size
        void make();
        void info() const;
        void save(const std::string&) const;

        private:
        Parameters params;
        Data_t src;
        
        std::string getOrientation() const;
        float getAspectRatio() const;
        Size_t getSize() const;
        int getHeight(int, float) const;
        int getHeight(int) const;
        void copyTo(Data_t&, const Mask_t&) const;
        
        friend class Canvas;
        friend class Matrix;
        friend class Cross;
    };
    

    class Canvas
    {
        public:
        Canvas(const std::vector<Frame>&, const Parameters&);
        virtual ~Canvas();
        virtual void make() = 0;
        virtual void resizeFrames();
        void save(const std::string&) const;
        void verboseOff();
        void verboseOn();
    
        protected:
        std::vector<Frame> frames;
        Parameters params;
        Data_t dst;
        bool verbose;

        Coord_t getOrigin(int, int, int, int, const std::string&) const;
    };


    class Matrix: public Canvas
    {
        public:
        Matrix(const std::vector<Frame>&, const Parameters&, int, int);
        void make() override;

        private:
        int nrows;
        int ncols;
    };


    class Cross: public Canvas
    {
        public:
        Cross(const std::vector<Frame>&, const Parameters&);
        void make() override;

        private:
        static FrameLayout_t framesLayout;
    };


};
