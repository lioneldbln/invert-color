#include "bmpImage.h"

#include <fstream>
#include <sstream>
#include <algorithm>

#include "fileGuard.h"
#include "exception_d.h"

BMPImage::BMPImage(const BMPImage& other) : header{other.header}, infoHeader{other.infoHeader}, data{new uint8_t[other.infoHeader.imageSize]} {
  std::copy(other.data.get(), other.data.get()+other.infoHeader.imageSize, data.get());
}

BMPImage& BMPImage::operator=(BMPImage other) {
  swap(*this, other);
  return *this;
}

BMPImage::BMPImage(BMPImage&& other) : BMPImage{} {
  swap(*this, other);
}  

void swap(BMPImage& left, BMPImage& right) noexcept {
  using std::swap; // enable ADL
  std::swap(left.header, right.header);
  std::swap(left.infoHeader, right.infoHeader);
  std::swap(left.data, right.data);
}

void BMPImage::readImage(const std::string &filePath) {
  FileGuard<std::ifstream> fileGuard(filePath, std::ios_base::in | std::ios_base::binary);
  if (!fileGuard.get().is_open()) {
    std::stringstream message;
    message << "file " << filePath << " does not exist";
    throw opening_file_error(message.str());
  }

  fileGuard.get().read(reinterpret_cast<char*>(&header.signature), sizeof(Header::signature));
  fileGuard.get().read(reinterpret_cast<char*>(&header.fileSize), sizeof(Header::fileSize));
  fileGuard.get().read(reinterpret_cast<char*>(&header.reserved), sizeof(Header::reserved));
  fileGuard.get().read(reinterpret_cast<char*>(&header.dataOffset), sizeof(Header::dataOffset));

  fileGuard.get().read(reinterpret_cast<char*>(&infoHeader.size), sizeof(InfoHeader::size));
  fileGuard.get().read(reinterpret_cast<char*>(&infoHeader.width), sizeof(InfoHeader::width));
  fileGuard.get().read(reinterpret_cast<char*>(&infoHeader.height), sizeof(InfoHeader::height));
  fileGuard.get().read(reinterpret_cast<char*>(&infoHeader.planes), sizeof(InfoHeader::planes));
  fileGuard.get().read(reinterpret_cast<char*>(&infoHeader.bitCount), sizeof(InfoHeader::bitCount));
  fileGuard.get().read(reinterpret_cast<char*>(&infoHeader.compression), sizeof(InfoHeader::compression));
  fileGuard.get().read(reinterpret_cast<char*>(&infoHeader.imageSize), sizeof(InfoHeader::imageSize));
  fileGuard.get().read(reinterpret_cast<char*>(&infoHeader.xPixelsPerM), sizeof(InfoHeader::xPixelsPerM));
  fileGuard.get().read(reinterpret_cast<char*>(&infoHeader.yPixelsPerM), sizeof(InfoHeader::yPixelsPerM));
  fileGuard.get().read(reinterpret_cast<char*>(&infoHeader.colorsUsed), sizeof(InfoHeader::colorsUsed));
  fileGuard.get().read(reinterpret_cast<char*>(&infoHeader.colorsImportant), sizeof(InfoHeader::colorsImportant));

  data = std::unique_ptr<uint8_t[]>{new uint8_t[infoHeader.imageSize]};
  fileGuard.get().read(reinterpret_cast<char*>(data.get()), infoHeader.imageSize);
}

void BMPImage::invertColors() {
  for (uint32_t i = 0; i < infoHeader.imageSize; i++) {
    data[i] = 255 - data[i];
  }
}

void BMPImage::saveImage(const std::string& filePath) {
  FileGuard<std::ofstream> fileGuard(filePath, std::ios_base::out | std::ios_base::binary);
  if (!fileGuard.get().is_open()) {
    std::stringstream message;
    message << "file " << filePath << " cannot be created";
    throw opening_file_error(message.str());
  }
    
  fileGuard.get().write(reinterpret_cast<char*>(&header.signature), sizeof(Header::signature));
  fileGuard.get().write(reinterpret_cast<char*>(&header.fileSize), sizeof(Header::fileSize));
  fileGuard.get().write(reinterpret_cast<char*>(&header.reserved), sizeof(Header::reserved));
  fileGuard.get().write(reinterpret_cast<char*>(&header.dataOffset), sizeof(Header::dataOffset));

  fileGuard.get().write(reinterpret_cast<char*>(&infoHeader.size), sizeof(InfoHeader::size));
  fileGuard.get().write(reinterpret_cast<char*>(&infoHeader.width), sizeof(InfoHeader::width));
  fileGuard.get().write(reinterpret_cast<char*>(&infoHeader.height), sizeof(InfoHeader::height));
  fileGuard.get().write(reinterpret_cast<char*>(&infoHeader.planes), sizeof(InfoHeader::planes));
  fileGuard.get().write(reinterpret_cast<char*>(&infoHeader.bitCount), sizeof(InfoHeader::bitCount));
  fileGuard.get().write(reinterpret_cast<char*>(&infoHeader.compression), sizeof(InfoHeader::compression));
  fileGuard.get().write(reinterpret_cast<char*>(&infoHeader.imageSize), sizeof(InfoHeader::imageSize));
  fileGuard.get().write(reinterpret_cast<char*>(&infoHeader.xPixelsPerM), sizeof(InfoHeader::xPixelsPerM));
  fileGuard.get().write(reinterpret_cast<char*>(&infoHeader.yPixelsPerM), sizeof(InfoHeader::yPixelsPerM));
  fileGuard.get().write(reinterpret_cast<char*>(&infoHeader.colorsUsed), sizeof(InfoHeader::colorsUsed));
  fileGuard.get().write(reinterpret_cast<char*>(&infoHeader.colorsImportant), sizeof(InfoHeader::colorsImportant));

  fileGuard.get().write(reinterpret_cast<char*>(data.get()), infoHeader.imageSize);
}

std::ostream& operator<<(std::ostream& os, const BMPImage& img) {
  os << "file size: " << img.header.fileSize << std::endl;
  os << "image width: " << img.infoHeader.width << std::endl;
  os << "image height: " << img.infoHeader.height << std::endl;
  os << "image size: " << img.infoHeader.imageSize;
  return os;
}

