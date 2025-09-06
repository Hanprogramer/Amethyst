#pragma once
#ifdef AMETHYST_EXPORTS
#define MC_API __declspec(dllexport)
#else
#define MC_API __declspec(dllimport)
#endif
#define IMPORT __declspec(dllimport)