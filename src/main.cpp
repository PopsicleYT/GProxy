#include <Geode/Geode.hpp>
#include <smjs.gdintercept/proxy/Proxy.hpp>
#include <sstream>
#include <iomanip>

using namespace geode::prelude;
using namespace proxy::prelude;

const std::string PROXY_BASE = "https://the.goon.lat/lumi/nal/";

std::string urlEncode(const std::string& value) {
    static const char hex[] = "0123456789ABCDEF";
    std::string result;
    result.reserve(value.size() * 3);

    for (unsigned char c : value) {
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            result += c;
        } else {
            result += '%';
            result += hex[c >> 4];
            result += hex[c & 15];
        }
    }

    return result;
}

$execute {
    log::info("=================================");
    log::info("GProxy URL Redirector loaded!");
    log::info("All GD server requests will be proxied to:");
    log::info("{}", PROXY_BASE);
    log::info("=================================");
    
    // Intercept all HTTP requests and redirect GD server URLs
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
