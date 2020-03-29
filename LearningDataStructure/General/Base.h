#pragma once

namespace lxc {
	typedef int SizeType;

	template <class S> S min_of_2(const S s1, const S s2) { return (s1 < s2 ? s1 : s2); }
	template <class S> S max_of_2(const S s1, const S s2) { return (s1 < s2 ? s2 : s1); }

	template <class T> void swap(T& ele1, T& ele2) { T tmp = ele1; ele1 = ele2; ele2 = tmp; }

	template <class S> bool equals(const S s1, const S s2) { return s1 == s2; }
}
