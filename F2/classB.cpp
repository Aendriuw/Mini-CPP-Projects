#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>

class Buffer {
public:
	explicit Buffer(int start) : size_(start) {
		if (size_ < 0) {
			throw std::invalid_argument("start must be greater than 0.");
		}
		buffer_ = static_cast<char*>(calloc(start, 1));

		if (buffer_ == NULL) {
			throw std::bad_alloc();
		}
	}

	~Buffer() {
		free(buffer_);
	}

	bool set_element(int idx, char value) {
		if (idx > size_ - 1 || idx < 0) {
			return false;
		}
		buffer_[idx] = value;

		return true;
	}

	char get_element(int idx) {
		if (idx > size_ - 1 || idx < 0) {
			throw std::invalid_argument("idx must be (0 - size_ - 1).");
		}
		return buffer_[idx];
	}

	Buffer(const Buffer&) = delete;
	Buffer& operator = (const Buffer&) = delete;
private:
	int size_;
	char *buffer_;
};

int main() {
	int start_size;
	std::unique_ptr<Buffer> aux_buffer;

	std::cin >> start_size;

	try {
		aux_buffer = std::make_unique<Buffer>(start_size);
	} catch (const std::invalid_argument&) {
		std::cerr << "Start size must be positive. If you entered a positive value, this means it is too big\n";
		return 1;
	}

	char aux_char = 'A';

	for (int i = 0; i < start_size; i++) {
		aux_buffer->set_element(i, aux_char);
		aux_char++;
	}

	for (int i = start_size - 1; i >= 0; i--) {
		std::cout << aux_buffer->get_element(i) << ' ';
	}
	std::cout << '\n';
}
