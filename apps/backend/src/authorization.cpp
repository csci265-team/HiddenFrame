#include "authorization.h"
#include <jwt-cpp/jwt.h>
#include <HiddenFrame_Headers.h>
#include <crow/middlewares/cookie_parser.h>
#include <crow/middlewares/cors.h>

using namespace std;

template <typename AllContext>
void AuthorizationMiddleware::before_handle(crow::request &req, crow::response &res, context &ctx, AllContext &all_ctx)
{
    try
    {
        string token = req.get_header_value("Authorization");

        if (token.empty())
        {
            auto cookie_ctx = all_ctx.template get<crow::CookieParser>();
            token = cookie_ctx.get_cookie("token");
        }

        cout << token << endl;

        auto decoded = jwt::decode(token);

        if (decoded.has_id() && decoded.has_expires_at())
        {
            if (decoded.get_expires_at() < std::chrono::system_clock::now())
            {
                crow::json::wvalue error_json;
                error_json["success"] = false;
                error_json["error"] = "Token expired";
                res = crow::response(401, error_json);
                res.end();
                return;
            }

            ctx.username = decoded.get_payload_claim("username").as_string();
            ctx.tokenId = decoded.get_id();
            ctx.userId = decoded.get_payload_claim("userId").as_integer();
        }
        else
        {
            crow::json::wvalue error_json;
            error_json["success"] = false;
            error_json["error"] = "Invalid token";
            res = crow::response(401, error_json);
            res.end();
            return;
        }
    }
    catch (const std::exception &e)
    {
        crow::json::wvalue error_json;
        error_json["success"] = false;
        error_json["error"] = e.what();
        res = crow::response(401, error_json);
        res.end();
        return;
    }
}

void AuthorizationMiddleware::after_handle(crow::request &req, crow::response &res, context &ctx)
{
    return;
}

template void AuthorizationMiddleware::before_handle<crow::detail::context<crow::CORSHandler, crow::CookieParser, AuthorizationMiddleware>>(crow::request &req, crow::response &res, context &ctx, crow::detail::context<crow::CORSHandler, crow::CookieParser, AuthorizationMiddleware> &all_ctx);