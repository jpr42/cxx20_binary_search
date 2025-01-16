#include <iostream>
#include <span>
#include <cassert>
#include <array>
#include <optional>
#include <vector>
#include <algorithm>

[[nodiscard]] constexpr std::optional<uint64_t> binary_search(std::span<const uint64_t> data, const uint64_t num)
{
    const auto beginPtr = data.data();
    std::optional<uint64_t> result = std::nullopt;

    while (!data.empty())
    {
        const uint64_t mid = data.size() / 2;
        if (num == data[mid])
        {
            const uint64_t *indexPtr = &data[mid];
            const uint64_t index = (indexPtr - beginPtr);
            result = index;
            data = data.first(mid); // Continue searching in the left half
        }
        else
        {
            data = (num > data[mid]) ? data.last(mid) : data.first(mid);
        }
    }
    return result;
}

int main()
{
    auto CheckFailure = [](bool val) {
        if (val == false)
        {
            std::exit(EXIT_FAILURE);
        }
    };

    // Even amount of elements in array
    {
        std::array<uint64_t, 4> arr1 = {1, 5, 9, 10};

        CheckFailure(binary_search(arr1, 1) == 0);
        CheckFailure(binary_search(arr1, 5) == 1);
        CheckFailure(binary_search(arr1, 9) == 2);
        CheckFailure(binary_search(arr1, 10) == 3);

        std::array<uint64_t, 1000> arr2 = {};
        arr2[999] = 42;
        CheckFailure(binary_search(arr2, 42) == 999);
    }

    // Odd amount of elements in array
    {
        std::vector<uint64_t> arr = {1, 5, 7, 9, 10};

        CheckFailure(binary_search(arr, 1) == 0);
        CheckFailure(binary_search(arr, 5) == 1);
        CheckFailure(binary_search(arr, 7) == 2);
        CheckFailure(binary_search(arr, 9) == 3);
        CheckFailure(binary_search(arr, 10) == 4);
    }

    // Edge cases
    {
        // Size of 0
        CheckFailure(binary_search({}, 10).has_value() == false);

        std::vector<uint64_t> arr = {1};

        // Size of 1
        CheckFailure(binary_search(arr, 1) == 0);
        // Size of 2
        arr.push_back(100);
        CheckFailure(binary_search(arr, 100) == 1);

        // Invalid search
        CheckFailure(binary_search(arr, 2).has_value() == false);
    }

    // Duplicate elements in array
    {
        std::vector<uint64_t> arr = {1, 5, 5, 9, 10};

        CheckFailure(binary_search(arr, 5) == 1); // Ensure it finds the first occurrence
    }

    // Large numbers in array
    {
        std::vector<uint64_t> arr = {1, 5, 9, 10, 1000000000000};

        CheckFailure(binary_search(arr, 1000000000000) == 4);
    }

    std::cout << "Success\n";
}
