#include "std_include.hpp"
#include "game/cg_client_side_effects_mp.hpp"

#include "console.hpp"

#include <utils/io.hpp>

namespace
{
	bool load_client_effects(const char* filename)
	{
		const auto data = utils::io::read_file(filename);
		if (data.empty())
		{
			console::error("'%s' is empty\n", filename);
			return false;
		}

		return game::parse_client_effects(data.data());
	}

	void usage(const char* prog)
	{
		console::info("X Labs IW4x validator tool\n"
			"Usage: %s OPTIONS\n"
			"  -createfx <filename>\n"
			"  -fx <filename>\n",
			prog
		);
	}
}

int main(const int argc, const char** argv)
{
	// Parse command-line flags
	for (auto i = 1; i < argc; i++)
	{
		if (std::strcmp(argv[i], "-createfx") == 0)
		{
			const auto* filename = argv[++i];
			console::info("Parsing createfx '%s'\n", filename);

			if (!load_client_effects(filename))
			{
				return EXIT_FAILURE;
			}
		}
		else if (std::strcmp(argv[i], "-fx") == 0)
		{
			console::info("Parsing client effect mapping files is currently unsupported\n");
		}
		else
		{
			usage(argv[0]);
			return EXIT_FAILURE;
		}
	}

	return EXIT_SUCCESS;
}
