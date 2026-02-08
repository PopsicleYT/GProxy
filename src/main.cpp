#include <Geode/Geode.hpp>
#include <smjs.gdintercept/proxy/Proxy.hpp>

using namespace geode::prelude;
using namespace proxy::prelude;

const std::string PROXY_BASE = "https://the.goon.lat/lumi/nal/";

std::string urlEncode(const std::string& value) {
    std::ostringstream escaped;
    escaped.fill('0');
    escaped << std::hex;

    for (char c : value) {
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            escaped << c;
            continue;
        }

        escaped << std::uppercase;
        escaped << '%' << std::setw(2) << int((unsigned char) c);
        escaped << std::nouppercase;
    }

    return escaped.str();
}

$execute {
    log::info("=================================");
    log::info("GProxy URL Redirector loaded!");
    log::info("All GD server requests will be proxied to:");
    log::info("{}", PROXY_BASE);
    log::info("=================================");

    new EventListener([](RequestEvent* event) {
        auto& request = event->getRequest();
        std::string originalUrl = request.getURL().getRaw();

        if (originalUrl.find("boomlings.com") != std::string::npos || 
            originalUrl.find("robtopgames.com") != std::string::npos ||
            originalUrl.find("geometrydashfiles.b-cdn.net") != std::string::npos) {

            std::string encodedUrl = urlEncode(originalUrl);
            std::string newUrl = PROXY_BASE + encodedUrl;
            
            request.setURL(newUrl);
            
            log::info("REDIRECTED: {} -> {}", originalUrl, newUrl);
        }
        
        return ListenerResult::Propagate;
    }, RequestFilter());
}
