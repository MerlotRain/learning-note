#include <iostream>
#include <string>
#include <iomanip>

#include <absl/base/log_severity.h>
#include <absl/log/absl_check.h>
#include <absl/log/absl_log.h>

#include <absl/time/time.h>
#include <absl/time/clock.h>

#include <absl/flags/flag.h>

#include <absl/hash/hash.h>

#include <absl/container/flat_hash_map.h>

#include <absl/strings/str_cat.h>
#include <absl/strings/str_join.h>
#include <absl/strings/str_replace.h>
#include <absl/strings/str_format.h>
#include <absl/strings/ascii.h>
#include <absl/strings/numbers.h>

struct Point
{
    int x, y;

    bool operator==(const Point &other) const
    {
        return x == other.x && y == other.y;
    }
};

template <typename H>
H AbslHashValue(H h, const Point &p)
{
    return H::combine(std::move(h), p.x, p.y);
}

static void absl_string_test()
{
    std::vector<std::string> strings = {"Trion Model", "link:https://example.com", "code:1342", "expired:2023-10-01T12:00:00Z"};

    std::string joined = absl::StrJoin(strings, "\n");
    std::cout << "Joined strings:\n"
              << joined << std::endl;

    std::string name = "Alice";
    int age = 30;
    std::string greeting = absl::StrCat("Hello, ", name, "! You are ", age, " years old.");
    std::cout << "Greeting: " << greeting << std::endl;

    std::string text = "  \t  Hello, Abseil!   \n\n  ";

    absl::StripLeadingAsciiWhitespace(&text);
    std::cout << __LINE__ << " " << text << std::endl;

    absl::StripTrailingAsciiWhitespace(&text);
    std::cout << __LINE__ << " " << text << std::endl;

    std::string text2 = "  \t  Test  \n  ";
    absl::StripLeadingAsciiWhitespace(&text2);
    absl::StripTrailingAsciiWhitespace(&text2);
    std::cout << __LINE__ << " " << text2 << std::endl;

    std::string text3 = "  \t  Text3  \n  ";
    absl::StripAsciiWhitespace(&text3);
    std::cout << __LINE__ << " " << text3 << std::endl;
}

static void absl_string_numbers_test()
{
    std::string int_str = "12345";
    int int_value;
    bool success = absl::SimpleAtoi(int_str, &int_value);
    if (success)
    {
        std::cout << "Parsed int: " << int_value << std::endl;
    }

    std::string double_str = "3.141592657985";
    double double_value;
    success = absl::SimpleAtod(double_str, &double_value);
    if (success)
    {
        std::cout << "Parsed double: "  << std::fixed << std::setprecision(17) << double_value << std::endl;
    }

    int num = 12345;
    std::string num_str = absl::StrCat(num);
    std::cout << "Number to string: " << num_str << std::endl;

    std::string num2 = "12345.678915364963";
    std::string num_str2 = absl::StrCat(num2);
    std::cout << "Number to string: " << num_str2 << std::endl;
}

static void absl_hash_test()
{
    Point p1{10, 20};
    size_t hash = absl::Hash<Point>{}(p1);
    std::cout << "Hash of Point (10, 20): " << hash << std::endl;

    absl::flat_hash_map<Point, std::string> point_to_name;
    point_to_name[p1] = "Origin";
    point_to_name[Point{30, 40}] = "Far away";

    auto it = point_to_name.find(Point{10, 20});
    if (it != point_to_name.end())
    {
        std::cout << "Found :" << it->second << std::endl;
    }

    for (auto it = point_to_name.begin(); it != point_to_name.end(); ++it)
    {
        std::cout << "Point (" << it->first.x << ", " << it->first.y << "): " << it->second << std::endl;
    }
}

static void absl_time_test()
{
    absl::Time now = absl::Now();
    std::string time_str = "2023-10-01T12:00:00Z";
    std::string error_message;
    absl::ParseTime(absl::RFC3339_full, time_str, &now, &error_message);
    ABSL_LOG(INFO) << "Current time: " << now;

    now = absl::Now();

    std::string formatted = absl::FormatTime(absl::RFC3339_full, now, absl::LocalTimeZone());
    std::cout << "Current time: " << formatted << std::endl;
}

static void absl_log_test()
{
    int n = 10;
    ABSL_CHECK(n > 0) << "n must be greater than 10";
    ABSL_CHECK_EQ(n, 10) << "n must be equal to 10";

    ABSL_LOG(INFO) << "This is an info message";
    ABSL_LOG(WARNING) << "This is a warning";
    ABSL_LOG(ERROR) << "This is an error";
}

int main(int argc, char *argv[])
{

    absl_string_numbers_test();

    return 0;
}
