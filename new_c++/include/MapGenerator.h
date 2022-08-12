#pragma once
#include <utility>
#include <iostream>
#include <string_view>
#include <functional>
#include <algorithm>
#include <vector>
#include <random>
#include <fstream>
#include <unordered_map>

#include "Enums.h"
#include "Utils.h"
#include "PerlinNoise.h"
#include "PoissonSampler.h"


//template<typename T>
//concept StringLike = std::is_convertible_v<T, std::string_view>;

template <size_t Width, size_t Height>
class MapGenerator
{
private:
	std::vector<std::vector<char>> m_game_map;
	//std::map<<size_t, size_t>, float> m_mountain_range;
	std::vector<std::function<int(size_t)>> m_generate_levels;
	std::mt19937 m_random_device;
	std::uniform_int_distribution<> m_distribution;
	std::uniform_real_distribution<> m_real_distribution;
	ColorWrapper m_colors;
	PerlinNoise m_perlin_noiser;
public:
	MapGenerator() 
		: 
			m_random_device { std::random_device{}() },
			// m_distribution( 0, static_cast<size_t>(Elements::Count) - 1 ),
			m_distribution( 0, 6 ),
			m_real_distribution( 0.0, 1.0 ),
			m_colors( ColorWrapper{} ),
			m_perlin_noise { 2.0, 1, 0.5, Width, Height
			m_seed_relax { 
				[&](auto container) -> void {
					std::transform(container.begin(), container.end(), conteiner.begin(), 
						[&]([[ maybe_unused ]] auto unused) -> double { return get_random_real(); }
					);	
				}
			}
	{
		m_game_map = std::vector<std::vector<char>> (Height, std::vector<char>(Width, ' '));
		m_generate_levels = std::vector<std::function<int(size_t)>> {
			[&](size_t i) -> int { return generate_level(i, GenerationType::Background, Elements::Dessert); },	
			[&](size_t i) -> int { return generate_level(i, GenerationType::Continuos, Elements::Water); },	
			[&](size_t i) -> int { 
				return generate_level(i, GenerationType::Random, Elements::Tree, Elements::Bush, Elements::Swamp);
			},	
			[&](size_t i) -> int { return generate_level(i, GenerationType::LessRandom, Elements::Nest); },	
			[&](size_t i) -> int { return generate_level(i, GenerationType::Rare, Elements::Corpse); },	
			[&](size_t i) -> int { return generate_level(i, GenerationType::Path, Elements::MigrationRoute); },	
		};
	}
	int generate_map(std::string_view folder_name, std::string_view file_name, bool both_maps=true)
	{
		std::string filename = folder_name.data();
		filename.append(file_name.data());

		int acc = 0;
		for (size_t i = 0; auto fn : m_generate_levels)
		{
			acc += fn(i++);
		}

		if (acc) { std::cout << acc << " "; puts("smth is wrong with generating levels"); }

		acc += export_to_file(filename + ".ppm", [&](auto& fs) -> void { export_ppm(fs); });
		
		if (both_maps)
		{ 
			acc += export_to_file(filename + ".txt", [&](auto& fs) -> void { export_ascii(fs); });
		}

		show_map();
		//show_seed();

		return acc;
	}
	void show_map()
	{
		puts("SHOW MAP");
		for (auto line : m_game_map)
		{
			for (auto c : line) { std::cout << c; }
			puts("");
		}
	}
	template <typename... Args>
	int generate_level(size_t i, GenerationType gen_type, Args... symbols)
	{
		// std::cout << "generate_level: " << static_cast<int>(gen_type) << " ";
		// // ( std::cout << ... << static_cast<std::underlying_type<Elements>::type>(symbols) ) << '\n';

		// TODO
		auto elements = std::vector<char> { get_char(symbols)... };

		int i_gen_type = static_cast<int>(gen_type);
		if (i_gen_type >= static_cast<int>(GenerationType::Random) && i_gen_type <= static_cast<int>(GenerationType::Rare))
		{
			auto distr = std::uniform_int_distribution<> { 0, static_cast<int>(elements.size()) - 1 };

			for (auto& line : m_game_map)
			{
				for (auto& c : line)
				{
					int random = get_random();
					// std::cout << random << ": " << static_cast<int>(gen_type) << '\n';
					// FIXME
					if (c != get_char(Elements::Water) && static_cast<double>((random - static_cast<int>(gen_type))) - 3.8 > 0.0)
					{
						c = static_cast<char>(elements[ static_cast<size_t>(distr(m_random_device)) ]);
					}
				}	
			}
			return 0;
		}
		else if (gen_type == GenerationType::Path)
		{
			// FIXME
			//path_generation()
			return 0;
		}
		
		// FIXME temp
		double lim_level = static_cast<double>(i) * m_lim_coeff;
		std::cout << i << " " <<  elements[0] << ": ... " << lim_level << '\n';

		// ( perlin_noise2D(m_noise_seed, m_octave_count, m_real_scalling_bias, symbols, lim_level), ... );
		( perlin_noise2D(symbols, m_game_map), ... );

		return 0;
	}

	int export_to_file(std::string_view filename, std::function<void(std::fstream&)> fn)
	{
		std::fstream newfile;
		newfile.open(filename.data(), std::ios::out);

		if (!newfile.is_open()) { return -1; }
		
		//( funcs(newfile), ... );	
		fn(newfile);

		newfile.close();

		return 0;
	}
	void export_ppm(std::fstream& newfile)
	{
		puts("export_ppm");
		
		//PPM header
		newfile << "P3" << '\n';
		newfile << "# Some comment" << '\n';
		newfile << Width << " " << Height << '\n';

		for (const auto& line : m_game_map)
		{
			for (const auto& token : line)
			{
				newfile << m_colors.color_map[token];
				if (&token != &line.back()) newfile << " ";
			}
			newfile << '\n';
		}
	}
	void export_ascii(std::fstream& newfile)
	{
		puts("export_ascii");
		for (auto line : m_game_map)
		{
			for (auto token : line) { newfile << token; }
			newfile << '\n';
		}
	}
private:
	int get_random() { return m_distribution(m_random_device); }
	double get_random_real() { return m_real_distribution(m_random_device); }
};

