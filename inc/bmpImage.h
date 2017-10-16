#pragma once

#include <string>
#include <iostream>

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
  uint8_t *data;

  BMPImage() : header{}, infoHeader{}, data{} {}
  ~BMPImage();
  BMPImage(const BMPImage&) = delete;
  BMPImage& operator=(const BMPImage&) = delete;
  BMPImage(BMPImage&&) = delete;
  BMPImage& operator=(BMPImage&&) = delete;

  void readImage(const std::string& filePath);
  void invertColors();
  void saveImage(const std::string& filePath);

  friend std::ostream& operator<<(std::ostream& os, const BMPImage& img);
};
 
