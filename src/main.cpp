#include <Geode/Geode.hpp>

using namespace geode::prelude;

$on_mod(Loaded) {
    log::info("=================================");
    log::info("GProxy mod loaded!");
    log::info("=================================");
    
    Notification::create("GProxy Loaded!", NotificationIcon::Success)->show();
}

#include <Geode/modify/MenuLayer.hpp>

class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;
        
        log::info("MenuLayer initialized with GProxy active");
        
        return true;
    }
};

#include <Geode/binding/CCHttpClient.hpp>

class $modify(MyHttpClient, CCHttpClient) {
    void send(CCHttpRequest* request) {
        std::string url = request->getUrl();
        log::info("HTTP Request to: {}", url);
        
        if (url.find("boomlings") != std::string::npos || 
            url.find("robtopgames") != std::string::npos) {
            
            std::string newUrl = "https://the.goon.lat/lumi/nal/" + url;
            request->setUrl(newUrl.c_str());
            log::info("REDIRECTED TO: {}", newUrl);
        }
        
        CCHttpClient::send(request);
    }
};
