#include "precomp/precomp.h"

#include "type_system/type_manager.h"

namespace asl
{
    type_manager::type_manager()
    {
        m_bool_type = add_type("bool", type_info::IT_BOOL);
        m_uint_type = add_type("uint", type_info::IT_UINT);
    }

    type_manager::~type_manager()
    {
    }

    type_info* type_manager::add_type(const std::string& name, type_info::internal_type internal_type)
    {
        ASL_ASSERT(m_types.find(name) == m_types.end());

        type_info*  type      = new type_info(*this, name, internal_type);
        std::string type_name = name;
        m_types.insert(type_name, type);

        return (type);
    }

    void type_manager::dump_types() const
    {
        ASL_LOG("available types:");
        ASL_LOG("================");
        for (type_map_type::const_iterator it = m_types.begin(); it != m_types.end(); ++it)
            it->second->dump();
    }

    value::ptr_type type_manager::create_value_bool(bool value) const
    {
        value::ptr_type result = m_bool_type->create_value();
        result->set_bool(value);
        return (result);
    }

    value::ptr_type type_manager::create_value_uint(unsigned int value) const
    {
        value::ptr_type result = m_uint_type->create_value();
        result->set_uint(value);
        return (result);
    }
}
