#pragma once

namespace lxc {
	typedef int SizeType;

	SizeType min_of_2(const lxc::SizeType a, const SizeType b) { return (a < b ? a : b); }
	SizeType max_of_2(const lxc::SizeType a, const SizeType b) { return (a < b ? b : a); }

	template <class T> void swap(T& ele1, T& ele2) { T tmp = ele1; ele1 = ele2; ele2 = tmp; }
}
