// Common code for userspace RCU concrete class definition.

public:
	void register_thread()
	{
		rcu_register_thread();
	}

	void unregister_thread()
	{
		rcu_unregister_thread();
	}

	void read_lock() noexcept
	{
		rcu_read_lock();
	}

	void read_unlock() noexcept
	{
		rcu_read_unlock();
	}

	void synchronize() noexcept
	{
		synchronize_rcu();
	}

	void call(class rcu_head *rhp,
		  void cbf(class rcu_head *rhp))
	{
		call_rcu(rhp, cbf);
	}

	void barrier() noexcept
	{
		rcu_barrier();
	}

	void quiescent_state() noexcept
	{
		rcu_quiescent_state();
	}

	void thread_offline() noexcept
	{
		rcu_thread_offline();
	}

	void thread_online() noexcept
	{
		rcu_thread_online();
	}
