#include "ws2812.h"


WS2812::WS2812()
{

    // Der Pfad zur Named Pipe
    std::string pipePath = "/dev/leds";
    
    // Öffnen der Named Pipe im Schreibmodus
    pipe.open(pipePath.c_str());
    
    if (!pipe.is_open()) {
        throw std::runtime_error("Fehler beim Öffnen der Pipe: " + pipePath);
    }
   
 
}

WS2812::~WS2812()
{
    // Schließen des Streams
	pipe.close();
}

void WS2812::send(std::string message){
    // Schreiben der Nachricht in die Pipe
    pipe << message << std::endl;
    if(_debug){
        std::cout << message << std::endl;
    }
}

void WS2812::setup( int channel, int led_count, int type, int invert, int brightness, int GPIO)
{
    // Die Nachricht, die geschrieben werden soll
    std::string message = "setup " + std::to_string(channel) + "," 
                                  + std::to_string(led_count) + "," 
                                  + std::to_string(type) + "," 
                                  + std::to_string(invert) + "," 
                                  + std::to_string(brightness) + "," 
                                  + std::to_string(GPIO); 
    // Schreiben der Nachricht in die Pipe
    send(message);
}

void WS2812::init()
{
    // Die Nachricht, die geschrieben werden soll
    std::string message = "init";
    // Schreiben der Nachricht in die Pipe
    send(message);
}

void WS2812::render(int channel)
{
    // Die Nachricht, die geschrieben werden soll
    std::string message = "render " + std::to_string(channel);
    // Schreiben der Nachricht in die Pipe
    send(message);
}

void WS2812::random(int channel, int start, int len)
{
    // Die Nachricht, die geschrieben werden soll
    std::string message = "random " + std::to_string(channel) + "," 
                                  + std::to_string(start) + "," 
                                  + std::to_string(len); 
    // Schreiben der Nachricht in die Pipe
    send(message);
}

void WS2812::fill(int channel,unsigned int fill_color,int start,int len,char op)
{
    // Die Nachricht, die geschrieben werden soll
    std::string message = "fill " + std::to_string(channel) + "," 
                                  + fmt::format("{:06x}", fill_color) + "," 
                                  + std::to_string(start) + "," 
                                  + std::to_string(len) + "," 
                                  + std::to_string(op); 
    // Schreiben der Nachricht in die Pipe
    send(message);
}

void WS2812::rainbow(int channel,int count,int start,int stop,int startled,int len)
{
    // Die Nachricht, die geschrieben werden soll
    std::string message = "rainbow " + std::to_string(channel) + "," 
                                  + std::to_string(count) + "," 
                                  + std::to_string(start) + "," 
                                  + std::to_string(stop) + "," 
                                  + std::to_string(startled) + "," 
                                  + std::to_string(len);
    // Schreiben der Nachricht in die Pipe
    send(message);
}

void WS2812::reset()
{
    // Die Nachricht, die geschrieben werden soll
    std::string message = "reset";
    // Schreiben der Nachricht in die Pipe
    send(message);
}
