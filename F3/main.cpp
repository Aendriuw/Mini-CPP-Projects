#include <charconv>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <filesystem>
#include <memory>
#include <optional>
#include <string>

constexpr std::size_t buf_size = 256;

std::optional<int> parse_line(const char *line, size_t line_size) {
	if (line[0] == '\0' || line[0] == '\n') {
		return std::nullopt;
	}

	if (line[line_size - 1] == '\n') {
		line_size--;
	}

	int number = 0;
	auto ret = std::from_chars(line, line + line_size, number);

	if (ret.ec != std::errc{} || ret.ptr != line + line_size) {
		return std::nullopt;
	}

	return number;
}

int main() {
	std::unique_ptr<std::FILE, int (*)(std::FILE*)> in(std::fopen("in.txt", "r"), &std::fclose);
	std::unique_ptr<std::FILE, int (*)(std::FILE*)> out(std::fopen("out.txt", "w"), &std::fclose);

	if (!in) {
		std::cerr << "No \"in.txt\" file.\n";
		return 1;
	}

	if (!out) {
		std::cerr << "No \"out.txt\" file\n";
		return 2;
	}


	char buffer[buf_size];
	while (std::fgets(buffer, buf_size, in.get())) {
		std::size_t line_size = std::strlen(buffer);
	
		if (buffer[line_size - 1] == '\n' || std::feof(in.get())) {
			auto p = parse_line(buffer, line_size);

			if (p) {
				fprintf(out.get(), "%d\n", *p);
			}
			
			continue;
		}

		while (std::fgets(buffer, buf_size, in.get())) {
			line_size = std::strlen(buffer);
			if (buffer[line_size - 1] == '\n' || std::feof(in.get())) {
				break;
			}
		}
	}
}
