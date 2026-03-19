### 1. 引入头文件和声明

要使用 `std::string`，首先必须包含 `<string>` 头文件。

```c++
#include <string>
#include <iostream> // 用于输出
```

声明和初始化 `string` 对象有多种方式：

```c++
// 1. 创建一个空字符串
std::string s1;

// 2. 使用字符串字面量初始化
std::string s2 = "Hello, World!";
std::string s3("Hello, C++!");

// 3. 使用另一个 string 对象初始化 (拷贝构造)
std::string s4 = s2;
std::string s5(s2);

// 4. 使用字符和数量初始化
std::string s6(5, '#'); // 创建一个包含 5 个 '#' 的字符串 "#####"

// 5. 使用 C++11 的统一初始化语法
std::string s7 {"Modern C++"};
```

------



### 2. 基本操作

#### 获取长度和检查是否为空

- `length()` 或 `size()`: 返回字符串中字符的数量。两者功能完全相同。
- `empty()`: 检查字符串是否为空，返回 `true` 或 `false`。

```c++
std::string s = "Hello";
std::cout << "Length: " << s.length() << std::endl; // 输出: Length: 5

std::string empty_str;
if (empty_str.empty()) {
    std::cout << "The string is empty." << std::endl;
}
```

#### 访问字符

- **使用下标 `[]`**: 最常用的方式，但**不进行边界检查**。如果索引越界，行为是未定义的。
- **使用 `at()` 方法**: 会进行边界检查。如果索引越界，会抛出 `std::out_of_range` 异常，更安全。
- `front()`: 获取第一个字符的引用。
- `back()`: 获取最后一个字符的引用。

```c++
std::string s = "Hello";

char first = s[0];         // 'H'
char last = s[s.length() - 1]; // 'o'

s[0] = 'J'; // 修改字符串，s 现在是 "Jello"
std::cout << s << std::endl;

try {
    char c = s.at(10); // 访问越界，会抛出异常
} catch (const std::out_of_range& e) {
    std::cerr << "Error: " << e.what() << std::endl;
}

std::cout << "First char: " << s.front() << std::endl; // 'J'
std::cout << "Last char: " << s.back() << std::endl;   // 'o'
```

------



### 3. 字符串拼接 (Concatenation)

- **使用 `+` 或 `+=` 运算符**: 最直观的方式。
- **使用 `append()` 方法**: 功能更强大，可以拼接字符串、字符数组或字符的一部分。

```c++
std::string str1 = "Hello";
std::string str2 = " World";

// 使用 +
std::string result1 = str1 + str2; // "Hello World"
std::cout << result1 << std::endl;

// 使用 +=
str1 += str2; // str1 现在是 "Hello World"
std::cout << str1 << std::endl;

// 使用 append()
std::string str3 = "Welcome";
std::string str4 = " to C++";
str3.append(str4); // str3 现在是 "Welcome to C++"
std::cout << str3 << std::endl;
```

------



### 4. 字符串的输入输出

可以直接使用 `std::cin` 和 `std::cout`。

- `std::cin >> s`: 读取字符串，但遇到任何空白字符（空格、制表符、换行符）就会停止。
- `std::getline(std::cin, s)`: 读取一整行，直到遇到换行符为止。这是读取包含空格的字符串的标准方法。

```c++
std::string name;
std::cout << "Enter your first name: ";
std::cin >> name; // 如果输入 "John Doe"，name 只会得到 "John"
std::cout << "Hello, " << name << std::endl;

std::cin.ignore(10000, '\n'); // 清除输入缓冲区，否则 getline 会立即结束

std::string full_line;
std::cout << "Enter a full line: ";
std::getline(std::cin, full_line); // 读取整行
std::cout << "You entered: " << full_line << std::endl;
```

------



### 5. 字符串查找

- `find(substring)`: 在字符串中查找子串第一次出现的位置。如果找到，返回子串的起始索引；如果没找到，返回 `std::string::npos`。
- `rfind(substring)`: 从后往前查找子串第一次出现的位置。
- `find_first_of(chars)`: 查找 `chars` 中任意一个字符在字符串中第一次出现的位置。
- `find_last_of(chars)`: 查找 `chars` 中任意一个字符在字符串中最后一次出现的位置。

```c++
std::string text = "The quick brown fox jumps over the lazy dog.";
std::string keyword = "fox";

size_t pos = text.find(keyword);

if (pos != std::string::npos) {
    std::cout << "'" << keyword << "' found at index: " << pos << std::endl;
} else {
    std::cout << "'" << keyword << "' not found." << std::endl;
}
```

`std::string::npos` 是一个特殊的静态常量，表示“未找到”或“无效位置”。

------



### 6. 子字符串和修改

#### 获取子串

- `substr(start_index, length)`: 返回一个新的 `std::string` 对象，它是原字符串的一部分。

```c++
std::string s = "0123456789";
std::string sub = s.substr(3, 4); // 从索引 3 开始，取 4 个字符
std::cout << sub << std::endl; // 输出 "3456"
```

#### 插入、删除和替换

- `insert(index, str)`: 在指定索引处插入一个字符串。
- `erase(index, count)`: 从指定索引开始，删除 `count` 个字符。
- `replace(index, count, str)`: 将从 `index` 开始的 `count` 个字符替换为 `str`。
- `clear()`: 清空整个字符串，使其变为空字符串。

```c++
std::string s = "This is a test.";

// 插入
s.insert(5, "awesome "); // 在 "is" 后面插入
std::cout << s << std::endl; // "This is awesome a test."

// 删除
s.erase(14, 2); // 删除 " a"
std::cout << s << std::endl; // "This is awesome test."

// 替换
s.replace(0, 4, "That"); // 将 "This" 替换为 "That"
std::cout << s << std::endl; // "That is awesome test."

// 清空
s.clear();
std::cout << "Length after clear: " << s.length() << std::endl; // 0
```

------



### 7. 字符串比较

可以直接使用比较运算符 `==`, `!=`, `<`, `>`, `<=`, `>=`。比较是按字典序进行的。

- `compare()` 方法: 提供更丰富的比较功能，返回值为：
  - `0`: 两个字符串相等。
  - `< 0`: 当前字符串按字典序小于被比较的字符串。
  - `> 0`: 当前字符串按字典序大于被比较的字符串。

```c++
std::string s1 = "Apple";
std::string s2 = "Banana";

if (s1 < s2) {
    std::cout << s1 << " comes before " << s2 << std::endl;
}

if (s1.compare(s2) != 0) {
    std::cout << "The strings are not equal." << std::endl;
}
```