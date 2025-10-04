#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>

// Definition of a singly-linked list node
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {} 
};

// Finds two indices whose values sum up to target
std::vector<int> twoSum(std::vector<int>& nums, int target) {
    for (int n = 0; n < nums.size(); n++) {
        for (int m = n + 1; m < nums.size(); m++) {
            if (nums[m] + nums[n] == target)
                return { n, m };
        }
    }
    return {};
}

// Adds two numbers represented as linked lists
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode* dummyHead = new ListNode(0); // placeholder for result list
    ListNode* current = dummyHead;         // pointer to build the list
    int carry = 0;
	
	// as long as any of the 2 linked List have more elements or carry not zero then continue adding 
    while (l1 != nullptr || l2 != nullptr || carry != 0) {
        int sum = carry;

        if (l1) { sum += l1->val; l1 = l1->next; }
        if (l2) { sum += l2->val; l2 = l2->next; }

        carry = sum / 10;
        current->next = new ListNode(sum % 10);
        current = current->next;
    }

    return dummyHead->next;
}

// Checks if an integer is a palindrome
bool isPalindrome(int x) {
    if (x < 0) return false;
    long long y = 0, z = x;

    while (x != 0) {
        y = y * 10 + x % 10;
        x /= 10;
    }

    return z == y;
}

// Reverses digits of an integer with overflow check
int reverse(int x) {
    long long y = 0;

    while (x != 0) {
        y = y * 10 + x % 10;
        x /= 10;
    }

    if (y > INT_MAX || y < INT_MIN) return 0;
    return y;
}

// Reverses bits of a 32-bit integer
int reverseBits(int n) {
    int x = 0;

    for (int i = 0; i < 32; i++) {
        x <<= 1;
        x |= (n & 1);
        n >>= 1;
    }
    return x;
}

// Returns the length of the longest substring without repeating characters
int lengthOfLongestSubstring(std::string s) {
    std::unordered_set<char> seen;
    int left = 0, maxLength = 0;

    for (int right = 0; right < s.size(); ++right) {
        while (seen.count(s[right])) {
            seen.erase(s[left]);
            left++;
        }
        seen.insert(s[right]);
        maxLength = std::max(maxLength, right - left + 1);
    }

    return maxLength;
}

// Finds the longest common prefix in a vector of strings
std::string longestCommonPrefix(std::vector<std::string>& strs) {
    if (strs.empty()) return "";

    std::string prefix = strs[0];
    for (int i = 1; i < strs.size(); i++) {
        while (strs[i].find(prefix) != 0) {
            prefix = prefix.substr(0, prefix.size() - 1);
            if (prefix.empty()) return "";
        }
    }

    return prefix;
}

// Converts a Roman numeral to an integer
int romanToInt(std::string s) {
    std::unordered_map<char, int> values = {
        {'I', 1}, {'V', 5}, {'X', 10},
        {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000}
    };

    int total = 0;
    for (int i = 0; i < s.size(); i++) {
        if (i + 1 < s.size() && values[s[i]] < values[s[i + 1]])
            total -= values[s[i]];
        else
            total += values[s[i]];
    }

    return total;
}

// Finds median of two sorted arrays
double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
    std::vector<int> merged;
    int i = 0, j = 0;

    while (i < nums1.size() && j < nums2.size()) {
        if (nums1[i] < nums2[j]) merged.push_back(nums1[i++]);
        else merged.push_back(nums2[j++]);
    }

    while (i < nums1.size()) merged.push_back(nums1[i++]);
    while (j < nums2.size()) merged.push_back(nums2[j++]);

    int n = merged.size();
    if (n % 2) return merged[n / 2];
    return (merged[n / 2] + merged[n / 2 - 1]) / 2.0;
}

// Zigzag string conversion
std::string convert(std::string s, int numRows) {
    if (numRows == 1 || s.size() <= numRows) return s;

    std::vector<std::string> rows(numRows);
    int currRow = 0;
    bool goingDown = false;

    for (char c : s) {
        rows[currRow] += c;
        if (currRow == 0 || currRow == rows.size() - 1)
            goingDown = !goingDown;
        currRow += goingDown ? 1 : -1;
    }

    std::string result;
    for (std::string r : rows) result += r;
    return result;
}

// Reverses an array in place
void reverseArray(int* arr, int size) {
    int* start = &arr[0];
    int* end = &arr[size - 1];
    int temp;

    while (start < end) {
        temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

// Computes size of a raw array at compile time
template <typename T, size_t N>
constexpr size_t getSize(T(&)[N]) {
    return N;
}

int main() {
    // Example usage for reverseArray
    int arr1[] = {1, 2, 3, 4, 5};
    size_t size1 = getSize(arr1);
    reverseArray(arr1, size1);
    std::cout << "Reversed array: ";
    for (size_t i = 0; i < size1; i++) std::cout << arr1[i] << " ";
    std::cout << std::endl;

    // Example usage for getSize
    std::cout << "Size of arr1: " << getSize(arr1) << std::endl;

    // Example usage for twoSum
    std::vector<int> nums = {2, 7, 11, 15};
    int target = 9;
    std::vector<int> indices = twoSum(nums, target);
    std::cout << "TwoSum indices for target " << target << ": ";
    for (int idx : indices) std::cout << idx << " ";
    std::cout << std::endl;

    // Example usage for isPalindrome
    int x = 121;
    std::cout << x << " is palindrome? " << (isPalindrome(x) ? "Yes" : "No") << std::endl;

    // Example usage for reverse digits
    int y = 12345;
    std::cout << "Reversed digits of " << y << ": " << reverse(y) << std::endl;

    // Example usage for romanToInt
    std::string roman = "MCMXCIV";
    std::cout << "Roman numeral " << roman << " as integer: " << romanToInt(roman) << std::endl;

    // Example usage for longestCommonPrefix
    std::vector<std::string> words = {"flower", "flow", "flight"};
    std::cout << "Longest common prefix: " << longestCommonPrefix(words) << std::endl;

    // Example usage for lengthOfLongestSubstring
    std::string s = "abcabcbb";
    std::cout << "Length of longest substring without repeating chars in " << s << ": "
              << lengthOfLongestSubstring(s) << std::endl;

    // Example usage for findMedianSortedArrays
    std::vector<int> nums1 = {1, 3};
    std::vector<int> nums2 = {2};
    std::cout << "Median of [1,3] and [2]: " << findMedianSortedArrays(nums1, nums2) << std::endl;

    // Example usage for Zigzag conversion
    std::string zigzag = "PAYPALISHIRING";
    int numRows = 3;
    std::cout << "Zigzag conversion: " << convert(zigzag, numRows) << std::endl;

    return 0;
}
