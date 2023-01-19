#include "products.h"

#include <iostream>

InvalidProductsJson::InvalidProductsJson(const std::string &what)
	: std::runtime_error(what) {}

Product::Product(const std::string &category, uint64_t id, const std::string &title, Json::Value item)
	: m_category(category), m_id(id), m_title(title), m_item(item)
{
}

uint64_t Product::get_id() const
{
	return m_id;
}

const std::string &Product::get_category() const
{
	return m_category;
}

const std::string &Product::get_title() const
{
	return m_title;
}

Products::Products(Json::Value &&root)
{
	auto products = root.get("products", Json::Value());
	if (!products.isArray())
	{
		throw InvalidProductsJson("could not find .products");
	}

	for (auto i = 0; i < products.size(); ++i)
	{
		auto product_json = products.get(i, Json::Value());
		if (!product_json.isObject())
		{
			throw InvalidProductsJson(".products is not an array");
		}

		auto category = product_json.get("category", Json::Value());
		auto id = product_json.get("id", Json::Value());
		auto title = product_json.get("title", Json::Value());
		if (!category.isString())
		{
			throw InvalidProductsJson("product has no category");
		}
		if (!id.isUInt64())
		{
			throw InvalidProductsJson("product has no id");
		}
		if (!title.isString())
		{
			throw InvalidProductsJson("product has no title");
		}

		auto product = Product(category.asString(), id.asUInt64(), title.asString(), std::move(product_json));

		add_product(std::move(product));
	}
}

std::unordered_map<std::string, std::vector<Product>>::iterator Products::begin()
{
	return m_products.begin();
}

std::unordered_map<std::string, std::vector<Product>>::iterator Products::end()
{
	return m_products.end();
}

void Products::add_product(Product &&product)
{
	auto &category = m_products[product.get_category()];
	category.push_back(product);
}
