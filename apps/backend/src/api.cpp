#include "crow.h"
#include <hiddenframe_headers.h>
#include <crow/middlewares/cors.h>
#include <fstream>
#include <filesystem>
#include <string>
#include <utils.h>

using namespace std;

const string BASE_API_URL = "http://localhost:8080";

int main()
{
    crow::App<crow::CORSHandler> app;

    CROW_ROUTE(app, "/")
        .methods(crow::HTTPMethod::GET)(
            []()
            { return "Hello, World!"; });

    CROW_ROUTE(app, "/images")
        .methods(crow::HTTPMethod::GET)(
            []()
            {
                string staticPath = "./static";
                vector<crow::json::wvalue> photos;

                for (const auto &entry : filesystem::directory_iterator(staticPath))
                {
                    image *imgptr = new image(entry.path().string());
                    string payload = imgptr->retrieve_payload(2);

                    string filename = entry.path().filename().string();
                    string id = filename.substr(0, filename.find_last_of('.')); // Remove the extension

                    crow::json::wvalue photo;
                    photo["id"] = id;
                    photo["url"] = BASE_API_URL + "/static/" + filename;
                    photo["payload"] = payload;
                    photo["resolved_payload"] = binaryToString(payload);
                    photos.push_back(photo);
                }

                crow::json::wvalue jsonResponse;
                jsonResponse = crow::json::wvalue::list(photos.begin(), photos.end());

                return jsonResponse;
            });

    CROW_ROUTE(app, "/image/upload")
        .methods(crow::HTTPMethod::POST)(
            [](const crow::request &req)
            {
                srand(static_cast<unsigned>(time(NULL)));

                int random = rand();

                string fileData;       // @patrick: this is the image data
                string metaDataString; // @patrick: this is of format { name: string, size: int, ext: string }, size is file size, ext is file extension
                string message;        // this will remain uninitialized if no message sent from frontend (FUTURE: it'll be uninitialized if no/invalid token provided)

                auto content_type = req.get_header_value("Content-Type");

                if (content_type.find("multipart/form-data") != string::npos)
                {
                    crow::multipart::message msg(req);

                    auto filePart = msg.get_part_by_name("file");
                    auto metaPart = msg.get_part_by_name("meta");
                    auto messagePart = msg.get_part_by_name("message");

                    if (!filePart.body.empty())
                    {
                        fileData = filePart.body;
                    }
                    else
                    {
                        crow::json::wvalue error_json;
                        error_json["success"] = false;
                        error_json["error"] = "No image found in the request";
                        return crow::response(400, error_json);
                    }

                    if (!metaPart.body.empty())
                    {
                        metaDataString = metaPart.body;
                    }
                    else
                    {
                        crow::json::wvalue error_json;
                        error_json["success"] = false;
                        error_json["error"] = "No metadata found in the request";
                        return crow::response(400, error_json);
                    }

                    if (!messagePart.body.empty())
                    {
                        message = messagePart.body;
                    }

                    try
                    {
                        // image i/o here
                        auto meta = crow::json::load(metaDataString);
                        if (!meta)
                        {
                            crow::json::wvalue error_json;
                            error_json["success"] = false;
                            error_json["error"] = "Invalid JSON in metadata";
                            return crow::response(400, error_json);
                        }
                        string fileExt = meta["ext"].s();
                        string fileName = to_string(random) + "." + fileExt;
                        string filePath = "./static/" + fileName;

                        int fileSize = meta["size"].i();
                        cout << fileSize + 1 << endl;
                        std::vector<unsigned char> convertedData(fileSize + 1);

                        memcpy(convertedData.data(), fileData.c_str(), fileSize + 1);
                        image *imgptr = new image(convertedData.data(), fileSize, fileExt);
                        // modify image with payload here if permission granted and desired
                        if (message != "")
                        {
                            // convert message to binary string
                            string messageBN = stringToBinary(message);
                            // need to get the first param from Jeremy's functions
                            imgptr->modify_image(2, messageBN);
                        }
                        imgptr->write_image(filePath);
                        crow::json::wvalue success_json;
                        success_json["success"] = true;
                        success_json["url"] = BASE_API_URL + "/static/" + fileName;
                        return crow::response(200, success_json);

                        // ofstream outputFile(filePath, ios::out | ios::binary);
                        // if (outputFile)
                        // {
                        //     outputFile << fileData;
                        //     outputFile.close();

                        // }
                        // else
                        // {
                        //     crow::json::wvalue error_json;
                        //     error_json["success"] = false;
                        //     error_json["error"] = "File writing failed";
                        //     return crow::response(500, error_json);
                        // }
                    }
                    catch (const exception &e)
                    {
                        crow::json::wvalue error_json;
                        error_json["success"] = false;
                        error_json["error"] = string("JSON parsing error: ") + e.what();
                        return crow::response(400, error_json);
                    }
                }
                else
                {
                    crow::json::wvalue error_json;
                    error_json["success"] = false;
                    error_json["error"] = "Invalid content type";
                    return crow::response(400, error_json);
                }
            });

    app.port(8080).multithreaded().run();
}