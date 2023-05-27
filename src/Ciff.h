//
// Created by black on 5/24/2023.
//

#ifndef PARSER_CIFF_H
#define PARSER_CIFF_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstring>
#include <algorithm>

struct Pixel {
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

class Ciff {
private:
    std::string magic_;
    unsigned long long int header_size_;
    unsigned long long int content_size_;
    unsigned long long int width_;
    unsigned long long int height_;
    std::string caption_;
    std::vector<std::string> tags_;
    std::vector<Pixel> pixels_;
public:
    Ciff(std::string magic_,
         unsigned long long int header_size_,
         unsigned long long int content_size_,
         unsigned long long int width_,
         unsigned long long int height_,
         std::string caption_,
         std::vector<std::string> tags_,
         std::vector<Pixel> pixels_) :
            magic_(std::move(magic_)),
            header_size_(header_size_),
            content_size_(content_size_),
            width_(width_),
            height_(height_),
            caption_(std::move(caption_)),
            tags_(std::move(tags_)),
            pixels_(std::move(pixels_)) {}

    // getters
    [[nodiscard]] auto magic() const -> const std::string & { return magic_; }

    [[nodiscard]] auto header_size() const -> const unsigned long long int & { return header_size_; }

    [[nodiscard]] auto content_size() const -> const unsigned long long int & { return content_size_; }

    [[nodiscard]] auto width() const -> const unsigned long long int & { return width_; }

    [[nodiscard]] auto height() const -> const unsigned long long int & { return height_; }

    [[nodiscard]] auto caption() const -> const std::string & { return caption_; }

    [[nodiscard]] auto tags() const -> const std::vector<std::string> & { return tags_; }

    [[nodiscard]] auto pixels() const -> const std::vector<Pixel> & { return pixels_; }

    //override << operator
    friend std::ostream &operator<<(std::ostream &os, const Ciff &ciff) {
        os << "MAGIC: " << ciff.magic_ << std::endl;
        os << "HEADER_SIZE: " << ciff.header_size_ << std::endl;
        os << "CONTENT_SIZE: " << ciff.content_size_ << std::endl;
        os << "WIDTH: " << ciff.width_ << std::endl;
        os << "HEIGHT: " << ciff.height_ << std::endl;
        os << "CAPTION: " << ciff.caption_ << std::endl;
        os << "TAG_CNT: " << ciff.tags_.size() << std::endl;
//        os << "TAGS: ";
//        for (const auto &tag : ciff.tags_) {
//            os << tag << " ";
//        }
//        os << std::endl;
        os << "PIXEL_CNT: " << ciff.pixels_.size() << std::endl;
//        os << "PIXELS: ";
//        for (const auto &pixel : ciff.pixels_) {
//            os << "(" << (int) pixel.r << "," << (int) pixel.g << "," << (int) pixel.b << ") ";
//        }
        os << std::endl;
        return os;
    }
};



#endif //PARSER_CIFF_H
