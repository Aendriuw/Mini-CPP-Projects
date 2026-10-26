#include <charconv>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <filesystem>
#include <memory>
#include <optional>
#include <span>
#include <string>
#include <vector>

namespace fs = std::filesystem;

constexpr ssize_t line_limit = 1e8;

class Getline_Buffer {
public:
	~Getline_Buffer() {
		if (buffer_) {
			std::free(buffer_);
		} 
	}

	ssize_t read(std::FILE* in) {
		return getline(&buffer_, &size_, in);
	}

	const char* get_buffer() const {
		return buffer_;
	}

	std::size_t get_size() const {
		return size_;
	}

	Getline_Buffer& operator = (const Getline_Buffer&) = delete;
	Getline_Buffer(const Getline_Buffer&) = delete;
	Getline_Buffer() = default;
private:
	std::size_t size_ = 0;
	char *buffer_ = nullptr;
};

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

void print_bad_line_error(const char *buffer, int line_idx, int reason, ssize_t len) {
	std::cerr << "Bad line " << line_idx << ": " << buffer;
	if (buffer[len - 1] != '\n' || reason == 2) {
		std::cerr << '\n';
	}

	std::cerr << "Reason: ";

	if (reason == 1) {
		std::cerr << "Line too long.\n";
	} else if (reason == 2) {
		std::cerr << "Corrupted line.\n";
	} else {
		std::cerr << "Not an integer.\n";
	}

	std::cerr << '\n';
}

int sum(std::span<const int> v) {
	int sum = 0;

	for (const auto& num : v) {
		sum += num;
	}

	return sum;
}

int main() {
	fs::path in_path = "./in.txt";
	if (!fs::is_regular_file(in_path)) {
		std::cerr << "./in.txt is not a regular file.\n";
		return 4;
	}

	fs::path out_dir = "./out";
	fs::path out_path = "./out/out.txt";

	try {
		fs::create_directories(out_dir);
		fs::permissions(out_dir, fs::perms::owner_read | fs::perms::owner_write | fs::perms::owner_exec, fs::perm_options::replace);
	} catch (const fs::filesystem_error& e) {
		std::cerr << e.what() << '\n';
		return 5;
	}

	std::unique_ptr<std::FILE, int (*)(std::FILE*)> in(std::fopen(in_path.c_str(), "r"), &std::fclose);
	std::unique_ptr<std::FILE, int (*)(std::FILE*)> out(std::fopen(out_path.c_str(), "w"), &std::fclose);

	if (!in) {
		std::cerr << "No \"in.txt\" file.\n";
		return 1;
	}

	if (!out) {
		std::cerr << "No \"out.txt\" file\n";
		return 2;
	}

	try {
		fs::permissions(out_path, fs::perms::owner_read | fs::perms::owner_write, fs::perm_options::replace);
	} catch (const fs::filesystem_error& e) {
		std::cerr << e.what() << '\n';
		return 6;
	}

	std::vector<int> valid_numbers;
	int line_idx = 0;
	ssize_t len;
	Getline_Buffer buf;
	while (true) {
		len = buf.read(in.get());
		if (len == -1) {
			if (std::ferror(in.get())) {
				std::cerr << "Error reading \"in.txt\"\n";
				return 3;
			}

			break;
		}

		if (memchr(buf.get_buffer(), 0, len) || len > line_limit) {
			print_bad_line_error(buf.get_buffer(), line_idx, 2 - (len > line_limit), len);

			line_idx++;
			continue;
		}

		auto ret = parse_line(buf.get_buffer(), len);
		if (ret) {
			std::fprintf(out.get(), "%d\n", *ret);
			valid_numbers.push_back(*ret);
		} else {
			print_bad_line_error(buf.get_buffer(), line_idx, 0, len);
		}

		line_idx++;
	}

	std::cout << "\nSum of valid numbers: " << sum(valid_numbers) << '\n';

	int aux_array[] = {4, 5, 6};
	std::cout << "\nSum of aux array: " << sum(aux_array) << '\n';
}
