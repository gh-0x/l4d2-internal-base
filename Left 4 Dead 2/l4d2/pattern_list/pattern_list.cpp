#include "pattern_list.h"

pattern_list g_pl;

void pattern_list::initialize()
{
	m_device_fn = pattern_scan(X_("shaderapidx9.dll"), X_("A1 ? ? ? ? 8B 08 6A 03")) + 1;
	m_client_mode_fn = pattern_scan(X_("client.dll"), X_("89 04 B5 ? ? ? ? E8")) + 3;
	m_get_weapon_data_fn = pattern_scan(X_("client.dll"), X_("0F B7 ? ? ? ? ? 50 E8 ? ? ? ? 83 C4 ? C3"));
}

m_pattern pattern_list::pattern_scan(const char* module_name, const char* signature)
{
	const auto module_handle = GetModuleHandleA(module_name);

	if (!module_handle)
		return nullptr;

	static auto pattern_to_byte = [](const char* pattern) {
		auto bytes = std::vector<int>{};
		auto start = const_cast<char*>(pattern);
		auto end = const_cast<char*>(pattern) + std::strlen(pattern);

		for (auto current = start; current < end; ++current) {
			if (*current == '?') {
				++current;

				if (*current == '?')
					++current;

				bytes.push_back(-1);
			}
			else {
				bytes.push_back(std::strtoul(current, &current, 16));
			}
		}
		return bytes;
	};

	auto dos_header = reinterpret_cast<PIMAGE_DOS_HEADER>(module_handle);
	auto nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<std::uint8_t*>(module_handle) + dos_header->e_lfanew);

	auto size_of_image = nt_headers->OptionalHeader.SizeOfImage;
	auto pattern_bytes = pattern_to_byte(signature);
	auto scan_bytes = reinterpret_cast<std::uint8_t*>(module_handle);

	auto s = pattern_bytes.size();
	auto d = pattern_bytes.data();

	for (auto i = 0; i < size_of_image - s; ++i) {
		bool found = true;

		for (auto j = 0; j < s; ++j) {
			if (scan_bytes[i + j] != d[j] && d[j] != -1) {
				found = false;
				break;
			}
		}

		if (found)
			return &scan_bytes[i];
	}
}