#pragma once

#include <expected>
#include <memory>
#include <system_error>

namespace cup::http
{

    template <typename T> using Result = std::expected<T, std::error_condition>;

    class Response;
    class Request;
    class Session
    {
        class Impl;

      public:
        Session();

        ~Session();

        [[nodiscard]] auto Do(Request req) -> Result<Response>;

      private:
        std::unique_ptr<Impl> pImpl{nullptr};
    };
} // namespace cup::http