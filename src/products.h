#include <unordered_map>

#include <json/json.h>

class InvalidProductsJson : public std::runtime_error
{
public:
	InvalidProductsJson(const std::string &what);
};

class Product
{
public:
	Product(const std::string &category, uint64_t id, const std::string &title, Json::Value item);

	uint64_t get_id() const;
	const std::string &get_category() const;
	const std::string &get_title() const;

private:
	std::string m_category;
	int64_t m_id;
	std::string m_title;
	Json::Value m_item;
};

class Products
{
public:
	Products(Json::Value &&root);

	std::unordered_map<std::string, std::vector<Product>>::iterator begin();
	std::unordered_map<std::string, std::vector<Product>>::iterator end();

private:
	void add_product(Product &&product);

	std::unordered_map<std::string, std::vector<Product>> m_products;
};
