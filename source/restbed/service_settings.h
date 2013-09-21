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

#ifndef _RESTBED_SERVICE_SETTINGS_H
#define _RESTBED_SERVICE_SETTINGS_H 1

//System Includes
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
        class ServiceSettingsImpl;
    }

    class ServiceSettings
    {
        public:
            //Friends
            
            //Definitions

            //Constructors
            ServiceSettings( void );
            
            ServiceSettings( const ServiceSettings& original );
            
            virtual ~ServiceSettings( void );
            
            //Functionality

            //Getters
            uint16_t get_port( void ) const;

            std::string get_root( void ) const;

            //Setters  
            void set_port( const uint16_t value );
            
            void set_root( const std::string& value ); //needs validation

            //Operators
            bool operator <( const ServiceSettings& rhs ) const;
            
            bool operator >( const ServiceSettings& rhs ) const;
            
            bool operator ==( const ServiceSettings& rhs ) const;
            
            bool operator !=( const ServiceSettings& rhs ) const;

            ServiceSettings& operator =( const ServiceSettings& rhs );

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
            std::unique_ptr< detail::ServiceSettingsImpl > m_pimpl;
    };
}

#endif  /* _RESTBED_SERVICE_SETTINGS_H */
