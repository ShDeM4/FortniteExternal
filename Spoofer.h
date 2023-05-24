#pragma once

#include "IncludeFiles.h"

// Created off the idea of -> https://github.com/MockbaTheBorg/RETSpoof

namespace Spoofer {
	namespace _SpoofCallInternal {
		extern "C" PVOID RetSpoofStub();

		template<typename Ret, typename... Args>
		inline Ret Wrapper(PVOID shell, Args... args) {
			auto fn = (Ret(*)(Args...))(shell);
			return fn(args...);
		}

		template<typename Ret, typename First, typename Second, typename Third, typename Fourth, typename... Pack>
		static Ret Call(PVOID shell, PVOID shell_params, First first, Second second, Third third, Fourth fourth, Pack... pack) {
			return Wrapper<Ret, First, Second, Third, Fourth, PVOID, PVOID, Pack...>(shell, first, second, third, fourth, shell_params, nullptr, pack...);
		}
	};

	template <std::size_t Argc>
	struct Remapper<Argc, std::enable_if_t<Argc <= 4>> {
		template<typename Ret, typename First = PVOID, typename Second = PVOID, typename Third = PVOID, typename Fourth = PVOID>
		static Ret Call(PVOID shell, PVOID shell_param, First first = First{}, Second second = Second{}, Third third = Third{}, Fourth fourth = Fourth{}) {
			return Wrapper<Ret, First, Second, Third, Fourth, PVOID, PVOID>(shell, first, second, third, fourth, shell_param, nullptr);
		}
	};
}