//System Includes
#include <memory>
#include <cstdarg>

//Project Includes
#include <corvusoft/restbed/logger.hpp>
#include <corvusoft/restbed/web_socket.hpp>

//External Includes
#include <catch2/catch_all.hpp>
#include <catch2/catch_session.hpp>

//System Namespaces
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using restbed::Logger;
using restbed::Settings;
using restbed::WebSocket;

//External Namespaces

namespace
{
    class CountingLogger : public Logger
    {
        public:
            void stop( void ) override
            {
                return;
            }

            void start( const shared_ptr< const Settings >& ) override
            {
                return;
            }

            void log( const Level level, const char*, ... ) override
            {
                if ( level == Logger::WARNING )
                {
                    m_warnings++;
                }
            }

            void log_if( bool expression, const Level level, const char* format, ... ) override
            {
                ( void ) format;

                if ( expression )
                {
                    log( level, "" );
                }
            }

            int m_warnings = 0;
    };
}

TEST_CASE( "destroying a WebSocket does not log a spurious wind-down warning", "[web_socket]" )
{
    auto logger = make_shared< CountingLogger >( );

    {
        auto socket = make_shared< WebSocket >( );
        socket->set_logger( logger );
    }

    // The destructor's graceful wind-down must not call shared_from_this( ),
    // which throws std::bad_weak_ptr while the object is being destroyed and
    // produces a misleading WARNING on every destruction.
    REQUIRE( logger->m_warnings == 0 );
}

int main( int argc, char* argv[] )
{
    return Catch::Session( ).run( argc, argv );
}
