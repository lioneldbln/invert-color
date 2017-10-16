#include <iostream>
#include <exception>

#include "exception_d.h"
#include "commandLine.h"
#include "fileGuard.h"
#include "bmpImage.h"

int main(int argc, char* argv[]) {
  try {
    CommandLine cmdline;
    cmdline.parse(argc, argv);

    BMPImage bmpImage;
    bmpImage.readImage(cmdline.file_path());
    std::cout << bmpImage << std::endl;
    bmpImage.invertColors();
    bmpImage.saveImage(cmdline.output_path());

    std::cout << "!!SUCCESS!!" << std::endl;
  }
  catch(bad_format_cmdline& ex) {
    std::cerr << ex.what() << std::endl;
    std::cerr << "Try 'clr_invert file_path -o output_file_path'" << std::endl;
    std::cerr << "!!FAILURE!!" << std::endl;
  }
  catch(opening_file_error& ex) {
    std::cerr << ex.what() << std::endl;
    std::cerr << "!!FAILURE!!" << std::endl;
  }    
  catch(...) {
    std::cerr << "Unknown exception" << std::endl;
    std::cerr << "!!FAILURE!!" << std::endl;
  }

  return 0;
}

