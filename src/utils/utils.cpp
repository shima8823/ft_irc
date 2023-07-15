#include "definition.hpp"

std::vector<std::string> ft::split(std::string str, std::string delim) {
	std::vector<std::string> res;

	uint64 i;

	while ((i = str.find(delim)) != std::string::npos) {
		res.push_back(str.substr(0, i));
		str.erase(0, i + delim.length());
	}
	if (str != "")
		res.push_back(str);

	return res;
}

void ft::put(std::string s) { std::cout << s << std::endl; }

std::ostream& operator << (std::ostream& stream, std::vector<std::string>& strs) {
	stream << "[";
	for (std::vector<std::string>::iterator it = strs.begin(); it != strs.end(); ++it) {
		stream << "\"" << *it << (it == strs.end() - 1 ? "\"" : "\", ");
	}
	stream << "]";
	return stream;
}
