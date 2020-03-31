#pragma once

#include <iostream>

#include "../Exception/Exception.h"

namespace lxc {
	// output
	std::ostream& operator<< (std::ostream& os, const String& str)
	{
		if (String::show_full_data) { os << str.to_cstr(); } else { os << str.elements(); }
		return os;
	}

	std::ostream& operator<< (std::ostream& os, Exception* e)
	{
		os << e->get_name() << ": " << e->get_message();
		return os;
	}

	std::ostream& operator<< (std::ostream& os, Exception& e)
	{
		os << e.get_name() << ": " << e.get_message();
		return os;
	}
};