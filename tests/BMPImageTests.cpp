#include "bmpImage.h"

#include <algorithm>

#include "gmock/gmock.h"

class BMPImageTest : public testing::Test {
public:
  BMPImage bmpImage;
};

TEST_F(BMPImageTest, copyConstructorWorks) {
  bmpImage.header = {0, 1, 2, 3};
  bmpImage.infoHeader = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  bmpImage.data.reset(new uint8_t[bmpImage.infoHeader.imageSize]);
  std::iota(bmpImage.data.get(), bmpImage.data.get()+bmpImage.infoHeader.imageSize, 0);
  BMPImage copy{bmpImage};
  ASSERT_THAT(copy.header.dataOffset, testing::Eq(bmpImage.header.dataOffset));
  ASSERT_THAT(copy.infoHeader.imageSize, testing::Eq(bmpImage.infoHeader.imageSize));
  ASSERT_THAT(copy.data[3], testing::Eq(bmpImage.data[3]));
}

TEST_F(BMPImageTest, copyAssignementWorks) {
  bmpImage.header = {0, 1, 2, 3};
  bmpImage.infoHeader = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  bmpImage.data.reset(new uint8_t[bmpImage.infoHeader.imageSize]);
  std::iota(bmpImage.data.get(), bmpImage.data.get()+bmpImage.infoHeader.imageSize, 0);
  BMPImage b1;
  BMPImage b2;
  b1 = b2 = bmpImage;
  ASSERT_THAT(b1.header.dataOffset, testing::Eq(bmpImage.header.dataOffset));
  ASSERT_THAT(b1.infoHeader.imageSize, testing::Eq(bmpImage.infoHeader.imageSize));
  ASSERT_THAT(b1.data[3], testing::Eq(bmpImage.data[3]));
}

TEST_F(BMPImageTest, moveConstructorWorks) {
  bmpImage.header = {0, 1, 2, 3};
  bmpImage.infoHeader = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  bmpImage.data.reset(new uint8_t[bmpImage.infoHeader.imageSize]);
  std::iota(bmpImage.data.get(), bmpImage.data.get()+bmpImage.infoHeader.imageSize, 0);
  BMPImage mv{std::move(bmpImage)};
  ASSERT_THAT(mv.header.dataOffset, testing::Eq(3u));
  ASSERT_THAT(mv.infoHeader.imageSize, testing::Eq(6u));
  ASSERT_THAT(mv.data[3], testing::Eq(3));
  ASSERT_THAT(bmpImage.header.dataOffset, testing::Eq(0u));
  ASSERT_THAT(bmpImage.infoHeader.imageSize, testing::Eq(0u));
  ASSERT_THAT(bmpImage.data.get(), testing::Eq(nullptr));
}

TEST_F(BMPImageTest, moveAssignmentWorks) {
  bmpImage.header = {0, 1, 2, 3};
  bmpImage.infoHeader = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  bmpImage.data.reset(new uint8_t[bmpImage.infoHeader.imageSize]);
  std::iota(bmpImage.data.get(), bmpImage.data.get()+bmpImage.infoHeader.imageSize, 0);
  BMPImage mv;
  mv = std::move(bmpImage);
  ASSERT_THAT(mv.header.dataOffset, testing::Eq(3u));
  ASSERT_THAT(mv.infoHeader.imageSize, testing::Eq(6u));
  ASSERT_THAT(mv.data[3], testing::Eq(3));
  ASSERT_THAT(bmpImage.header.dataOffset, testing::Eq(0u));
  ASSERT_THAT(bmpImage.infoHeader.imageSize, testing::Eq(0u));
  ASSERT_THAT(bmpImage.data.get(), testing::Eq(nullptr));
}

