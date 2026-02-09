#include <Geode/Geode.hpp>
#include <smjs.gdintercept/proxy/Proxy.hpp>

using namespace geode::prelude;
using namespace proxy::prelude;

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
    const std::string PROXY_BASE = "https://the.goon.lat/lumi/nal/";
    
    log::info("GProxy loaded - redirecting to proxy server");
    
    new EventListener([PROXY_BASE](RequestEvent* event) {
        auto& request = event->getRequest();
        std::string originalUrl = request.getURL().getRaw();
        
        if (originalUrl.find("boomlings.com") != std::string::npos || 
            originalUrl.find("robtopgames.com") != std::string::npos ||
            originalUrl.find("geometrydashfiles.b-cdn.net") != std::string::npos) {
            
            std::string encodedUrl = urlEncode(originalUrl);
            std::string newUrl = PROXY_BASE + encodedUrl;
            
            request.setURL(newUrl);
            
            log::info("URL redirected through proxy");
        }
        
        return ListenerResult::Propagate;
    }, RequestFilter());
}
