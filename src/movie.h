#pragma once

#include <memory>
#include <string>
#include <vector>

namespace Retro {

class Movie {
public:
	static std::unique_ptr<Movie> load(const std::string& path);
	virtual ~Movie() {}

	virtual std::string getGameName() const { return {}; }

	virtual bool step() = 0;

	virtual void close() {}

	virtual bool getState(std::vector<uint8_t>*) const { return false; }
	virtual void setState(const uint8_t*, size_t) {}

	bool getKey(int);
	void setKey(int key, bool);

protected:
	uint16_t m_keys = 0;
};
}
