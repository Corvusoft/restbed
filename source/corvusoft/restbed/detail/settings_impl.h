/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

#ifndef _RESTBED_DETAIL_SETTINGS_IMPL_H
#define _RESTBED_DETAIL_SETTINGS_IMPL_H 1

//System Includes
#include <map>
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
        //Forward Declarations
        
        class SettingsImpl
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                SettingsImpl( void );
                
                SettingsImpl( const SettingsImpl& original );
                
                virtual ~SettingsImpl( void );
                
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
                SettingsImpl& operator =( const SettingsImpl& value );
                
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
                std::map< std::string, std::string > m_properties;
        };
    }
}

#endif  /* _RESTBED_DETAIL_SETTINGS_IMPL_H */
