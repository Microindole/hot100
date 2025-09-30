#!/bin/bash

# 定义要输出的文件名
output_file="README.md"

# --- 第一步：遍历文件，将链接分类存储到数组中 ---

# 声明两个数组，用于存放不同类型的链接
declare -a leetcode_links
declare -a summary_links

# 循环 hot100 目录下的所有 .md 文件
for file in hot100/*.md; do
  # 提取不带路径和扩展名的文件名作为链接标题
  title=$(basename "$file" .md)
  
  # 准备URL编码的文件路径
  url_encoded_file="${file// /%20}"

  # 判断标题是否以 "数字." 开头
  if [[ $title =~ ^[0-9]+\. ]]; then
    # 是 LeetCode 题目，进行转义处理
    title_display="${title/./\\.}"
    markdown_link="* [$title_display]($url_encoded_file)"
    # 将链接添加到 leetcode_links 数组
    leetcode_links+=("$markdown_link")
  else
    # 是知识总结
    title_display="$title"
    markdown_link="* [$title_display]($url_encoded_file)"
    # 将链接添加到 summary_links 数组
    summary_links+=("$markdown_link")
  fi
done

# --- 第二步：将分类好的链接写入 README.md 文件 ---

# 写入文件头部信息
echo "# LeetCode Hot 100 笔记目录" > "$output_file"
echo "" >> "$output_file"
echo "这是一个我正在整理的 LeetCode Hot 100 题目笔记与相关知识总结。" >> "$output_file"
echo "" >> "$output_file"

# 写入 LeetCode 题目笔记部分
echo "## LeetCode 题目笔记" >> "$output_file"
# 将 leetcode_links 数组的内容逐行写入文件
printf "%s\n" "${leetcode_links[@]}" >> "$output_file"
echo "" >> "$output_file"

# 写入基础知识与总结部分
echo "## 基础知识与总结" >> "$output_file"
# 将 summary_links 数组的内容逐行写入文件
printf "%s\n" "${summary_links[@]}" >> "$output_file"
echo "" >> "$output_file"

# 写入文件尾部信息
echo "---" >> "$output_file"
current_date=$(TZ="Asia/Tokyo" date +'%Y/%m/%d')
echo "*列表最后更新于 $current_date*" >> "$output_file"

echo "分类目录已成功生成到 $output_file"