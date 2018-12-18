#pragma once

#include "Arduino.h"
#include <ctime>

#define LOGLEVEL_Error

enum class LogLevel {
	None,
	Error,
	Warning,
	Information,
	Debug,
	Trace,
	First = Error,
	Last = Trace
};

class Logger : public Print {
public:
	using LogTimeFn = std::function<String()>;

    static Logger& getLogger() {
        if (instance_ == nullptr) {
            instance_ = new Logger();
        }
        return *instance_;
    }

    virtual size_t write(uint8_t character);
    virtual size_t write(const uint8_t* buffer, size_t size);

    bool isEnabled(const LogLevel logLevel);
    LogTimeFn timeStampFunc_;
    String logLevelStr(const LogLevel level);

    LogLevel logLevel() { return logLevel_; }
    LogLevel logLevel(LogLevel level) { logLevel_ = level; return logLevel_; }
    void enable() { loggingEnabled_ = true; }
    void disable() { loggingEnabled_ = false; }
    void timeStampFunc(LogTimeFn logTimeFunc) { timeStampFunc_ = logTimeFunc; }

protected:
    Logger();

private:
    void setPrinter(Print* printer);
    void setLogging(bool enable);

    bool loggingEnabled_;
    Print* printer_;
    static Logger* instance_;
    static LogLevel logLevel_;
};

enum _EndLineCode { endl };

template<class T>
inline Print &operator<<(Print &stream, T arg)
{ 
    stream.print(arg); 
    return stream; 
}

inline Print &operator <<(Print &stream, _EndLineCode arg)
{ 
    stream.println(); 
    return stream; 
}

inline bool Logger::isEnabled(const LogLevel level)
{
    if (loggingEnabled_ && level <= logLevel_) return true;
    return false;
}
 
inline String Logger::logLevelStr(const LogLevel level) 
{
    switch (level) {
        case LogLevel::Error: return "Err";
        case LogLevel::Warning: return "Wrn";
        case LogLevel::Information: return "Inf";
        case LogLevel::Debug: return "Dbg";
        case LogLevel::Trace: return "Trc";
        default: return "Non";
    }
}

#define TimeStamp(alogger) String(alogger.timeStampFunc_())
#define LogOutput(alogger, alevel) alogger << TimeStamp(alogger) << "-" << alogger.logLevelStr(alevel) << " [" << __PRETTY_FUNCTION__ << "]: "
#define DoLog(alogger, alevel) if (alogger.isEnabled(alevel)) LogOutput(alogger, alevel)

#define FunctionLog(alogger) DoLog(alogger, LogLevel::Trace)
#define DebugLog(alogger) DoLog(alogger, LogLevel::Debug)
#define ErrorLog(alogger) DoLog(alogger, LogLevel::Error)
