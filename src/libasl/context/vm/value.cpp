#include "precomp/precomp.h"

#include "context/vm/value.h"

#include "context/context.h"
#include "context/type_system/type_info.h"

namespace asl
{
    value::value(const type_info& type)
        :   m_type(type)
    {
    }

    value::~value()
    {
    }

    const type_info& value::get_type() const
    {
        return (m_type);
    }

    bool value::is_bool() const
    {
        return (m_type.is_bool() == true);
    }

    bool value::get_bool() const
    {
        ASL_ASSERT(is_bool());
        return (m_bool);
    }

    void value::set_bool(bool value)
    {
        ASL_ASSERT(is_bool());
        m_bool = value;
    }

    bool value::is_uint() const
    {
        return (m_type.is_uint() == true);
    }

    unsigned int value::get_uint() const
    {
        ASL_ASSERT(is_uint());
        return (m_uint);
    }

    void value::set_uint(unsigned int value)
    {
        ASL_ASSERT(is_uint());
        m_uint = value;
    }

    std::string value::to_string() const
    {
        return (m_type.to_string(*this));
    }

    value::ptr_type value::operator ==(const value& rhs) const
    {
        return (binary_operator(rhs, OP_EQUAL));
    }

    value::ptr_type value::operator !=(const value& rhs) const
    {
        return (binary_operator(rhs, OP_NOT_EQUAL));
    }

    value::ptr_type value::operator >(const value& rhs) const
    {
        return (binary_operator(rhs, OP_GREATER));
    }

    value::ptr_type value::operator >=(const value& rhs) const
    {
        return (binary_operator(rhs, OP_GREATER_EQUAL));
    }

    value::ptr_type value::operator <(const value& rhs) const
    {
        return (binary_operator(rhs, OP_LESSER));
    }

    value::ptr_type value::operator <=(const value& rhs) const
    {
        return (binary_operator(rhs, OP_LESSER_EQUAL));
    }

    value::ptr_type value::operator +(const value& rhs) const
    {
        return (binary_operator(rhs, OP_ADD));
    }

    value::ptr_type value::operator -(const value& rhs) const
    {
        return (binary_operator(rhs, OP_SUB));
    }

    value::ptr_type value::operator *(const value& rhs) const
    {
        return (binary_operator(rhs, OP_MUL));
    }

    value::ptr_type value::operator /(const value& rhs) const
    {
        return (binary_operator(rhs, OP_DIV));
    }
        
    value::ptr_type value::binary_operator(const value& rhs, binary_op op) const
    {
        ASL_ASSERT(get_type() == rhs.get_type());

#define TEST_OP(in_type, out_type, symbol)                                                                                              \
        if (is_##in_type() == true)                                                                                                     \
        {                                                                                                                               \
            value::ptr_type result = get_type().get_type_manager().create_value_##out_type(get_##in_type() symbol rhs.get_##in_type()); \
            return (result);                                                                                                            \
        }

        switch (op)
        {
        case OP_EQUAL:
            {
                TEST_OP(bool, bool, ==)
                TEST_OP(uint, bool, ==)
                break;
            }
        case OP_NOT_EQUAL:
            {
                TEST_OP(bool, bool, !=)
                TEST_OP(uint, bool, !=)
                break;
            }
        case OP_GREATER:
            {
                TEST_OP(uint, bool, >)
                break;
            }
        case OP_GREATER_EQUAL:
            {
                TEST_OP(uint, bool, >=)
                break;
            }
        case OP_LESSER:
            {
                TEST_OP(uint, bool, <)
                break;
            }
        case OP_LESSER_EQUAL:
            {
                TEST_OP(uint, bool, <=)
                break;
            }
        case OP_ADD:
            {
                TEST_OP(uint, uint, +)
                break;
            }
        case OP_SUB:
            {
                TEST_OP(uint, uint, -)
                break;
            }
        case OP_MUL:
            {
                TEST_OP(uint, uint, *)
                break;
            }
        case OP_DIV:
            {
                TEST_OP(uint, uint, /)
                break;
            }
        }
#undef TEST_OP

        ASL_ASSERT(false);
        return (NULL);
    }
}
