#include <bitset>
#include <iostream>
#include <math.h>
#include <sstream>
#include <vector>

// string to binary O(n)
std::string stringToBits(std::string s) {
	std::ostringstream o;
	for (int i = 0; i < s.length(); i++)
	{
		 o << std::bitset<8>(s[i]).to_string();
	}
	return o.str();
}

// transform to 32byte/256byte format O(n)
std::string bitFormater(std::string s) {
	std::ostringstream o;
	o << s << '1';
	o << std::string((((512 * int(std::floor((o.str().length() + 64) / 512) + 1)) - o.str().length()) - 64), '0') << std::bitset<64>(s.length());
	return o.str();
}

// create Vector with 32bit-Words O(n)
std::vector<std::string> ChunckFormater(std::string s) {
	std::vector<std::string> v;
	for (int i = 0; i < s.length() / 32; i++)
	{
		v.push_back(std::string(s.substr((32 * (i)), 32)));
	}
	v.insert(v.end(), 48, "00000000000000000000000000000000");
	return v;
}

// SHR / Shift Right O(n)
std::string SHR(std::string s, int n) {
	std::ostringstream o;
	for (int i = 0; i < s.length() / 32; i++)
	{
		o << std::string(n, '0');
		o << s.substr((32 * i), 32 - n);
	}
	return o.str();
}

// ROT / Right Rotation O(n)
std::string ROT(std::string s, int n) {
	std::ostringstream o;
	for (int i = 0; i < s.length() / 32; i++)
	{
		o << s.substr((32 * (i + 1)) - n, n);
		o << s.substr((32 * i), 32 - n);
	}
	return o.str();
}

// XOR O(n)
std::string XOR(std::string s) {
	std::ostringstream o;
	for (int i = 0; i < s.length() / 3; i++)
	{
		long long x = 0;
		for (int j = 0; j < s.length() / 32; j++)
		{
			x += (s[(j * 32) + i] - 48);
		}
		o << x % 2;
	}
	return o.str();
}

// ADD (O)n
std::string Add(std::string s) {
	long long x = 0;
	for (int i = 0; i < s.length() / 32; i++)
	{
		x += std::bitset<32>(s.substr(32 * i, 32)).to_ulong();
	}
	return std::bitset<32>(x % 4294967296).to_string();
}

// AND (O)n
std::string And(std::string s) {
	std::ostringstream o;
	for (int i = 0; i < s.length() / 2; i++)
	{
		o << 4 % ((s[i] - 47) + (s[i+32] - 48));
	}
	return o.str();
}

// NOT (O)n
std::string Not(std::string s) {
	std::ostringstream o;
	for (int i = 0; i < s.length(); i++)
	{
		o << 1 - (s[i] - 48);
	}
	return o.str();
}

int main()
{
	// Get string as input
	std::string p;
	std::cout << "Enter the string you want to hash: ";
	std::getline(std::cin >> std::ws, p);

	// Initialize Hash Values
	std::string h0 = "01101010000010011110011001100111";
	std::string h1 = "10111011011001111010111010000101";
	std::string h2 = "00111100011011101111001101110010";
	std::string h3 = "10100101010011111111010100111010";
	std::string h4 = "01010001000011100101001001111111";
	std::string h5 = "10011011000001010110100010001100";
	std::string h6 = "00011111100000111101100110101011";
	std::string h7 = "01011011111000001100110100011001";

	// Initialize Rounded Constants
	std::string k[64] = { "01000010100010100010111110011000", "01110001001101110100010010010001", "10110101110000001111101111001111", "11101001101101011101101110100101", "00111001010101101100001001011011", "01011001111100010001000111110001", "10010010001111111000001010100100", "10101011000111000101111011010101", "11011000000001111010101010011000", "00010010100000110101101100000001", "00100100001100011000010110111110", "01010101000011000111110111000011", "01110010101111100101110101110100", "10000000110111101011000111111110", "10011011110111000000011010100111", "11000001100110111111000101110100", "11100100100110110110100111000001", "11101111101111100100011110000110", "00001111110000011001110111000110", "00100100000011001010000111001100", "00101101111010010010110001101111", "01001010011101001000010010101010", "01011100101100001010100111011100", "01110110111110011000100011011010", "10011000001111100101000101010010", "10101000001100011100011001101101", "10110000000000110010011111001000", "10111111010110010111111111000111", "11000110111000000000101111110011", "11010101101001111001000101000111", "00000110110010100110001101010001", "00010100001010010010100101100111", "00100111101101110000101010000101", "00101110000110110010000100111000", "01001101001011000110110111111100", "01010011001110000000110100010011", "01100101000010100111001101010100", "01110110011010100000101010111011", "10000001110000101100100100101110", "10010010011100100010110010000101", "10100010101111111110100010100001", "10101000000110100110011001001011", "11000010010010111000101101110000", "11000111011011000101000110100011", "11010001100100101110100000011001", "11010110100110010000011000100100", "11110100000011100011010110000101", "00010000011010101010000001110000", "00011001101001001100000100010110", "00011110001101110110110000001000", "00100111010010000111011101001100", "00110100101100001011110010110101", "00111001000111000000110010110011", "01001110110110001010101001001010", "01011011100111001100101001001111", "01101000001011100110111111110011", "01110100100011111000001011101110", "01111000101001010110001101101111", "10000100110010000111100000010100", "10001100110001110000001000001000", "10010000101111101111111111111010", "10100100010100000110110011101011", "10111110111110011010001111110111", "11000110011100010111100011110010"};
	
	// Get chunck as Vector
	std::string s = bitFormater(stringToBits(p));

	// Chunkloop
	for (int j = 0; j < s.length() / 512; j++)
	{
		std::vector<std::string> v = ChunckFormater(s.substr(j * 512, 512));

		// Create Message Schedule
		for (int i = 16; i < v.size(); i++)
		{
			v.at(i) = Add(v[i - 16] + (XOR(ROT(v[i - 15], 7) + ROT(v[i - 15], 18) + SHR(v[i - 15], 3))) + v[i - 7] + (XOR(ROT(v[i - 2], 17) + ROT(v[i - 2], 19) + SHR(v[i - 2], 10))));
		}

		// Initizalize a - h
		std::string a = h0;
		std::string b = h1;
		std::string c = h2;
		std::string d = h3;
		std::string e = h4;
		std::string f = h5;
		std::string g = h6;
		std::string h = h7;

		// Compression loop
		for (int i = 0; i < v.size(); i++)
		{
			std::string S1 = (XOR(ROT(e, 6) + ROT(e, 11) + ROT(e, 25)));
			std::string ch = (And(e + f) + (And(Not(e) + g)));
			std::string temp1 = Add(h + S1 + ch + k[i] + v[i]);
			std::string S0 = (XOR(ROT(a, 2) + ROT(a, 13) + ROT(a, 22)));
			std::string maj = (XOR(And(a + b) + And(a + c) + And(b + c)));
			std::string temp2 = Add(S0 + maj);

			h = g;
			g = f;
			f = e;
			e = Add(d + temp1);
			d = c;
			c = b;
			b = a;
			a = Add(temp1 + temp2);
		}
		// Final Values
		h0 = Add(h0 + a);
		h1 = Add(h1 + b);
		h2 = Add(h2 + c);
		h3 = Add(h3 + d);
		h4 = Add(h4 + e);
		h5 = Add(h5 + f);
		h6 = Add(h6 + g);
		h7 = Add(h7 + h);
	}

	// Convert to hexadecimal and append all hash values to create one hash
	std::ostringstream o;
	o << std::hex << std::bitset<32>(h0).to_ullong() << std::bitset<32>(h1).to_ullong() << std::bitset<32>(h2).to_ullong() << std::bitset<32>(h3).to_ullong() << std::bitset<32>(h4).to_ullong() << std::bitset<32>(h5).to_ullong() << std::bitset<32>(h6).to_ullong() << std::bitset<32>(h7).to_ullong();

	std::cout << "\n" << o.str() << "\n";

	system("pause");
}
