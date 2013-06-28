#include "precomp/precomp.h"

#include "context/context.h"

namespace asl
{
    context::context()
        :   m_vm(m_type_manager)
    {
    }

    context::~context()
    {
    }

    type_manager& context::get_type_manager()
    {
        return (m_type_manager);
    }

    vm& context::get_vm()
    {
        return (m_vm);
    }
}
