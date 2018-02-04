#include "movie.h"

#include "movie-bk2.h"

#include <functional>
#include <unordered_map>

using namespace std;
using namespace Retro;

static unordered_map<string, function<unique_ptr<Movie>(const string&)>> s_movieTypes{
#ifdef USE_LIBZIP
	make_pair("bk2", MovieBK2::load),
#endif
};

std::unique_ptr<Movie> Movie::load(const string& path) {
	size_t dot = path.find_last_of('.');
	if (dot == string::npos) {
		return nullptr;
	}
	string extName = path.substr(dot + 1);
	const auto& found = s_movieTypes.find(extName);
	if (found == s_movieTypes.end()) {
		return nullptr;
	}
	return found->second(path);
}

bool Movie::getKey(int key) {
	return (m_keys >> key) & 1;
}

void Movie::setKey(int key, bool set) {
	m_keys &= ~(1 << key);
	m_keys |= set << key;
}
