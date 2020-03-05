#include "VideoBank.h"

void VideoBank::loadVideos() {
	// Get the absolute path relative to videos.
	string path = ofFilePath::getAbsolutePath("videos", true); // Path relative to the current directory.
	ofDirectory dir(path);
	dir.allowExt("mp4");
	// Populate dir object.
	dir.listDir();

	// All files should be loaded now.
	for (auto file : dir.getFiles()) {
		ofVideoPlayer video; video.load(file.getAbsolutePath());
		videos.push_back(video);
	}
}

int VideoBank::getVideoCount() {
	return this->videos.size();
}

ofVideoPlayer &VideoBank::getVideoPlayer(int idx) {
	return this->videos[idx];
}

// Create a new instance
VideoBank &VideoBank::instance() {
  return bank;
}

// For a static class, variable needs to be
// initialized in the implementation file.
VideoBank VideoBank::bank;
