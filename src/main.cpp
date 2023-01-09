#include "std_include.hpp"

#include "component/map_rotation.hpp"

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

	bool load_map_rotation(const char* filename)
	{
		const auto data = utils::io::read_file(filename);
		if (data.empty())
		{
			console::error("'%s' is empty\n", filename);
			return false;
		}

		
		try
		{
			map_rotation::rotation_data rotation_data;
			rotation_data.parse(data);
		}
		catch (const std::exception& ex)
		{
			console::error("%s: '%s' contains invalid data!\n", ex.what(), filename);
			return false;
		}

		console::info("Successfully parsed map rotation\n");
		return true;
	}

	void usage(const char* prog)
	{
		console::info("X Labs IW4x validator tool\n"
			"Usage: %s OPTIONS\n"
			"  -createfx <filename>\n"
			"  -fx <filename>\n"
			"  -map-rotation <filename>\n",
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
		else if (std::strcmp(argv[i], "-map-rotation") == 0)
		{
			const auto* filename = argv[++i];
			console::info("Parsing map rotation '%s'\n", filename);

			if (!load_map_rotation(filename))
			{
				return EXIT_FAILURE;
			}

		}
		else
		{
			usage(argv[0]);
			return EXIT_FAILURE;
		}
	}

	return EXIT_SUCCESS;
}
