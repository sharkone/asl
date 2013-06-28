#include "precomp/precomp.h"

#include "context/vm/opcodes.h"

#include "context/vm/value.h"
#include "context/vm/vm.h"

namespace asl
{
    opcode::opcode()
        :   m_function(NULL)
        ,   m_data_size(0)
    {
    }

    opcode::opcode(function_type function, std::size_t data_size)
        :   m_function(function)
        ,   m_data_size(data_size)
    {
    }

    int opcode_nop(vm& vm, void* data)
    {
        return (0);
    }

    int opcode_push_bool(vm& vm, void* data)
    {
        vm.push_value_bool(reinterpret_cast<bool>(data));
        return (0);
    }

    int opcode_push_uint(vm& vm, void* data)
    {
        vm.push_value_uint(reinterpret_cast<unsigned int>(data));
        return (0);
    }

#define BINARY_OP(name, symbol)                 \
    int opcode_##name(vm& vm, void* data)       \
    {                                           \
        value::ptr_type op2 = vm.pop_value();   \
        value::ptr_type op1 = vm.pop_value();   \
        vm.push_value(*op1 symbol *op2);        \
        return (0);                             \
    }

    BINARY_OP(equal,         ==)
    BINARY_OP(not_equal,     !=)
    BINARY_OP(greater,        >)
    BINARY_OP(greater_equal, >=)
    BINARY_OP(lesser,         <)
    BINARY_OP(lesser_equal,  <=)
    BINARY_OP(add,            +)
    BINARY_OP(sub,            -)
    BINARY_OP(mul,            *)
    BINARY_OP(div,            /)
#undef BINARY_OP


    int opcode_pop(vm& vm, void* data)
    {
        vm.pop_value();
        return (0);
    }

    int opcode_jmp(vm& vm, void* data)
    {
        return (reinterpret_cast<int>(data));
    }

    int opcode_dump_stack(vm& vm, void* data)
    {
        vm.dump_stack();
        return (0);
    }
}
