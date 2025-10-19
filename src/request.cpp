//
// Created by Vasyl Zaichenko on 19.10.2025.
//

#include "request.h"

namespace cup::http
{
    auto Request::URL() const & -> const boost::url &
    {
        return m_url;
    }

    auto Request::UserAgent() const & -> const std::string &
    {
        return m_userAgent;
    }

    auto Request::Method() const & -> const http::Method &
    {
        return m_method;
    }

    [[nodiscard]] auto Request::Body() const & -> const std::optional<Bytes> &
    {
        return m_body;
    }

} // namespace cup::http