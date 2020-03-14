#pragma once

namespace lxc {
	typedef int SizeType;

	SizeType min_of_2(const lxc::SizeType a, const SizeType b) { return (a < b ? a : b); }
	SizeType max_of_2(const lxc::SizeType a, const SizeType b) { return (a < b ? b : a); }
}
