#ifndef scopeguard_h__
#define scopeguard_h__

namespace ggp
{
    template <class Fun>
    class ScopeGuard {
        Fun f_;
        bool active_;
    public:
        ScopeGuard(Fun f)
            : f_(std::move(f))
            , active_(true) {
        }
        ~ScopeGuard() { if (active_) f_(); }
        void dismiss() { active_ = false; }
        ScopeGuard(ScopeGuard&& rhs)
            : f_(std::move(rhs.f_))
            , active_(rhs.active_) {
            rhs.dismiss();
        }

    private:
        //ScopeGuard(){};
        //ScopeGuard(const ScopeGuard&){};
        //ScopeGuard& operator=(const ScopeGuard&){};

    };

    namespace detail {
        class ScopeGuardOnExit {};
        template <typename Fun>
        ScopeGuard<Fun> operator+(ScopeGuardOnExit, Fun&& fn) {
            return ScopeGuard<Fun>(std::forward<Fun>(fn));
        }
    }
}



#define SCOPE_EXIT \
    auto ANONYMOUS_VARIABLE(SCOPE_EXIT_STATE) \
    = ggp::detail::ScopeGuardOnExit() + [&]()

#define CONCATENATE_IMPL(s1, s2) s1##s2
#define CONCATENATE(s1, s2) CONCATENATE_IMPL(s1, s2)
#ifdef __COUNTER__
#define ANONYMOUS_VARIABLE(str) \
    CONCATENATE(str, __COUNTER__)
#else
#define ANONYMOUS_VARIABLE(str) \
    CONCATENATE(str, __LINE__)
#endif

#endif // scopeguard_h__
