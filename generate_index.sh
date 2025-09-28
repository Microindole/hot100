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
  
  # 如果标题符合 "数字. " 格式，则在点后插入一个反斜杠进行转义
  # 否则标题保持不变
  if [[ $title =~ ^[0-9]+\. ]]; then
    # 使用sed在数字和点之后插入转义符
    # s/([0-9]+\.)/\\1\\/ 匹配 "数字." 并替换为 "数字.\", 但sed正则复杂
    # 更简单的方法是直接替换第一个点
    title_display="${title/./\\.}"
  else
    title_display="$title"
  fi

  # 将文件路径中的空格替换为 %20，以符合URL标准
  url_encoded_file="${file// /%20}"

  # 使用美化后的标题和编码后的路径创建链接 (注意这里没有反引号了)
  markdown_link="* [$title_display]($url_encoded_file)"

  # 输出拼接好的完整链接
  echo "$markdown_link" >> "$output_file"
done

echo "" >> "$output_file"
echo "---" >> "$output_file"
# 获取当前日期并写入
current_date=$(TZ="Asia/Tokyo" date +'%Y/%m/%d')
echo "*列表最后更新于 $current_date*" >> "$output_file"

echo "目录已成功生成到 $output_file"