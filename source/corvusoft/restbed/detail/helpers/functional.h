/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

#ifndef _RESTBED_DETAIL_HELPER_FUNCTIONAL_H
#define _RESTBED_DETAIL_HELPER_FUNCTIONAL_H 1

//System Includes
#include <functional>

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
        //Forward Declarations
        
        namespace helpers
        {
            //Forward Declarations
            
            class Functional
            {
                public:
                    //Friends
                    
                    //Definitions
                    typedef std::size_t address_type;
                    
                    //Constructors
                    
                    //Functionality
                    template< typename Type, typename... Arguments >
                    static address_type get_address( std::function< Type( Arguments... ) > function )
                    {
                        typedef Type( function_decl )( Arguments... );
                        
                        function_decl** ptr = function.template target< function_decl* >( );
                        
                        address_type address = ( ptr not_eq nullptr ) ? ( address_type ) * ptr : 0;
                        
                        return address;
                    }
                    
                    //Getters
                    
                    //Setters
                    
                    //Operators
                    
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
                    Functional( void ) = delete;
                    
                    Functional( const Functional& original ) = delete;
                    
                    virtual ~Functional( void ) = delete;
                    
                    //Functionality
                    
                    //Getters
                    
                    //Setters
                    
                    //Operators
                    Functional& operator =( const Functional& rhs ) = delete;
                    
                    //Properties
            };
        }
    }
}

#endif  /* _RESTBED_DETAIL_HELPER_FUNCTIONAL_H */
