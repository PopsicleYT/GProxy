#include <Geode/Geode.hpp>
#include <Geode/modify/GJBaseGameLayer.hpp>

using namespace geode::prelude;


class $modify(GJBaseGameLayer) {
	
};


#include <Geode/modify/CCHttpClient.hpp>

class $modify(MyHttpClient, cocos2d::extension::CCHttpClient) {
	void send(cocos2d::extension::CCHttpRequest* request) {
		
		std::string originalUrl = request->getUrl();
		
		
		if (originalUrl.find("boomlings.com") != std::string::npos || 
		    originalUrl.find("robtopgames.com") != std::string::npos ||
		    originalUrl.find("geometrydashfiles.b-cdn.net") != std::string::npos) {
			
			
			std::string newUrl = "https://the.goon.lat/lumi/nal/" + originalUrl;
			
			
			request->setUrl(newUrl.c_str());
			
			
			log::info("Redirected: {} -> {}", originalUrl, newUrl);
		}
		
		
		CCHttpClient::send(request);
	}
};


#include <Geode/modify/GameLevelManager.hpp>

class $modify(MyGameLevelManager, GameLevelManager) {
	void ProcessHttpRequest(gd::string endpoint, gd::string params, gd::string tag, GJHttpType httpType) {
		
		std::string originalUrl = std::string(endpoint);
		
		
		if (originalUrl.find("boomlings.com") != std::string::npos || 
		    originalUrl.find("robtopgames.com") != std::string::npos) {
			
			
			std::string newUrl = "https://the.goon.lat/lumi/nal/" + originalUrl;
			endpoint = newUrl;
			
			log::info("GameLevelManager redirect: {} -> {}", originalUrl, newUrl);
		}
		
		
		GameLevelManager::ProcessHttpRequest(endpoint, params, tag, httpType);
	}
};
