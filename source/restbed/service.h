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

#ifndef _RESTBED_SERVICE_H
#define _RESTBED_SERVICE_H 1

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
    class Request;
    class Resource;
    class Settings;

    enum LogLevel : int;

    namespace detail
    {
        class ServiceImpl;
    }

    class Service
    {
        public:
            //Friends
            
            //Definitions

            //Constructors
            Service( const Settings& settings );
            
            Service( const Service& original );

            virtual ~Service( void );

            //Functionality
            void start( void );

            void stop( void );

            void publish( const Resource& value );

            void suppress( const Resource& value );

            //Getters

            //Setters

            //Operators
            Service& operator =( const Service& rhs );

            bool operator <( const Service& rhs ) const;
            
            bool operator >( const Service& rhs ) const;
            
            bool operator ==( const Service& rhs ) const;
            
            bool operator !=( const Service& rhs ) const;

            //Properties
            
        protected:
            //Friends
            
            //Definitions
            
            //Constructors
            
            //Functionality
            virtual void error_handler( const Request& request );

            virtual bool authentication_handler( const Request& request );

            virtual void log_handler(  const LogLevel level, const std::string& format, ... );

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
            std::unique_ptr< detail::ServiceImpl > m_pimpl;
    };
}

#endif  /* _RESTBED_SERVICE_H */
