#include <Arduino.h>
#include <logger.h>

Logger& logger = Logger::getLogger();

void setup()
{
    Serial.begin(115200);
    Serial << "Ready" << endl;
    
    logger.enable();
    logger.logLevel(LogLevel::Debug);
    
    DebugLog(logger) << "setup complete" << endl;

    logger.logLevel(LogLevel::information);
}

void loop()
{
    FunctionLog(logger) << "loop() starts here" << endl;

    // do something 
    delay(1000);

    InfoLog(logger) << "this is information" << endl;
}
