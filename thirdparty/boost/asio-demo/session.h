#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast.hpp>
#include <boost/beast/http.hpp>
#include <boost/bind/bind.hpp>
#include <memory>

namespace beast = boost::beast;
namespace http = beast::http;
using tcp = boost::asio::ip::tcp;


class Session : public std::enable_shared_from_this<Session>
{
public:
    explicit Session(tcp::socket socket);
    void start();

private:
    void read_request();
    void handle_read(beast::error_code ec, size_t bytes_transferred);
    void process_request();
    void handle_not_found();
    void handle_bad_request();
    void write_response();

private:
    tcp::socket socket_;
    beast::flat_buffer buffer_;
    http::request<http::string_body> req_;
    http::response<http::string_body> res_;
};