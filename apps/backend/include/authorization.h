#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include "crow.h"
#include <jwt-cpp/jwt.h>
#include <HiddenFrame_Headers.h>
#include <string>

struct AuthorizationMiddleware : public crow::ILocalMiddleware
{
    struct context
    {
        std::string username;
        std::string tokenId;
        int userId;
    };

    void before_handle(crow::request &req, crow::response &res, context &ctx);
    void after_handle(crow::request &req, crow::response &res, context &ctx);
};

#endif // AUTHORIZATION_H