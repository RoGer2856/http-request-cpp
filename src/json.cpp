#include "json.h"

bool parse_json(const std::string &json_str, Json::Value &root)
{
	JSONCPP_STRING err;
	Json::CharReaderBuilder builder;
	const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
	return reader->parse(json_str.c_str(), json_str.c_str() + json_str.length(), &root, &err);
}
