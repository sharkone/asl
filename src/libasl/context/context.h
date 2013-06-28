#pragma once

#include "type_system/type_manager.h"
#include "vm/vm.h"

namespace asl
{
    class context : public boost::noncopyable
    {
    public:
        context();
        ~context();

        type_manager&   get_type_manager();
        vm&             get_vm();

    private:
        type_manager    m_type_manager;
        vm              m_vm;
    };
}
