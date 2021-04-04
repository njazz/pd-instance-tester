#undef PDINSTANCE

extern "C"{
#include "m_pd.h"
#include "m_imp.h"
}

t_class* instance_tester_class = nullptr;
static uintptr_t tptr = 0;

struct t_itester {
    t_object obj;

    t_outlet* out1 = nullptr;
};

static void itester_method(t_itester* x, t_symbol*)
{
}

extern "C" {
uintptr_t mptr(size_t i){
    return (uintptr_t)(void*)(instance_tester_class->c_methods[i].me_fun);
}
}

static inline bool hasInstanceSupport(){
    bool instanceSupport = true;
    for (int i = 0; i < instance_tester_class->c_nmethod; i++) {
        if (mptr(i) == tptr ) {
            instanceSupport = false;
            break;
        }
    }
    return instanceSupport;
}

static void* itester_new(t_symbol* s, int argc, t_atom* argv)
{
    t_itester* x = (t_itester*)pd_new(instance_tester_class);

    post("instance tester result:");
    post(hasInstanceSupport() ? "supports multiple instances" : "supports single instance");

    x-> out1 = outlet_new((t_object*)x, gensym("float"));

    return x;
}

static void itester_bang(t_itester* x){
    outlet_float(x->out1, hasInstanceSupport()?1:0);
}

static void itester_free(t_itester* x)
{
    outlet_free(x->out1);
}

extern "C" {
void setup(void)
{

    instance_tester_class = class_new(gensym("pdinstance_tester"), (t_newmethod)itester_new,
        (t_method)itester_free, sizeof(t_itester), 0, A_GIMME, 0);

    tptr = (uintptr_t)&itester_method;
    class_addmethod(instance_tester_class, (t_method)&itester_method, gensym("_test_method_"), A_NULL);
    class_addbang(instance_tester_class,(t_method)&itester_bang);
}
}
