#pragma once

// Works with functions that don't return classes.
#define DLL_EXPORT extern "C" __declspec(dllexport)
