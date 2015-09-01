#pragma once


class TokenPool {
public:
	unsigned AddToken(const std::string & str);
	const std::string & GetToken(unsigned token);

private:
	std::vector<std::string> m_pool;
};


