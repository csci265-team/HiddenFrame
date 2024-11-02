#include "crow.h"
#include "crow.h"
#include <jwt-cpp/jwt.h>

using namespace std;

struct Authorization
{
    struct context
    {
    };

    void before_handle(crow::request &req, crow::response &res, context &ctx)
    {
        try
        {
            string token = req.get_header_value("Authorization");

            auto decoded = jwt::decode(token);

            if (decoded.has_id() && decoded.has_expires_at())
            {
                if (decoded.get_expires_at() < std::chrono::system_clock::now())
                {
                    crow::json::wvalue error_json;
                    error_json["success"] = false;
                    error_json["error"] = "Token expired";
                    res.code = 401;
                    res.write(error_json.dump());
                    res.end();
                    return;
                }

                string token_id = decoded.get_id();
                string username = "username"; // TODO: @patrick get username from database based on token id
                string secret = std::getenv("JWT_SECRET");

                decoded.get_payload_json();

                auto verifier = jwt::verify()
                                    .with_issuer("HiddenFrame")
                                    .with_claim("username", jwt::claim(username))
                                    .allow_algorithm(jwt::algorithm::hs256{secret});
                verifier.verify(decoded); // this will error if verification fails
            }
            else
            {
                crow::json::wvalue error_json;
                error_json["success"] = false;
                error_json["error"] = "Unauthorized";
                res.code = 401;
                res.write(error_json.dump());
                res.end();
                return;
            }
        }

        catch (const std::exception &e)
        {
            crow::json::wvalue error_json;
            error_json["success"] = false;
            error_json["error"] = "Unauthorized";
            res.code = 401;
            res.write(error_json.dump());
            res.end();
            return;
        }
    }

    void after_handle(crow::request &req, crow::response &res, context &ctx)
    {
        // add logged in user to context
    }
};
