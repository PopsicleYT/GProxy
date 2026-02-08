#include <Geode/Geode.hpp>
#include <Geode/modify/GameLevelManager.hpp>

using namespace geode::prelude;

const std::string PROXY_BASE = "https://the.goon.lat/lumi/nal/";

$on_mod(Loaded) {
    log::info("=================================");
    log::info("GProxy mod loaded successfully!");
    log::info("Proxy: {}", PROXY_BASE);
    log::info("=================================");
}

class $modify(MyGameLevelManager, GameLevelManager) {
    
    void ProcessHttpRequest(gd::string endpoint, gd::string params, gd::string tag, GJHttpType httpType) {
        std::string originalUrl = std::string(endpoint);
        log::info("ProcessHttpRequest called with: {}", originalUrl);
        
        if (originalUrl.find("boomlings.com") != std::string::npos || 
            originalUrl.find("robtopgames.com") != std::string::npos) {
            
            std::string newUrl = PROXY_BASE + originalUrl;
            endpoint = newUrl;
            
            log::info("REDIRECTED: {} -> {}", originalUrl, newUrl);
        }
        
        GameLevelManager::ProcessHttpRequest(endpoint, params, tag, httpType);
    }
    
    void getOnlineLevels(GJSearchObject* searchObj) {
        log::info("getOnlineLevels called!");
        GameLevelManager::getOnlineLevels(searchObj);
    }
    
    void downloadLevel(int levelID, bool unknown) {
        log::info("downloadLevel called for ID: {}", levelID);
        GameLevelManager::downloadLevel(levelID, unknown);
    }
};
