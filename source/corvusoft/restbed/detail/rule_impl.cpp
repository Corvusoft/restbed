/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes

//Project Includes
#include "corvusoft/restbed/session.hpp"
#include "corvusoft/restbed/detail/rule_impl.hpp"

//External Includes

//System Namespaces

//Project Namespaces
using restbed::detail::RuleImpl;

//External Namespaces

namespace restbed
{
    namespace detail
    {
        RuleImpl::RuleImpl( const Rule::Type type ) : m_priority( 0 ),
            m_mandatory( false ),
            m_type( type )
        {
            return;
        }
        
        RuleImpl::RuleImpl( const RuleImpl& original ) : m_priority( original.m_priority ),
            m_mandatory( original.m_mandatory ),
            m_type( original.m_type )
        {
            return;
        }

        RuleImpl::~RuleImpl( void )
        {
            return;
        }

        bool RuleImpl::is_mandatory( void ) const
        {
            return m_mandatory;
        }

        Rule::Type RuleImpl::get_type( void ) const
        {
        	return m_type;
        }

        int RuleImpl::get_priority( void ) const
        {
        	return m_priority;
        }

        void RuleImpl::set_priority( const int value )
        {
        	m_priority = value;
        }

        void RuleImpl::set_mandatory( const bool value )
        {
        	m_mandatory = value;
        }

        RuleImpl& RuleImpl::operator =( const RuleImpl& value )
        {
        	m_type = value.m_type;
            m_priority = value.m_priority;
            m_mandatory = value.m_mandatory;

        	return *this;
        }
    }
}
