/*
 * Site: restbed.corvusoft.co.uk
 * Author: Ben Crowhurst
 *
 * Copyright (c) 2013 Restbed Core Development Team and Community Contributors
 *
 * This file is part of Restbed.
 *
 * Restbed is free software: you can redistribute it and/or modify
 * it under the terms of the Lesser GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Restbed is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * Lesser GNU General Public License for more details.
 *
 * You should have received a copy of the Lesser GNU General Public License
 * along with Restbed.  If not, see <http://www.gnu.org/licenses/>.
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
    namespace detail
    {
        class SettingsImpl;
    }

    class Settings //add readonly funcationality, and add map constructor (remember uppercase!). + ServiceSettings, ReourceSettings
    {
        public:
            //Friends
            
            //Definitions

            //Constructors
            Settings( void );
            
            Settings( const Settings& original );
            
            virtual ~Settings( void );
            
            //Functionality

            //Getters
            uint16_t get_port( void ) const;

            std::string get_root( void ) const;

            std::string get_property( const std::string& name ) const;

            std::map< std::string, std::string > get_properties( void ) const;

            //Setters  
            void set_port( const uint16_t value );
            
            void set_root( const std::string& value ); //needs validation
            
            void set_property( const std::string& name, const std::string& value );
            
            void set_properties( const std::map< std::string, std::string >& values );

            //Operators
            Settings& operator =( const Settings& rhs );

            bool operator <( const Settings& rhs ) const;
            
            bool operator >( const Settings& rhs ) const;
            
            bool operator ==( const Settings& rhs ) const;
            
            bool operator !=( const Settings& rhs ) const;

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
