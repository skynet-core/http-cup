#include "internal/session.h"
#include "request.h"
#include "response.h"
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/url.hpp>
#include <chrono>
#include <memory>
#include <system_error>

namespace cup::http
{
    namespace beast = boost::beast;
    namespace http = beast::http;
    namespace net = boost::asio;
    namespace ssl = net::ssl;

    using tcp = net::ip::tcp;
    using url = boost::url;
    using scheme = boost::urls::scheme;
    using error_code = boost::system::error_code;

    class Session::Impl
    {
        constexpr static auto DEFAULT_HTTPS_PORT = 443;
        constexpr static auto DEFAULT_HTTP_PORT = 80;
        constexpr static auto DEFAULT_CONNECT_TIMEOUT = 30;
        constexpr static auto DEFAULT_WRITE_TIMEOUT = 30;

        static auto getPort(const url &reqUrl) -> int
        {
            if (auto port = reqUrl.port_number(); port > 0)
            {
                return port;
            }
            switch (reqUrl.scheme_id())
            {
            case scheme::https:
                return DEFAULT_HTTPS_PORT;
            case scheme::http:
                return DEFAULT_HTTP_PORT;
            default:
                abort();
            }
        }

      public:
        Impl(net::io_context &ioc_) : ioc(ioc_)
        {
        }

        auto Do([[maybe_unused]] Request req) -> Result<Response>
        {
            tcp::resolver resolver{ioc};
            beast::tcp_stream stream{ioc};
            auto const &url = req.URL();
            auto const results = resolver.resolve(url.host(), std::to_string(getPort(url)));
            // connection timeout ...
            beast::get_lowest_layer(stream).expires_after(connection_timeout);
            beast::get_lowest_layer(stream).connect(results);

            writeRequest(stream, req);
            return {};
        }

      private:
        auto writeRequest(beast::tcp_stream &stream, const Request &req) const -> error_code
        {
            // write timeout
            auto const &url = req.URL();
            auto req_ = http::message<true, http::buffer_body>{};
            req_.method(http::verb::get);
            req_.set(http::field::host, url.host_name());
            req_.set(http::field::user_agent, req.UserAgent());
            req_.target(url.encoded_target());

            beast::get_lowest_layer(stream).expires_after(write_timeout);
            error_code errc;
            http::write(stream, req_, errc);
            return errc;
        }

        net::io_context &ioc;
        std::chrono::seconds connection_timeout = std::chrono::seconds{DEFAULT_CONNECT_TIMEOUT};
        std::chrono::seconds write_timeout = std::chrono::seconds{DEFAULT_WRITE_TIMEOUT};
    };

    Session::Session() = default;

    Session::~Session() = default;

    auto Session::Do(Request req) -> Result<Response>
    {
        auto result = pImpl->Do(req);
        return {};
    }

} // namespace cup::http