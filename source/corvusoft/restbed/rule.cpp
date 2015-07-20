/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes

//Project Includes
#include "corvusoft/restbed/rule.hpp"
#include "corvusoft/restbed/session.hpp"
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
    Rule::Rule( const Rule::Type type ) : m_pimpl( new RuleImpl( type ) )
    {
        return;
    }
    
    Rule::Rule( const Rule& original ) : m_pimpl( new RuleImpl( *original.m_pimpl ) )
    {
        return;
    }

    Rule::~Rule( void )
    {
        return;
    }

    bool Rule::is_mandatory( void ) const
    {
    	return m_pimpl->is_mandatory( );
    }

    Rule::Type Rule::get_type( void ) const
    {
    	return m_pimpl->get_type( );
    }

    int Rule::get_priority( void ) const
    {
    	return m_pimpl->get_priority( );
    }

    void Rule::set_priority( const int value )
    {
    	m_pimpl->set_priority( value );
    }

    void Rule::set_mandatory( const bool value )
    {
    	m_pimpl->set_mandatory( value );
    }

    Rule& Rule::operator =( const Rule& value )
    {
        *m_pimpl = *value.m_pimpl;

        return *this;
    }

    bool Rule::operator >( const Rule& value ) const
    {
        return *m_pimpl > *value.m_pimpl;
    }

    bool Rule::operator <( const Rule& value ) const
    {
        return *m_pimpl < *value.m_pimpl;
    }

    bool Rule::operator ==( const Rule& value ) const
    {
        return *m_pimpl == *value.m_pimpl;
    }

    bool Rule::operator !=( const Rule& value ) const
    {
        return *m_pimpl != *value.m_pimpl;
    }
}
