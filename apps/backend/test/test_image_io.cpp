#include <boost/test/unit_test.hpp>
#include <hiddenframe_headers.h>
#include <iostream>
#include <vector>
#include <utils.h>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;

vector<unsigned char> readFileToBuffer(const char *filepath);

BOOST_AUTO_TEST_SUITE(ImageIOTestSuite)

BOOST_AUTO_TEST_CASE(TestLoadAndWriteJPGFromFileSystem)
{
    image test1 = image("../../resources/images/test/input/test_image_1.jpg");
    BOOST_REQUIRE(test1.valid_image());
    BOOST_TEST_MESSAGE("Test 1 - Loading JPG from File System - was successful.");
    test1.write_image("../../resources/images/test/output/test_image_1.png");
}

BOOST_AUTO_TEST_CASE(TestLoadAndWritePNGromFileSystem)
{
    image test2 = image("../../resources/images/test/input/test_image_2.png");
    BOOST_REQUIRE(test2.valid_image());
    BOOST_TEST_MESSAGE("Test 2 - Loading PNG from File System - was successful.");
    test2.write_image("../../resources/images/test/output/test_image_2.png");
}

BOOST_AUTO_TEST_CASE(TestWriteImageToFileSystem)
{
    image test3a = image("../../resources/images/test/output/test_image_1.png");
    BOOST_REQUIRE(test3a.valid_image());
    BOOST_TEST_MESSAGE("Test 3 - Writing Image to File System - was successful.");
    image test3b = image("../../resources/images/test/input/test_image_1.jpg");
    BOOST_REQUIRE(test3b.valid_image());
    BOOST_CHECK(test3a.filetype != test3b.filetype);
    BOOST_TEST_MESSAGE("Test 4 - Changing image format - was successful.");
}

BOOST_AUTO_TEST_CASE(TestImageReadingFromSimulatedLiveStream)
{
    vector<unsigned char> imageData = readFileToBuffer("../../resources/images/test/input/test_image_6.bmp");
    image test5 = image(imageData.data(), static_cast<int>(imageData.size()), "bmp");
    BOOST_REQUIRE(test5.valid_image());
    BOOST_TEST_MESSAGE("Test 5 - Image reading from simulated live stream - was successful.");
}

BOOST_AUTO_TEST_CASE(TestImageEmbeddingAndRetrieval)
{
    image test6 = image("../../resources/images/test/input/test_image_7.png");
    int n = 2; // pixel spacing
    string teststr = "Hello, World!";
    string teststrBin = stringToBinary(teststr);
    test6.modify_image(n, teststrBin);
    test6.write_image("../../resources/images/test/output/test_image_7.png");
    test6.displayImageProperties();
    image payloadTest = image("../../resources/images/test/output/test_image_7.png");
    string payload = payloadTest.retrieve_payload(n);
    BOOST_CHECK_EQUAL(teststr, binaryToString(payload));
    BOOST_TEST_MESSAGE("Test 6 - Image embedding and retrieval - was successful.");
}

BOOST_AUTO_TEST_SUITE_END()

vector<unsigned char> readFileToBuffer(const char *filepath)
{
    ifstream file(filepath, ios::binary);
    if (!file)
    {
        throw std::runtime_error("Error opening file");
    }
    vector<unsigned char> buffer((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));
    return buffer;
}