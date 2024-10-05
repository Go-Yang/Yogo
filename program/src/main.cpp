#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "zstd.h"
#include "nlohmann/json.hpp"

void compress_data(const void* input, size_t input_size, void** output, size_t* output_size) {
    *output_size = ZSTD_compressBound(input_size);
    *output = malloc(*output_size);
    if (*output == NULL) {
        perror("Failed to allocate memory for compressed data");
        exit(EXIT_FAILURE);
    }

    *output_size = ZSTD_compress(*output, *output_size, input, input_size, 1);
    if (ZSTD_isError(*output_size)) {
        fprintf(stderr, "Compression failed: %s\n", ZSTD_getErrorName(*output_size));
        free(*output);
        exit(EXIT_FAILURE);
    }
}

void decompress_data(const void* input, size_t input_size, void** output, size_t output_size) {
    *output = malloc(output_size);
    if (*output == NULL) {
        perror("Failed to allocate memory for decompressed data");
        exit(EXIT_FAILURE);
    }

    size_t decompressed_size = ZSTD_decompress(*output, output_size, input, input_size);
    if (ZSTD_isError(decompressed_size)) {
        fprintf(stderr, "Decompression failed: %s\n", ZSTD_getErrorName(decompressed_size));
        free(*output);
        exit(EXIT_FAILURE);
    }
}

void print_data(const void* data, size_t size) {
    const unsigned char* byte_data = static_cast<const unsigned char*>(data);
    for (size_t i = 0; i < size; ++i) {
        printf("%02X ", byte_data[i]);  // 按位打印
    }
    printf("\n");
}

int main() {
    std::cout << "Hello world!" << std::endl;

    const char* original_data = "This is a test data to compress using Zstandard!";
    size_t original_size = strlen(original_data) + 1; // 包括结束符

    // 打印原始数据
    printf("Original Data: ");
    print_data(original_data, original_size);

    // 压缩
    void* compressed_data = NULL;
    size_t compressed_size = 0;
    compress_data(original_data, original_size, &compressed_data, &compressed_size);

    printf("Original Size: %zu bytes\n", original_size);
    printf("Compressed Size: %zu bytes\n", compressed_size);
    
    // 计算并输出压缩比例
    double compression_ratio = static_cast<double>(original_size) / compressed_size;
    printf("Compression Ratio: %.2f:1\n", compression_ratio);

    // 打印压缩数据
    printf("Compressed Data: ");
    print_data(compressed_data, compressed_size);

    // 解压缩
    void* decompressed_data = NULL;
    decompress_data(compressed_data, compressed_size, &decompressed_data, original_size);

    printf("Decompressed Data: %s\n", (char*)decompressed_data);

    // 清理内存
    free(compressed_data);
    free(decompressed_data);

using json = nlohmann::json;
json j; // 首先创建一个空的json对象
j["pi"] = 3.141;
j["happy"] = true;
j["name"] = "Niels";
j["nothing"] = nullptr;
j["answer"]["everything"] = 42; // 初始化answer对象
j["list"] = { 1, 0, 2 }; // 使用列表初始化的方法对"list"数组初始化
j["object"] = { {"currency", "USD"}, {"value", 42.99} }; // 初始化object对象

float pi = j.at("pi");
std::string name = j.at("name");
int everything = j.at("answer").at("everything");
std::cout << pi << std::endl; // 输出: 3.141
std::cout << name << std::endl; // 输出: Niels
std::cout << everything << std::endl; // 输出: 42
// 打印"list"数组
for(int i=0; i<3; i++)
std::cout << j.at("list").at(i) << std::endl;
// 打印"object"对象中的元素
std::cout << j.at("object").at("currency") << std::endl; // 输出: USD
std::cout << j.at("object").at("value") << std::endl; // 输出: 42.99


    return 0;
}
