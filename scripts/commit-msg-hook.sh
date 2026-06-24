#!/bin/sh
#
# Commit-msg hook: reject vague documentation cleanup messages.
# Copy to your repo: cp scripts/commit-msg-hook.sh .git/hooks/commit-msg && chmod +x .git/hooks/commit-msg
# Use in MenuMap, Gecko_Guardian, or any repo where you want this rule.
#
msg=$(cat "$1" | tr '[:upper:]' '[:lower:]')
discouraged=0

if echo "$msg" | grep -qE 'user\s+guides?\s+from\s+doc'; then discouraged=1; fi
if echo "$msg" | grep -qE 'remove\s+.*\s+from\s+(doc|docs|markdown|html)'; then discouraged=1; fi

if [ "$discouraged" -eq 1 ]; then
  echo "Commit rejected: use a specific message like 'Docs: simplify README' or 'Docs: update structure'." >&2
  exit 1
fi
exit 0
