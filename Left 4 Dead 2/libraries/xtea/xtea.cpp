#include "xtea.h"

#include <string>
#include <fstream>

xtea g_xtea;

unsigned int key[4] = { 0x3154, 0x5346, 0x2157, 0x4314 };

//XTEA block cipher - code from Wikipedia
//https://en.wikipedia.org/wiki/XTEA

static void encipher(unsigned int num_rounds, uint32_t v[2], uint32_t const key[4])
{
	unsigned int i;
	uint32_t v0 = v[0], v1 = v[1], sum = 0, delta = 0x9E3779B9;
	for (i = 0; i < num_rounds; i++)
	{
		v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + key[sum & 3]);
		sum += delta;
		v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + key[(sum >> 11) & 3]);
	}
	v[0] = v0; v[1] = v1;
}

static void decipher(unsigned int num_rounds, uint32_t v[2], uint32_t const key[4])
{
	unsigned int i;
	uint32_t v0 = v[0], v1 = v[1], delta = 0x9E3779B9, sum = delta * num_rounds;
	for (i = 0; i < num_rounds; i++)
	{
		v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + key[(sum >> 11) & 3]);
		sum -= delta;
		v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + key[sum & 3]);
	}
	v[0] = v0; v[1] = v1;
}

void xtea::encode(const std::string& path)
{
	std::fstream file(path, std::ios::in | std::ios::out | std::ios::binary);

	file.seekg(0, std::ios::end);

	unsigned file_size = file.tellg();

	file.seekg(std::ios::beg);
	file.clear();

	int num = file_size / 8;
	if (file_size % 8 != 0) {
		++num;
	}

	unsigned char data_array[8];
	unsigned file_position = file.tellg();

	for (int i = 0; i < num; i++)
	{
		file.seekg(file_position);
		file.read((char*)data_array, 8);

		encipher(32, (uint32_t*)data_array, key);

		file.seekp(file_position);
		file.write((char*)data_array, 8);

		memset(data_array, 0, 8);
		file_position += 8;
	}

	file.close();
}

void xtea::decode(const std::string& path)
{
	std::fstream file(path, std::ios::in | std::ios::out | std::ios::binary);

	file.seekg(0, std::ios::end);

	unsigned file_size = file.tellg();

	file.seekg(std::ios::beg);
	file.clear();

	int num = file_size / 8;
	if (file_size % 8 != 0) {
		++num;
	}

	unsigned char data_array[8];
	unsigned file_position = file.tellg();

	for (int i = 0; i < num; i++)
	{
		file.seekg(file_position);
		file.read((char*)data_array, 8);

		decipher(32, (uint32_t*)data_array, key);

		file.seekp(file_position);
		file.write((char*)data_array, 8);

		memset(data_array, 0, 8);
		file_position += 8;
	}

	file.close();
}