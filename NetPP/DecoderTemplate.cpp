#include "include.h"

const DecoderTemplate & DecoderTemplate::operator<<(const std::string input)
{
	content = content + input;
	return *this;
}

DecoderTemplate::DecoderTemplate(nlohmann::json& conf)
{
	std::string decoder_path;
	if (conf["decoder_template"] != nullptr)
		decoder_path = conf["decoder_template"].get<std::string>();
	else
		throw std::string("Decoder template path not specified in config");

	decoder_path = conf["__relative_path"].get<std::string>() + "\\" + decoder_path;
	std::ifstream decoder(decoder_path, std::ios::in);

	if (!decoder.good())
		throw std::string("File '" + decoder_path + "' not found");

	global_context = std::string((std::istreambuf_iterator<char>(decoder)), std::istreambuf_iterator<char>());

	std::string ph_rx;
	if (conf["placeholder"] != nullptr)
		ph_rx = conf["placeholder"].get<std::string>();
	else
		throw std::string("Placeholder regular expression not specified in config");

	placeholder_regex = std::regex(ph_rx);
}


DecoderTemplate::~DecoderTemplate()
{
}

void DecoderTemplate::Save(std::ofstream& file_out)
{
	bool algo_inserted = false;
	std::smatch match;
	std::string result = global_context;

	while (std::regex_search(result, match, placeholder_regex))
	{
		if (match[1] == "ALGO_DECODER")
		{
			if (algo_inserted)
				Console::Warn("Placeholder ALGO_DECODER specified more than once");

			result = result.replace(match.position(), match.length(), content);
			algo_inserted = true;
		}
		else
			Console::Warn(std::string("Placeholder ") + match[1].str() + " not allowed in global context. Ignored");
	}

	if (!algo_inserted)
	{
		Console::Warn("No ALGO_DECODER placeholder specified in global context");
	}

	file_out << result;
}