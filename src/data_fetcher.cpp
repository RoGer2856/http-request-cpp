#include "data_fetcher.h"

#include <cstring>
#include <iostream>

size_t curl_write_chunk_callback(void *contents, size_t size, size_t nmemb, std::vector<uint8_t> *userp)
{
	size_t real_size = size * nmemb;
	auto data_received = userp->size();
	userp->resize(data_received + real_size);
	memcpy(userp->data() + data_received, contents, real_size);

	return real_size;
}

bool fetch_data(const std::string &url, std::vector<uint8_t> &result_body)
{
	result_body.clear();

	const int BUFFER_WINDOW_SIZE = 1024;

	CURL *curl_handle = curl_easy_init();
	if (curl_handle)
	{
		curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, curl_write_chunk_callback);
		curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &result_body);

		auto result = curl_easy_perform(curl_handle);

		curl_easy_cleanup(curl_handle);

		return result == CURLE_OK;
	}

	return false;
}

CurlInitializerRAII::CurlInitializerRAII()
{
	curl_global_init(CURL_GLOBAL_ALL);
}

CurlInitializerRAII::~CurlInitializerRAII()
{
	curl_global_cleanup();
}
