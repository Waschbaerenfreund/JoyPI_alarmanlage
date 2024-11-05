#include <iostream>
#include <fstream>
#include <string>
#include <fmt/core.h>


class WS2812 
{ 
	public:

	WS2812();
	~WS2812();

	void setup(int channel=0,int led_count=64, int type=3, int invert=0,int brightness=255,int GPIO=12);
	void init();
	void render(int channel=0);
	void random(int channel=0, int start=0, int len=-1);
	void fill(int channel=0,unsigned int fill_color=0,int start=0,int len=-1,char op=0);
	void rainbow(int channel=0,int count=1,int start=0,int stop=255,int startled=0,int len=0);
	void reset();
	
	private:   
	    // Ausgabestream für die Named Pipe
		std::ofstream pipe;
		void send(std::string message);
		bool _debug = false;
};

