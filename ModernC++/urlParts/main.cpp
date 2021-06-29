#include <iostream>
#include <optional>
#include <regex>

using namespace std;

struct uri_parts {
    string protocol;
    string domain;
    optional<int> port;
    optional<string> path;
    optional<string> query;
    optional<string> fragment;
};

optional<uri_parts> parse_uri(string url) {
    regex rx(R"(^(\w+):\/\/([\w.-]+)(:(\d+))?)"
             R"(([\w/\.]+)?(\?([\w=&]*)(#?(\w+))?)?$)");
     auto matches = smatch{};
    if (regex_match(url, matches, rx)) {
        if (matches[1].matched && matches[2].matched) {
            uri_parts parts;
            parts.protocol = matches[1].str();
            parts.domain = matches[2].str();
            if (matches[4].matched)
                parts.port = stoi(matches[4]);
            if (matches[5].matched)
                parts.path = matches[5];
            if (matches[7].matched)
                parts.query = matches[7];
            if (matches[9].matched)
                parts.fragment = matches[9];

            return parts;
        }
    }

    return {};
}

int main() {
    auto p1 = parse_uri("https://packt.com");
    assert(p1.has_value());
    assert(p1->protocol == "https");
    assert(p1->domain == "packt.com");
    assert(!p1->port.has_value());
    assert(!p1->path.has_value());
    assert(!p1->query.has_value());
    assert(!p1->fragment.has_value());

    auto p2 = parse_uri("https://bbc.com:80/en/index.html?lite=true#ui");
    assert(p2.has_value());
    assert(p2->protocol == "https");
    assert(p2->domain == "bbc.com");
    assert(p2->port.value() == 80);
    assert(p2->path == "/en/index.html");
    assert(p2->query.value() == "lite=true");
    assert(p2->fragment.value() == "ui");

    auto p3 = parse_uri("aaaaa.com");
    assert(!p3.has_value());
    assert(p3 == nullopt);

    return 0;
}
