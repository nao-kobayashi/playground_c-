#include <iostream>
#include <vector>

template <typename T>
T sequence(T x, const std::vector<T>& coefficients) {
	T xx = 1;
	T result = 0;
	for (auto i : coefficients) {
		result += i * xx;
		xx *= x;
	}
	return result;
}

template <typename T>
T lagrange(const std::vector<T>& known) {
	T result = 0;

	size_t next = known.size() + 1;
	for (size_t i = 1; i < next; i++) {
		T n = 1;
		T d = 1;
		for (size_t j = 1; j < next; j++) {
			if (i == j)
				continue;

			n *= next - j;
			d *= i - j;
		}

		result += known[i - 1] * (n / d);
	}
	return result;
}

int main() {
	std::vector<long long> coefficients = { +1, -1, +1, -1, +1, -1, +1, -1, +1, -1, +1 };
	long long sum = 0;
	std::vector<long long> data;
	for (long long x = 1; x < (long long)coefficients.size(); x++) {
		data.push_back(sequence(x, coefficients));

		long long next = lagrange(data);
		sum += next;
	}

	std::cout << sum << std::endl;
	return 0;
}
