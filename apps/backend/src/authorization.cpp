#include "crow.h"

using namespace std;

struct Authorization
{
    struct context
    {
    };

    void before_handle(crow::request &req, crow::response &res, context &ctx)
    {
        string token = req.get_header_value("Authorization");
    }

    void after_handle(crow::request &req, crow::response &res, context &ctx)
    {
    }
};
