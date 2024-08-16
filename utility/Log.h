#ifndef LOG_H
#define LOG_H
#include <Poco/ConsoleChannel.h>
#include <Poco/FormattingChannel.h>
#include <Poco/PatternFormatter.h>

// Logger 채널 설정 (ConsoleChannel 사용)
static Poco::AutoPtr<Poco::ConsoleChannel> consoleChannel(new Poco::ConsoleChannel);
static Poco::AutoPtr<Poco::PatternFormatter> patternFormatter(new Poco::PatternFormatter( "%Y-%m-%d %H:%M:%S [%p] %s: %t"));
static Poco::AutoPtr<Poco::FormattingChannel> formattingChannel(new Poco::FormattingChannel(patternFormatter, consoleChannel));
#endif