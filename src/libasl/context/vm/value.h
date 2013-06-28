#pragma once

namespace asl
{
    class type_info;

    class value : public boost::noncopyable
    {
    public:
        typedef boost::shared_ptr<value> ptr_type;

        value(const type_info& type);
        ~value();

        const type_info&    get_type() const;

        bool                is_bool() const;
        bool                get_bool() const;
        void                set_bool(bool value);

        bool                is_uint() const;
        unsigned int        get_uint() const;
        void                set_uint(unsigned int value);

        std::string         to_string() const;

        ptr_type            operator ==(const value& rhs) const;
        ptr_type            operator !=(const value& rhs) const;
        ptr_type            operator >(const value& rhs) const;
        ptr_type            operator >=(const value& rhs) const;
        ptr_type            operator <(const value& rhs) const;
        ptr_type            operator <=(const value& rhs) const;

        ptr_type            operator +(const value& rhs) const;
        ptr_type            operator -(const value& rhs) const;
        ptr_type            operator *(const value& rhs) const;
        ptr_type            operator /(const value& rhs) const;

    private:
        enum binary_op
        {
            OP_EQUAL,
            OP_NOT_EQUAL,
            OP_GREATER,
            OP_GREATER_EQUAL,
            OP_LESSER,
            OP_LESSER_EQUAL,

            OP_ADD,
            OP_SUB,
            OP_MUL,
            OP_DIV
        };
        ptr_type            binary_operator(const value& rhs, binary_op op) const;

        const type_info&    m_type;

        union
        {
            bool            m_bool;
            unsigned int    m_uint;
        };
    };
}
