/*
 * Copyright 2013-2018, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes

//Project Includes
#include "corvusoft/restbed/rule.hpp"
#include "corvusoft/restbed/detail/rule_impl.hpp"

//External Includes

//System Namespaces
using std::unique_ptr;
using std::shared_ptr;

//Project Namespaces
using restbed::detail::RuleImpl;

//External Namespaces

namespace restbed
{
    bool Rule::condition( const shared_ptr< Session > )
    {
        return true;
    }
    
    int Rule::get_priority( void ) const
    {
        return m_pimpl->m_priority;
    }
    
    void Rule::set_priority( const int value )
    {
        m_pimpl->m_priority = value;
    }
    
    Rule::Rule( void ) : m_pimpl( new RuleImpl )
    {
        return;
    }
    
    Rule::~Rule( void )
    {
        return;
    }
}
