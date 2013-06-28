#pragma once

#include "context/vm/opcodes.h"
#include "context/vm/value.h"

namespace asl
{
    class context;
    class type_manager;

    class vm
    {
    public:
        vm(const type_manager& type_manager);
        ~vm();
        
        void                                    load(const std::string& file_path, std::vector<unsigned int>& program) const;
        void                                    execute(const std::vector<unsigned int>& program);

        void                                    push_value(const value::ptr_type& value);
        void                                    push_value_bool(bool value);
        void                                    push_value_uint(unsigned int value);

        value::ptr_type                         pop_value();
        const value::ptr_type&                  peek_value(int index) const;

        void                                    dump_stack() const;

    private:
        const type_manager&                     m_type_manager;

        std::vector<opcode> m_opcodes;

        typedef std::vector<value::ptr_type>    stack_type;
        stack_type                              m_stack;
    };
}
