#pragma once

#include <boost/url.hpp>
#include <string>
#include <vector>
#include <optional>

namespace cup::http
{
    enum class Method
    {
        GET = 0,
        POST = 1
    };

    using Bytes = std::vector<uint8_t>;

    class Request
    {
      public:
        constexpr static auto USER_AGENT = "Mozilla/5.0";
        [[nodiscard]] auto URL() const & -> const boost::url &;
        [[nodiscard]] auto UserAgent() const & -> const std::string &;
        [[nodiscard]] auto Method() const & -> const Method &;
        [[nodiscard]] auto Body() const & -> const std::optional<Bytes> &;

      private:
        boost::url m_url;
        std::string m_userAgent{USER_AGENT};
        http::Method m_method{Method::GET};
        std::optional<Bytes> m_body;
    };
} // namespace cup::http