#!/bin/sh
# Rewrites legacy vague documentation cleanup commit messages for git history rewrites.
msg=$(cat)
first_line=$(echo "$msg" | head -1)

if echo "$first_line" | grep -qiE '^remove .+user guides from docs$'; then
  echo "Docs: update structure"
elif echo "$first_line" | grep -qiE '^update documentation by removing outdated user guides'; then
  echo "Docs: update structure"
elif echo "$first_line" | grep -qiE '^fix 404 error and remove .+ from readme$'; then
  echo "Fix 404 error in README"
elif echo "$first_line" | grep -qiE '^remove .+ from html; remove user guides$'; then
  echo "Docs: clean HTML and remove user guides"
elif echo "$first_line" | grep -qiE '^remove all .+ from markdown docs$'; then
  echo "Docs: update markdown structure"
elif echo "$first_line" | grep -qiE '^sync docs: remove .+ and user guides$'; then
  echo "Sync docs: update structure and remove user guides"
elif [ "$first_line" = "Add FIU coursework assignments and remove guide files" ]; then
  echo "Add FIU coursework assignments"
else
  printf '%s' "$msg"
fi
