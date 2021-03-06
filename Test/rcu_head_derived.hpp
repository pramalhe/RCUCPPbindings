#include <cstddef>

// Derived-type approach.  All RCU-protected data structures using this
// approach must derive from std::rcu_head_derived, which in turn derives
// from std::rcu_head.  No idea what happens in case of multiple inheritance.

namespace std {
	template<typename T>
	class rcu_head_derived: public rcu_head {
	public:
		static void trampoline(rcu_head *rhp)
		{
			T *obj;
			rcu_head_derived<T> *rhdp;

			rhdp = static_cast<rcu_head_derived<T> *>(rhp);
			obj = static_cast<T *>(rhdp);
			if (rhdp->callback_func)
				rhdp->callback_func(obj);
			else
				delete obj;
		}

		void call(void callback_func(T *obj) = nullptr)
		{
			this->callback_func = callback_func;
			call_rcu(static_cast<rcu_head *>(this), trampoline);
		}

		void call(class rcu_domain &rd,
			  void callback_func(T *obj) = nullptr)
		{
			this->callback_func = callback_func;
			rd.call(static_cast<rcu_head *>(this), trampoline);
		}

	private:
		void (*callback_func)(T *obj);
	};
}
