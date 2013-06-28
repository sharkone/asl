#pragma once

#include "context/vm/value.h"

namespace asl
{
    class type_manager;

    class type_info : public boost::noncopyable
    {
    public:
        enum internal_type
        {
            IT_BOOL   = 0x00000000,
            IT_UINT   = 0x00000001
        };

        type_info(const type_manager& type_manager, const std::string& name, internal_type internal_type);

        const type_manager& get_type_manager() const;
        const std::string&  get_name() const;
        internal_type       get_internal_type() const;

        bool                is_bool() const;
        bool                is_uint() const;

        value::ptr_type     create_value() const;
        void                dump() const;
        std::string         to_string(const value& value) const;

        bool                operator ==(const type_info& rhs) const;

    private:
        const type_manager& m_type_manager;
        std::string         m_name;
        internal_type       m_internal_type;
    };
}
