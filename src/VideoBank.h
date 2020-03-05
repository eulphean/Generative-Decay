// Singleton pattern for loading videos.
// Seems like this video bank maybe have to be multithreaded
// because more videos are active, the more computation access
// it needs. 
#pragma once
#include "ofMain.h"

class VideoBank {
  public:
    void loadVideos();
    int getVideoCount();
    ofVideoPlayer &getVideoPlayer(int idx); 
    static VideoBank &instance();
    
  private:
		std::vector<ofVideoPlayer> videos;
    static VideoBank bank;
};
