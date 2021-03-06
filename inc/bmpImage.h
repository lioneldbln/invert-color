#pragma once

#include <string>
#include <iostream>
#include <memory>

class BMPImage {
public:
  struct Header {
    uint16_t signature;
    uint32_t fileSize;
    uint32_t reserved;
    uint32_t dataOffset;
  };

  struct InfoHeader {
    uint32_t size;
    uint32_t width;
    uint32_t height;
    uint16_t planes;
    uint16_t bitCount;
    uint32_t compression;
    uint32_t imageSize;
    uint32_t xPixelsPerM;
    uint32_t yPixelsPerM;
    uint32_t colorsUsed;
    uint32_t colorsImportant;
  };

  Header header;
  InfoHeader infoHeader;
  std::unique_ptr<uint8_t[]> data;

  BMPImage() : header{}, infoHeader{}, data{} {}
  ~BMPImage() = default;
  BMPImage(const BMPImage&);
  BMPImage& operator=(BMPImage);
  BMPImage(BMPImage&&);

  friend void swap(BMPImage& left, BMPImage& right) noexcept;
 
  void readImage(const std::string& filePath);
  void invertColors();
  void saveImage(const std::string& filePath);

  friend std::ostream& operator<<(std::ostream& os, const BMPImage& img);
};
 
