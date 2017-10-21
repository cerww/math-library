#pragma once
#include <chrono>

class timer {
public:
	void start(){
		startTime = std::chrono::high_resolution_clock::now();
	}
	template<typename duration>
	duration timeSinceStart()const{
		return std::chrono::duration_cast<duration>((std::chrono::high_resolution_clock::now() - startTime));
	}
private:
	std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();

};