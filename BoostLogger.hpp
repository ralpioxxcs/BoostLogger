#ifndef BOOSTLOGGER_H
#define BOOSTLOGGER_H

// Boost Libraries
#define BOOST_ALL_DYN_LINK 1
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/format.hpp>
#include <boost/log/attributes/mutable_constant.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/attributes/timer.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/support/exception.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/manipulators/add_value.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>

namespace logging = boost::log;
namespace attrs = boost::log::attributes;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;

#define TRACE boost::log::trivial::trace
#define INFO logging::trivial::info
#define DEBUG logging::trivial::debug
#define WARNING logging::trivial::warning

#define REG_LOGGER Logger::RegisterLogger()
#define GET_LOGGER Logger::GetLogger()->GetInstance()

#define LOG(logger_, sev)                                                      \
  BOOST_LOG_SEV(logger_, sev)                                                  \
      << boost::log::add_value("Line", __LINE__)                               \
      << boost::log::add_value("File", __FILE__)                               \
      << boost::log::add_value("Function", BOOST_CURRENT_FUNCTION)

typedef src::severity_logger<logging::trivial::severity_level> LOGGER;

namespace SimpleLogger {

// trace, debug, info, warning, error, fatal
class Logger {
public:
  static void RegisterLogger() {
    if (m_pThis == nullptr) {
      m_pThis = new Logger;
    }
  }

  static Logger *GetLogger() {
    if (m_pThis == nullptr) {
      m_pThis = new Logger;
    } else {
      return m_pThis;
    }
    return m_pThis;
  }

  LOGGER &GetInstance() { return m_logger; }
  void SetLevel() { ; }

private:
  Logger() { init_logger(); }
  Logger(Logger const &rhs) { ; }
  Logger &operator=(Logger const &rhs) {
    m_logger = rhs.m_logger;
    m_pThis = rhs.m_pThis;
    return *this;
  }

  inline void init_logger() {
    // 로깅코어 get
    boost::shared_ptr<logging::core> core = logging::core::get();

    // backend 객체 생성
    boost::shared_ptr<sinks::text_file_backend> backend =
        boost::make_shared<sinks::text_file_backend>(
            keywords::file_name = "Log_%Y%m%d_%N.log", // 로그파일
            /*
             *  1 KiB = 1024 Bit
             *  1 MiB = 1024 KiB
             *  1 MiB = 1.04858 MB
             * */
            keywords::rotation_size =
                1 * 1024 * 1024, // 파일 사이즈 ( N * 1024 Bit * 1024 Bit )
            keywords::open_mode = (std::ios::out | std::ios::app),
            keywords::time_based_rotation =
                sinks::file::rotation_at_time_point(12, 0, 0));
    backend->auto_flush(true);

    // front end : synchronous_sink
    // back  end : text file backend
    typedef sinks::synchronous_sink<sinks::text_file_backend> text_sink;

    // 새로운 text file base 객체 할당
    boost::shared_ptr<text_sink> sink(new text_sink(backend));
    core->add_sink(sink);

    sink->set_formatter(&SimpleLogger::Logger::init_format);

    // 로그 레벨 설정
    core->set_filter(logging::trivial::severity >= logging::trivial::trace);

    // 로깅 속성값 적용
    logging::add_common_attributes();
  }

  static void init_format(logging::record_view const &rec,
                          logging::formatting_ostream &strm) {

    /*
                  [LineID]  [Timestamp]	        [func]  [Line]  [severity]
       [message]

            ex) [55] 20200802-10:13:52.24123 [main.cpp : 13] <debug> : log test
       insert
    */

    typedef boost::log::formatter formatter;
    formatter f = expr::stream
                  << expr::format_date_time<boost::posix_time::ptime>(
                         "TimeStamp", "%Y%m%d-%H:%M:%S");

    // custom value
    logging::value_ref<std::string> fullpath =
        logging::extract<std::string>("File", rec);
    logging::value_ref<unsigned int> line =
        logging::extract<unsigned int>("Line", rec);

    // format
    // strm << "[" << boost::format("%04d") % logging::extract<unsigned
    // int>("LineID", rec) <<"] ";
    f(rec, strm);
    strm << " [" << boost::filesystem::path(fullpath.get()).filename().string()
         << " : ";
    strm << boost::format("%03d") % logging::extract<int>("Line", rec) << "]";
    strm << " <" << rec[logging::trivial::severity] << ">";
    strm << " : " << rec[expr::smessage];
  }

  // member variable
  LOGGER m_logger;
  static Logger *m_pThis;
};

} // namespace SimpleLogger

SimpleLogger::Logger *SimpleLogger::Logger::m_pThis = nullptr;

#endif
