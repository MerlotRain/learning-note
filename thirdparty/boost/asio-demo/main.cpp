#include <iostream>

#include "server.h"
#include "session.h"

#include <gflags/gflags.h>

DEFINE_int32(port, 8080, "Server port number");
DEFINE_string(log_dir, "./logs", "Log directory path");

int main(int argc, char *argv[])
{
    gflags::SetUsageMessage("Usage: " + std::string(argv[0]) +
                            " --port=<port> --log_dir=<path>\n"
                            "Example:\n"
                            "  " +
                            std::string(argv[0]) +
                            " --port=8080 --log_dir=/var/log/myserver");

    try
    {
        gflags::ParseCommandLineFlags(&argc, &argv, true);
        if (FLAGS_port <= 0 || FLAGS_log_dir.empty())
        {
            std::cerr << "Error: --port and --log_dir are required.\n\n";
            std::cerr << gflags::ProgramUsage();
            return 1;
        }

        std::cout << "Server will start on port: " << FLAGS_port << std::endl;
        std::cout << "Log directory: " << FLAGS_log_dir << std::endl;

        net::io_context io_context;
        Server server(io_context, FLAGS_port);
        io_context.run();
    }
    catch (std::exception const &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}