#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <crow_all.h>
#include <jwt-cpp/jwt.h>
#include <string>
#include <variant>
#include <sqlite/sqlite3.h>

struct AuthorizationMiddleware : public crow::ILocalMiddleware
{
    struct context
    {
        std::string username;
        std::string tokenId;
        int userId;
    };

    template <typename AllContext>
    void before_handle(crow::request &req, crow::response &res, context &ctx, AllContext &all_ctx);
    void after_handle(crow::request &req, crow::response &res, context &ctx);
};

std::pair<bool, std::variant<std::string, std::tuple<int, std::string, std::string>>> verify_token(const std::string &token, sqlite3 *database);

#endif // AUTHORIZATION_H