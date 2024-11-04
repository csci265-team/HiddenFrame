#include "crow.h"
#include <jwt-cpp/jwt.h>
#include <HiddenFrame_Headers.h>

using namespace std;

struct AuthorizationMiddleware : crow::ILocalMiddleware
{
    struct context
    {
        string username;
        string tokenId;
        int userId;
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
                string secret = std::getenv("JWT_SECRET");

                auto verifier = jwt::verify()
                                    .with_issuer("HiddenFrame")
                                    .allow_algorithm(jwt::algorithm::hs256{secret});
                verifier.verify(decoded); // this will error if verification fails

                try
                {
                    sqlite3 *db = createDB();
                    auto [user_id, username] = verifyToken(db, token_id);

                    ctx.userId = user_id;
                    ctx.tokenId = token_id;
                    ctx.username = username;
                }
                catch (const std::exception &e)
                {
                    crow::json::wvalue error_json;
                    error_json["success"] = false;
                    error_json["error"] = e.what();
                    res.code = 401;
                    res.write(error_json.dump());
                    res.end();
                    return;
                }
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


};
