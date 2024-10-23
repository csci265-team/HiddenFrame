#include "crow.h"
#include <hiddenframe_headers.h>

int main()
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")
    ([]() -> std::string
     { 
        try {
            // Simulates images on the FS
            image* test = new image("../../resources/images/test/input/test_image_1.jpg");
            test->displayImageProperties();
            int n = 2; // pixel spacing
            int arrSize = 12;
            int arr[12] = {3, 1, 3, 0, 2, 1, 2, 0, 1, 1, 1, 0};
            test->modify_image(n, arr, arrSize);
            test->write_image("../../resources/images/test/output/test_image_1.png");
            image* payloadTest = new image("../../resources/images/test/output/test_image_1.png");
            std::string payload = payloadTest->retrieve_payload(n);

            return "Hidden Message is " + payload;
        
            // Simulate image passed by API
            /*int ioWidth, ioHeight, ioChannels;
            std::string filepath = "../../resources/images/test/input/test_image_1.jpg";
            unsigned char* testptr = stbi_load(filepath.c_str(), &ioWidth, &ioHeight, &ioChannels, 0);
            image* test2 = new image(testptr);
            test2->displayImageProperties();*/
        }
        catch (const std::invalid_argument& e1) {
            std::cerr << "Encountered an exception: " << e1.what() << std::endl;
            return "Error";
        }
    });

    app.port(8080).multithreaded().run();
}