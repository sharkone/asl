#include "precomp/precomp.h"

#include "vm/vm.h"

#include "type_system/type_info.h"
#include "type_system/type_manager.h"
#include "vm/opcodes.h"

namespace asl
{
    vm::vm(const type_manager& type_manager)
        :   m_type_manager(type_manager)
    {
        m_opcodes.resize(opcode::OP_MAX);
        m_opcodes[opcode::OP_NOP]           = opcode(&opcode_nop, 0);
        m_opcodes[opcode::OP_PUSH_BOOL]     = opcode(&opcode_push_bool, 1);
        m_opcodes[opcode::OP_PUSH_UINT]     = opcode(&opcode_push_uint, 1);
        m_opcodes[opcode::OP_POP]           = opcode(&opcode_pop, 0);
        m_opcodes[opcode::OP_EQUAL]         = opcode(&opcode_equal, 0);
        m_opcodes[opcode::OP_NOT_EQUAL]     = opcode(&opcode_not_equal, 0);
        m_opcodes[opcode::OP_GREATER]       = opcode(&opcode_greater, 0);
        m_opcodes[opcode::OP_GREATER_EQUAL] = opcode(&opcode_greater_equal, 0);
        m_opcodes[opcode::OP_LESSER]        = opcode(&opcode_lesser, 0);
        m_opcodes[opcode::OP_LESSER_EQUAL]  = opcode(&opcode_lesser_equal, 0);
        m_opcodes[opcode::OP_ADD]           = opcode(&opcode_add, 0);
        m_opcodes[opcode::OP_SUB]           = opcode(&opcode_sub, 0);
        m_opcodes[opcode::OP_MUL]           = opcode(&opcode_mul, 0);
        m_opcodes[opcode::OP_DIV]           = opcode(&opcode_div, 0);
        m_opcodes[opcode::OP_JMP]           = opcode(&opcode_jmp, 1);
        m_opcodes[opcode::OP_DUMP_STACK]    = opcode(&opcode_dump_stack, 0);
    }

    vm::~vm()
    {
    }

    void vm::load(const std::string& file_path, std::vector<unsigned int>& program) const
    {
        std::ifstream file_stream(file_path);

        std::string line;
        while (std::getline(file_stream, line))
        {
            std::vector<std::string> words;
            std::copy(std::istream_iterator<std::string>(std::istringstream(line)), std::istream_iterator<std::string>(), std::back_inserter<std::vector<std::string>>(words));

            if (words[0] == "nop")
            {
                program.push_back(opcode::OP_NOP);
            }
            else if (words[0] == "push_bool")
            {
                program.push_back(opcode::OP_PUSH_BOOL);
                if (words[1] == "true")
                    program.push_back(1);
                else
                    program.push_back(0);
            }
            else if (words[0] == "push_uint")
            {
                program.push_back(opcode::OP_PUSH_UINT);
                program.push_back(boost::lexical_cast<unsigned int>(words[1]));
            }
            else if (words[0] == "pop")
            {
                program.push_back(opcode::OP_POP);
            }
            else if (words[0] == "equal")
            {
                program.push_back(opcode::OP_EQUAL);
            }
            else if (words[0] == "not_equal")
            {
                program.push_back(opcode::OP_NOT_EQUAL);
            }
            else if (words[0] == "greater")
            {
                program.push_back(opcode::OP_GREATER);
            }
            else if (words[0] == "greater_equal")
            {
                program.push_back(opcode::OP_GREATER_EQUAL);
            }
            else if (words[0] == "lesser")
            {
                program.push_back(opcode::OP_LESSER);
            }
            else if (words[0] == "lesser_equal")
            {
                program.push_back(opcode::OP_LESSER_EQUAL);
            }
            else if (words[0] == "add")
            {
                program.push_back(opcode::OP_ADD);
            }
            else if (words[0] == "sub")
            {
                program.push_back(opcode::OP_SUB);
            }
            else if (words[0] == "mul")
            {
                program.push_back(opcode::OP_MUL);
            }
            else if (words[0] == "div")
            {
                program.push_back(opcode::OP_DIV);
            }
            else if (words[0] == "jmp")
            {
                program.push_back(opcode::OP_JMP);
                program.push_back(boost::lexical_cast<int>(words[1]));
            }
            else if (words[0] == "dump_stack")
            {
                program.push_back(opcode::OP_DUMP_STACK);
            }
        }
    }

    void vm::execute(const std::vector<unsigned int>& program)
    {
        for (std::size_t i = 0; i < program.size(); ++i)
        {
            opcode::id    op_id = (opcode::id)program[i];
            const opcode& op    = m_opcodes[op_id];

            int jmp_offset = op.m_function(*this, (i < (program.size() - 1)) ? (void*)program[i + 1] : NULL);

            i += op.m_data_size;
            i += jmp_offset;
        }
    }

    void vm::push_value(const value::ptr_type& value)
    {
        m_stack.push_back(value);
    }

    void vm::push_value_bool(bool value)
    {
        push_value(m_type_manager.create_value_bool(value));
    }

    void vm::push_value_uint(unsigned int value)
    {
        push_value(m_type_manager.create_value_uint(value));
    }

    value::ptr_type vm::pop_value()
    {
        ASL_ASSERT(m_stack.empty() == false);

        value::ptr_type top = m_stack.back();
        m_stack.pop_back();
        return (top);
    }

    const value::ptr_type& vm::peek_value(int index) const
    {
        ASL_ASSERT(m_stack.empty() == false);

        int actual_index = m_stack.size() + index - 1;
        ASL_ASSERT(actual_index >= 0);
        ASL_ASSERT((std::size_t)actual_index < m_stack.size());

        return (m_stack[actual_index]);
    }

    void vm::dump_stack() const
    {
        ASL_LOG("stack:");
        ASL_LOG("======");
        for (stack_type::const_iterator it = m_stack.begin(); it != m_stack.end(); ++it)
            ASL_LOG("%s (%s)", (*it)->to_string().c_str(), (*it)->get_type().get_name().c_str());
    }
}
