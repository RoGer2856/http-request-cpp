#include <string>
#include <vector>

#include <curl/curl.h>

size_t curl_write_chunk_callback(void *contents, size_t size, size_t nmemb, std::vector<uint8_t> *userp);
bool fetch_data(const std::string &url, std::vector<uint8_t> &result_body);

class CurlInitializerRAII {
public:
	CurlInitializerRAII();
	~CurlInitializerRAII();
};
