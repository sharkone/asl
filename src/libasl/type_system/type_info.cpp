#include "precomp/precomp.h"

#include "type_system/type_info.h"

namespace asl
{
    type_info::type_info(const type_manager& type_manager, const std::string& name, internal_type internal_type)
        :   m_type_manager(type_manager)
        ,   m_name(name)
        ,   m_internal_type(internal_type)
    {
    }

    const type_manager& type_info::get_type_manager() const
    {
        return (m_type_manager);
    }

    const std::string& type_info::get_name() const
    {
        return (m_name);
    }

    type_info::internal_type type_info::get_internal_type() const
    {
        return (m_internal_type);
    }

    bool type_info::is_bool() const
    {
        return (m_internal_type == IT_BOOL);
    }

    bool type_info::is_uint() const
    {
        return (m_internal_type == IT_UINT);
    }

    value::ptr_type type_info::create_value() const
    {
        return (boost::make_shared<value>(*this));
    }

    void type_info::dump() const
    {
        //if (m_super != NULL)
        //    ASL_LOG(" * %s (%s)", m_name.c_str(), m_super->get_name().c_str());
        //else
            ASL_LOG(" * %s", m_name.c_str());

        //for (method_map_type::const_iterator it = m_methods.begin(); it != m_methods.end(); ++it)
        //    it->second->dump();
    }

    std::string type_info::to_string(const value& value) const
    {
        ASL_ASSERT(value.get_type() == *this);

        switch (m_internal_type)
        {
        case IT_BOOL:
            return ((value.get_bool() == true) ? "true" : "false");
        case IT_UINT:
            return (boost::lexical_cast<std::string>(value.get_uint()));
        }
        return ("<invalid>");
    }

    bool type_info::operator ==(const type_info& rhs) const
    {
        if (m_internal_type != rhs.m_internal_type)
            return (false);

        // TODO: Use hash instead
        if (m_name != rhs.m_name)
            return (false);

        return (true);
    }
}
