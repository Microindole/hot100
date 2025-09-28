#!/bin/bash

# --- 配置 ---
output_file="README.md"
base_dir="hot100"
temp_dir="${base_dir}/temp"
problems_dir="${base_dir}/problems"
knowledge_dir="${base_dir}/knowledge"
todo_filename_suffix="-未做未解析.md" # 用于进度统计

# --- 阶段一：自动整理文件 ---
echo "📂 阶段一：开始整理 '${temp_dir}' 文件夹..."

# 确保目标目录存在
mkdir -p "$problems_dir"
mkdir -p "$knowledge_dir"
mkdir -p "$temp_dir"

# 检查 temp 目录是否为空
if [ -z "$(ls -A $temp_dir)" ]; then
    echo "  - '${temp_dir}' 为空，无需整理。"
else
    # 遍历 temp 目录下的所有 .md 文件
    for file in "$temp_dir"/*.md; do
        [ -e "$file" ] || continue # 确保文件存在
        filename=$(basename "$file")

        # 如果文件名包含 "-", 则跳过，不进行整理
        if [[ $filename == *-* ]]; then
            echo "  - 忽略 (进行中): $filename"
            continue
        fi

        # 根据文件名判断是题目还是知识点
        if [[ $filename =~ ^[0-9]+\. ]]; then
            mv "$file" "$problems_dir/"
            echo "  - 归档题目: $filename -> ${problems_dir}/"
        else
            mv "$file" "$knowledge_dir/"
            echo "  - 归档知识点: $filename -> ${knowledge_dir}/"
        fi
    done
fi
echo "✅ 整理完成！"
echo ""


# --- 阶段二：生成 README.md ---
echo "📝 阶段二：开始生成 '${output_file}'..."

# 1. 计算 LeetCode 题目进度
total_problems=0
completed_problems=0
# 只在 problems 目录中统计进度
if [ -d "$problems_dir" ] && [ -n "$(ls -A $problems_dir)" ]; then
    total_problems=$(find "$problems_dir" -maxdepth 1 -name "*.md" | wc -l)
    # 识别带特定后缀的未完成题目
    # 注意：这里的逻辑是，只有在 problems 目录里还带后缀的才算未完成
    unfinished_files=$(find "$problems_dir" -maxdepth 1 -name "*${todo_filename_suffix}" | wc -l)
    completed_problems=$((total_problems - unfinished_files))
fi

# 计算完成率和进度条
if (( total_problems > 0 )); then
  percentage=$((completed_problems * 100 / total_problems))
else
  percentage=0
fi
bar_length=40; filled_length=$((bar_length * percentage / 100)); empty_length=$((bar_length - filled_length))
progress_bar="["; for ((i=0; i<filled_length; i++)); do progress_bar+="="; done; for ((i=0; i<empty_length; i++)); do progress_bar+=" "; done; progress_bar+="]"

# 2. 写入文件头部和进度
cat > "$output_file" << EOL
# LeetCode Hot 100 笔记与知识总结

这是一个我正在整理的 LeetCode Hot 100 题目笔记与相关知识总结。

---

### 学习进度

**已归档题目: ${completed_problems} / ${total_problems} (${percentage}%)**
\`${progress_bar}\`

---
EOL

# 3. 写入 LeetCode 题目笔记
echo "## 🚀 LeetCode 题目笔记" >> "$output_file"
if [ -d "$problems_dir" ] && [ -n "$(ls -A $problems_dir)" ]; then
    # 按数字自然排序并生成列表
    while IFS= read -r file; do
        title=$(basename "$file" .md)
        url_encoded_file="${file// /%20}"
        title_display="${title/./\\.}"
        echo "* [${title_display}](${url_encoded_file})" >> "$output_file"
    done < <(find "$problems_dir" -maxdepth 1 -name "*.md" | sort -V)
else
    echo "暂无已归档的题目笔记。" >> "$output_file"
fi
echo "" >> "$output_file"


# 4. 写入基础知识与总结
echo "## 📚 基础知识与总结" >> "$output_file"
if [ -d "$knowledge_dir" ] && [ -n "$(ls -A $knowledge_dir)" ]; then
    # 按文件名排序并生成列表
    while IFS= read -r file; do
        title=$(basename "$file" .md)
        url_encoded_file="${file// /%20}"
        echo "* [${title}](${url_encoded_file})" >> "$output_file"
    done < <(find "$knowledge_dir" -maxdepth 1 -name "*.md" | sort)
else
    echo "暂无已归档的知识总结。" >> "$output_file"
fi
echo "" >> "$output_file"


# 5. 写入文件尾部
current_date=$(TZ="UTC" date +'%Y-%m-%d %H:%M:%S %Z')
echo "---" >> "$output_file"
echo "*🤖 本目录由脚本自动生成，最后更新于 ${current_date}*" >> "$output_file"

echo "🎉 README.md 已成功更新！"