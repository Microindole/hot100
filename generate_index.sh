#!/bin/bash

# 定义要输出的文件名
output_file="README.md"

# 写入文件头部信息
echo "# LeetCode Hot 100 笔记目录" > "$output_file"
echo "" >> "$output_file"
echo "这是一个我正在整理的 LeetCode Hot 100 题目笔记列表。" >> "$output_file"
echo "" >> "$output_file"
echo "## 目录" >> "$output_file"

# 循环 hot100 目录下的所有 .md 文件并生成链接
for file in hot100/*.md; do
  # 提取不带路径和扩展名的文件名作为链接标题
  title=$(basename "$file" .md)
  # 将原始文件名（包含空格）用于链接路径
  # Markdown 能够很好地处理带空格的相对路径
  echo "* [$title]($file)" >> "$output_file"
done

echo "" >> "$output_file"
echo "---" >> "$output_file"
# 获取当前日期并写入
current_date=$(date +'%Y/%m/%d')
echo "*列表最后更新于 $current_date*" >> "$output_file"

echo "目录已成功生成到 $output_file"