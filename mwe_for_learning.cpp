#include "opencv2/core.hpp"
#include "opencv2/imgcodecs.hpp" // for cv:imwrite, cv::imread
#include "opencv2/imgproc.hpp" // for cv::resize
#include <iostream>
#include <string>
#include <vector>


// image load
cv::Mat img_load (const std::string& img_name){
    cv::Mat src;
    try{
        src = cv::imread(cv::samples::findFile(img_name), cv::IMREAD_COLOR); // 3 channels
    }
    catch (const std::exception& e){
        std::cerr << "failed acquisition" << std::endl << e.what();
    }
    return src;
}

// image dump
int img_save (const std::string& save_name, const cv::Mat& src){
    bool retval = false;
    try{
        retval = cv::imwrite(save_name, src);
    }
    catch (const std::exception& e){
        std::cerr << "failed export" << std::endl << e.what();
    }

    return retval ? 0 : -1;
}


/*
 * Step 1: import and save .jpg unmodified picture
 */

int _step1 (int argc, char** argv){
    cv::Mat src = img_load(argv[1]);
    return img_save("step1.jpg", src);
} 


/*
 * Step 2: print out relevant data of imported image
 */

int _step2 (int argc, char** argv){
    cv::Mat src = img_load(argv[1]);
    
    std::cout << "dims: "      << src.dims    << std::endl <<
                 "flags: "     << src.flags   << std::endl <<
                 "size dim1: " << src.cols    << std::endl <<
                 "size dim2: " << src.rows    << std::endl <<
                 "type: "      << src.type()  << std::endl <<
                 "depth: "     << src.depth() << std::endl;
    return 0;
}


/*
 * Step 3: resize imported image and save it. 
 * Resize along dimensions by arbitrary factors *or*
 * resize according to an arbitrary size (x,y).
 */

int _step3 (int argc, char** argv){
    cv::Mat src = img_load(argv[1]);
    cv::Mat dst; // allocate destination cv::Mat object   
    
    // 1) shrink by 0.1 in width and by 0.5 in height (provide cv::Size() empty)
    cv::resize(src, dst, cv::Size(), 0.1, 0.5, cv::INTER_AREA);
    int retval1 = img_save("step3_a.jpg", dst);

    // 2) resize by (x,y)
    cv::resize(src, dst, cv::Size(1000,500), 0, 0, cv::INTER_AREA);
    int retval2 = img_save("step3_b.jpg", dst);

    return retval1 + retval2;
}


/*
 * Step 4: add a padding to the imported image
 * cv::BORDER_CONSTANT ensures a uniform color
 *
 */

int _step4 (int argc, char** argv){
    cv::Mat src = img_load(argv[1]);
    cv::Mat dst; // allocate destination cv::Mat object
    
    // mind BGR order
    cv::Scalar pad_color {227, 254, 254};
    // span of padding
    int span = atoi(argv[2]); // [px]
    // copy image in larger image so as to get the padding
    cv::copyMakeBorder(src, dst, span, span, span, span, cv::BORDER_CONSTANT, pad_color);
    
    int retval = img_save("step4.png", dst);

    return retval;
}


/*
 * Step 5: compose more images in one file
 * for instance, two horizontal photos, stacked with arbitrary clearance.
 */


int _step5 (int argc, char** argv){
    // params
    cv::Size ph_size {300, 200}; // size of each photo
    cv::Size bg_size {800, 600}; // size of canvas
    int vspace {50}; // clearance space

    // import images and store in a vector
    std::vector<cv::Mat> srcs;
    srcs.push_back(img_load(argv[1]));
    srcs.push_back(srcs.at(0)); // just use the same image twice

    // resize images
    for (std::size_t k=0; k!=srcs.size(); k++)
        cv::resize(srcs.at(k), srcs.at(k), ph_size, 0, 0, cv::INTER_AREA);

    // create background with uniform color, cv::Mat bg is the saved object of this function
    cv::Scalar bg_color {255, 255, 255}; // white
    cv::Mat bg {bg_size, 16, bg_color}; // type 16 == CV_8UC3 i.e. 8 bit x 3 channels BGR

    // here goes the maths: set sources origin P(x,y) from top left corner
    std::vector <cv::Point_ <int>> orgs;
    orgs.push_back(
                    cv::Point_ <int>{
                                     (bg_size.width - ph_size.width)/2, 
                                     (bg_size.height - vspace - 2*ph_size.height)/2
                                    }
                  );
    orgs.push_back(
                    cv::Point_ <int>{
                                     (bg_size.width - ph_size.width)/2, 
                                     (bg_size.height + vspace)/2
                                    }
                  );

    // copy to background
    cv::Mat inset;
    cv::Rect mask;
    for (std::size_t k=0; k!=srcs.size(); k++){
        mask  = cv::Rect {orgs.at(k), ph_size};
        inset = cv::Mat  {bg, mask};
        srcs.at(k).copyTo(inset);
    }

    return img_save("step5.png", bg);
}


/*
 * Step 6: compression format, jpg vs png
 */

int _step6 (int argc, char** argv){

    cv::Mat a {cv::Size(1920,1080), 16, cv::Scalar(0,0,0)};
    cv::Mat b = img_load(argv[1]);

    cv::imwrite("1.png", b, std::vector<int> {cv::IMWRITE_PNG_COMPRESSION, 1});
    cv::imwrite("6.png", b,  std::vector<int> {cv::IMWRITE_PNG_COMPRESSION, 6});
    cv::imwrite("20.jpg", b, std::vector<int> {cv::IMWRITE_JPEG_QUALITY, 20});
    cv::imwrite("95.jpg", b, std::vector<int> {cv::IMWRITE_JPEG_QUALITY, 95});

    return 0;
}



int main(int argc, char** argv){

    int retval = _step6 (argc, argv);

    return retval;
}
