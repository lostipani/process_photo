#include "../include/exhibit.h"

exhibit::Data_t exhibit::utils::input(const std::string& path)
{
    Data_t src = cv::imread(cv::samples::findFile(path), cv::IMREAD_COLOR); // 3 channels
    return src;
}

void exhibit::utils::output(const exhibit::Data_t& src, const std::string& path)
{
    if (!cv::imwrite(path, src)) 
        std::cerr << "Saving failed" << std::endl;
}

exhibit::Scalar_t exhibit::utils::rgb2bgr(const std::vector<int>& rgb)
{
    double b = static_cast<double>(rgb.at(2));
    double g = static_cast<double>(rgb.at(1));
    double r = static_cast<double>(rgb.at(0));

    return Scalar_t {b,g,r};
}


bool exhibit::utils::parser(int argc, char** argv, exhibit::Parameters& params, int& nrows, int& ncols, std::vector<std::string>& source_files, std::string& save_name)
{
    namespace po = boost::program_options;
    
    // declarations
    bool force_quit = false; // =true in case caller should be terminated, e.g. --help
    std::string config_file;
    po::options_description generic("Cmd-line options");
    po::options_description config("Parameters configuration");
    po::options_description visible("Options");
    po::options_description hidden("Hidden options");
    po::options_description cmdline_options;
    po::options_description config_file_options;
    po::positional_options_description posit; // positional for source file(s)
    po::variables_map vm;
    
    // specifications
    generic.add_options()
        ("help", "Produce help message")
        ("config", po::value<std::string>(&config_file)->default_value("parameters.cfg"),"Parameters configuration file path")
        ("save", po::value<std::string>(&save_name)->default_value("test.jpg"),"Save canvas in name.jpg/png")
        ("cross", "Canvas Cross layout, overwrites choice of nrows/ncols")
        ("nrows", po::value<int>(&nrows)->default_value(1), "Canvas Matrix layout, number of rows, int")
        ("ncols", po::value<int>(&ncols)->default_value(1), "Canvas Matrix layout, number of columns, int")
        ;


    config.add_options()
        ("canvasAspectRatio", po::value<float>(&params.canvasAspectRatio), "Canvas base/height, float")
        ("frameAspectRatio", po::value<float>(&params.frameAspectRatio), "Frame base/height, always >1, float")
        ("hspaceRatio", po::value<float>(&params.hspaceRatio), "Frames horizontal spacing / Frame base, float")
        ("vspaceRatio", po::value<float>(&params.vspaceRatio), "Frames vertical spacing / Frame base, float")
        ("frame2canvasRatio", po::value<float>(&params.frame2canvasRatio), "Frame base / Canvas base, float")
        ("photo2frameRatio", po::value<float>(&params.photo2frameRatio), "Photo base / Frame base, float")
        ("frameThickRatio", po::value<std::vector<float>>(&params.frameThickRatio)->multitoken(), "Frame thickness / base, 4 floats {top,bot,lft,rgt}")
        ("canvasBase", po::value<int>(&params.canvasBase), "Canvas base, pixels")
        ("canvasColor", po::value<std::vector<int>>(&params.canvasColor)->multitoken(), "RGB, 3 ints")
        ("frameColor", po::value<std::vector<int>>(&params.frameColor)->multitoken(), "RGB, 3 ints")
        ("passpartoutColor", po::value<std::vector<int>>(&params.passpartoutColor)->multitoken(), "RGB, 3 ints")
        ;

    posit.add("sourceFiles", -1);

    hidden.add_options()
        ("sourceFiles", po::value<std::vector<std::string>>(), "Source file(s) path")
        ;
    
    cmdline_options.add(generic).add(config).add(hidden);
    config_file_options.add(config).add(hidden);
    visible.add(generic).add(config);


    // executions
    store(po::command_line_parser(argc, argv).options(cmdline_options).positional(posit).run(), vm);
    notify(vm);
    
    if (vm.count("help")){
        std::cout << "Mumi23 Process Photo Tool - October 2023" << std::endl << std::endl;
        std::cout << "Usage: process [options] sources..." << std::endl << std::endl;
        std::cout << visible << std::endl;
        force_quit = true;
        return force_quit;
    }
    
    std::ifstream ifs(config_file.c_str());
    if (!ifs) {
        std::cerr << "cannot open configuration file" << std::endl;
        force_quit = true;
        return force_quit;
    }
    else {
        store(parse_config_file(ifs, config_file_options), vm);
        notify(vm);
    }

    if (vm.count("sourceFiles"))
        source_files = vm["sourceFiles"].as<std::vector<std::string>>();
    else {
        std::cout << "no input source provided" << std::endl;
        force_quit=true;
        return force_quit;
    }

    if (vm.count("cross")) {
        ncols = 0;
        nrows = 0;
    }

    return force_quit;
}
