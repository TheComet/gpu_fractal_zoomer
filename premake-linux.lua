----------------------------------------------------------------
-- Premake File - Builds project files
----------------------------------------------------------------

----------------------------------------------------------------
-- Global directories to include
----------------------------------------------------------------

if os.get() == "windows" then
	solutionIncludeDirs = {
		"include",
		"include/lib",
		"include/main",
		"$(SFML_HOME)/include"
	}
end

if os.get() == "linux" then
	solutionIncludeDirs = {
		"include",
		"include/lib",
		"include/main",
		"/usr/include",
		"/usr/local/include"
	}
end

----------------------------------------------------------------
-- 8-bit-challenge solution
----------------------------------------------------------------

-- Project name
solution "GPU-Fractal-Zoomer"

	-- Configurations
	configurations {
		"Debug",
		"Release"
	}

	-- Where to generate project files
	location "project"

	----------------------------------------------------------------
	-- Main application
	----------------------------------------------------------------

	project "GPU-Fractal-Zoomer"
		kind "ConsoleApp"
		language "C++"

		-- Files to include
		files {
			"src/main/**.cpp",
			"include/main/**.hpp"
		}

		-- header search directories
		includedirs (solutionIncludeDirs)

		-- global definitions
		defines {
			"SFML_DYNAMIC"
		}

		-- Debug configuration
		configuration "Debug"
			targetdir "bin/debug"
			defines {
				"DEBUG",
				"_DEBUG"
			}
			flags {
				"Symbols"
			}
			libdirs {
				"bin/lib",
				"$(SFML_HOME)/lib",
				"/usr/lib",
				"/usr/local/lib"
			}
			links {
				"gpu-fractal-zoomer-lib_d",
				"sfml-graphics",
				"sfml-system",
				"sfml-window"
			}

		-- Release configuration
		configuration "Release"
			targetdir "bin/release"
			defines {
				"NDEBUG"
			}
			flags {
				"Optimize"
			}
			libdirs {
				"bin/lib",
				"$(SFML_HOME)/lib"
			}
			links {
				"gpu-fractal-zoomer-lib",
				"sfml-main",
				"sfml-graphics",
				"sfml-system",
				"sfml-window"
			}

		----------------------------------------------------------------
		-- Main game library
		----------------------------------------------------------------

		project "gpu-fractal-zoomer-lib"
			kind "StaticLib"
			language "C++"
			files {
				"src/lib/**.cpp",
				"include/lib/**.hpp"
			}

			-- Header search directories
			includedirs (solutionIncludeDirs)

			-- Debug configuration
			configuration "Debug"
				targetdir "bin/lib"
				targetsuffix "_d"
				defines {
					"DEBUG",
					"_DEBUG"
				}
				flags {
					"Symbols"
				}
				libdirs {
				--	"$(SFML_HOME)/lib"
				}
				links {
				}

			-- release configuration
			configuration "Release"
				targetdir "bin/lib"
				defines {
					"NDEBUG"
				}
				flags {
					"Optimize"
				}
				libdirs {
				--	"$(SFML_HOME)/lib"
				}
				links {
				}

