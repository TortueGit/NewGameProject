#include "Logger.h"

Logger* g_logger;

Logger::Logger() {
	m_logLevel = LogLevel::Debug;
}

void Logger::log(LogLevel level, const std::string& source, const std::string& message) const {
	if (level <= m_logLevel && level != LogLevel::None) {
		std::string levelString;
		std::string color;
		switch (level) {
		case LogLevel::Debug:
			levelString = "[DEBUG]";
			color = GREEN;
			break;
		case LogLevel::Info:
			levelString = "[INFO]";
			color = DEFAULT;
			break;
		case LogLevel::Warning:
			levelString = "[WARNING]";
			color = YELLOW;
			break;
		case LogLevel::Error:
			levelString = "[ERROR]";
			color = RED;
			break;
		case LogLevel::Verbose:
			levelString = "[VERBOSE]";
			color = BLUE;
			break;
		default:
			return;
		}

		std::cout << color << levelString << "-[" << source << "]: " << message << DEFAULT << std::endl;
	}
}

void Logger::logError(const std::string& source, const std::string& message) const {
	log(LogLevel::Error, source, message);
}

void Logger::logWarning(const std::string& source, const std::string& message) const {
	log(LogLevel::Warning, source, message);
}

void Logger::logInfo(const std::string& source, const std::string& message) const {
	log(LogLevel::Info, source, message);
}

void Logger::setLogLevel(LogLevel level) {
	m_logLevel = level;
}

LogLevel Logger::getLogLevel() const {
	return m_logLevel;
}

