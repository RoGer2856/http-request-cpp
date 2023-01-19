#include <iostream>
#include <string>

#include <curl/curl.h>

#include "data_fetcher.h"
#include "json.h"
#include "products.h"

int main(int argc, char *argv[])
{
	auto curl_initializer = CurlInitializerRAII();

	std::vector<uint8_t> body;
	if (!fetch_data("https://dummyjson.com/products", body))
	{
		std::cerr << "Could not fetch data" << std::endl;
		return 1;
	}

	auto body_str = std::string((const char *)body.data(), body.size());

	Json::Value root;
	if (!parse_json(body_str, root))
	{
		std::cerr << "Could not parse body as Json" << std::endl;
		return 1;
	}

	// std::cout << root.toStyledString() << std::endl;

	try
	{
		Products products = Products(std::move(root));

		for (auto &&[category_name, products] : products)
		{
			std::cout << category_name << std::endl;
			for (auto &&product : products)
			{
				std::cout << "    " << product.get_id() << " - " << product.get_title() << std::endl;
			}
		}
	}
	catch (InvalidProductsJson e)
	{
		std::cerr << "Received Json data does not contain a valid Products object, msg = " << e.what() << std::endl;
		return 1;
	}

	return 0;
}
