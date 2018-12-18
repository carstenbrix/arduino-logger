#include "logger.h"

Logger* Logger::instance_ = nullptr;

Logger::Logger()
    : timeStampFunc_(nullptr)
    , loggingEnabled_(false)
    , printer_(&Serial)
{
}

size_t Logger::write(uint8_t character) 
{
    if (loggingEnabled_) return printer_->write(character);
    return 0;
}

size_t Logger::write(const uint8_t* buffer, size_t size) 
{
    if (loggingEnabled_) return printer_->write(buffer, size);
    return 0;
}
