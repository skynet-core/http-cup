#pragma once
#include <boost/beast/http/basic_dynamic_body.hpp>
#include <boost/beast/http/message_fwd.hpp>

namespace cup::http::internal
{
    class Request;
    class Mapper
    {
      public:
        [[nodiscard]] static  auto MapToRequest(boost::beast::http::request<boost::beast::http::basic_dynamic_body<>>) -> Request;
    };
} // namespace cup::http::internal