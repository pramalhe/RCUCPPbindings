#include <iostream>
#include <unistd.h>
#include "urcu-signal.hpp"
#include "rcu_scoped_reader.hpp"

int main()
{
	std::rcu_register_thread();
	{
		class std::rcu_scoped_reader rr;
	}
	{
		class std::rcu_scoped_reader rrs(std::rcu_signal);
	}
	std::rcu_unregister_thread();

	return 0;
}
