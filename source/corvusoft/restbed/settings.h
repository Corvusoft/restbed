/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

#ifndef _RESTBED_SETTINGS_H
#define _RESTBED_SETTINGS_H 1

//System Includes
#include <map>
#include <memory>
#include <string>

//Project Includes

//External Includes

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    enum Mode :
    int;
    
    namespace detail
    {
        class SettingsImpl;
    }
    
    class Settings
    {
        public:
            //Friends
            
            //Definitions
            
            //Constructors
            Settings( void );
            
            Settings( const Settings& original );
        
            Settings( const detail::SettingsImpl& implementation );
            
            virtual ~Settings( void );
            
            //Functionality
            
            //Getters
            Mode get_mode( void ) const;
            
            uint16_t get_port( void ) const;
            
            std::string get_root( void ) const;
            
            int get_maximum_connections( void ) const;
            
            std::string get_property( const std::string& name ) const;
            
            std::map< std::string, std::string > get_properties( void ) const;
            
            //Setters
            void set_mode( const Mode value );
            
            void set_port( const uint16_t value );
            
            void set_root( const std::string& value );
            
            void set_maximum_connections( const int value );
            
            void set_property( const std::string& name, const std::string& value );
            
            void set_properties( const std::map< std::string, std::string >& values );
            
            //Operators
            Settings& operator =( const Settings& value );
            
            //Properties
            
        protected:
            //Friends
            
            //Definitions
            
            //Constructors
            
            //Functionality
            
            //Getters
            
            //Setters
            
            //Operators
            
            //Properties
            
        private:
            //Friends
            
            //Definitions
            
            //Constructors
            
            //Functionality
            
            //Getters
            
            //Setters
            
            //Operators
            
            //Properties
            std::unique_ptr< detail::SettingsImpl > m_pimpl;
    };
}

#endif  /* _RESTBED_SETTINGS_H */
