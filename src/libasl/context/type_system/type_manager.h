#pragma once

#include "context/type_system/type_info.h"

namespace asl
{
    class type_manager
    {
    public:
        type_manager();
        ~type_manager();

        type_info*                                      add_type(const std::string& name, type_info::internal_type internal_type);
        void                                            dump_types() const;

        value::ptr_type                                 create_value_bool(bool value) const;
        value::ptr_type                                 create_value_uint(unsigned int value) const;

    private:
        typedef boost::ptr_map<std::string, type_info>  type_map_type;
        type_map_type                                   m_types;

        type_info*                                      m_bool_type;
        type_info*                                      m_uint_type;
    };
}
