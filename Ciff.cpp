//
// Created by black on 5/24/2023.
//

#include "Ciff.h"
#include <jpeglib.h>

using namespace std;
bool  Ciff::writeJpeg(std::string filename) const {

    for (auto pixel : pixels()){

    }

    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;

    FILE* outfile;
    JSAMPROW row_pointer[1];

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);

    if ((outfile = fopen(filename.c_str(), "wb")) == NULL) {
        std::cerr << "can't open " << filename << "\n";
        return false;
    }

    jpeg_stdio_dest(&cinfo, outfile);

    cinfo.image_width = width();
    cinfo.image_height = height();
    cinfo.input_components = 3;    // Number of color components per pixel
    cinfo.in_color_space = JCS_RGB; // Color space of input image

    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, 75, TRUE); // Set quality [0..100]

    jpeg_start_compress(&cinfo, TRUE);

    while (cinfo.next_scanline < cinfo.image_height) {
        row_pointer[0] = (JSAMPROW)&pixels()[cinfo.next_scanline * width()];
        jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }

    jpeg_finish_compress(&cinfo);
    fclose(outfile);
    jpeg_destroy_compress(&cinfo);

    return true;
}

