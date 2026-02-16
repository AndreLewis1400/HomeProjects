#!/bin/sh
#
# Commit-msg hook: reject messages like "Remove emojis and user guides from docs"
# Copy to your repo: cp scripts/commit-msg-hook.sh .git/hooks/commit-msg && chmod +x .git/hooks/commit-msg
# Use in MenuMap, Gecko_Guardian, or any repo where you want this rule.
#
msg=$(cat "$1" | tr '[:upper:]' '[:lower:]')
discouraged=0

if echo "$msg" | grep -qE 'remove\s+emoji|remove\s+emojis'; then discouraged=1; fi
if echo "$msg" | grep -qE 'user\s+guides?\s+from\s+doc'; then discouraged=1; fi
if echo "$msg" | grep -qE 'remove\s+emoji.*user\s+guide|user\s+guide.*remove\s+emoji'; then discouraged=1; fi

if [ "$discouraged" -eq 1 ]; then
  echo "Commit rejected: avoid phrases like 'Remove emojis' or 'user guides from docs'." >&2
  echo "Use something like 'Docs: simplify README' or 'Docs: update structure'." >&2
  exit 1
fi
exit 0
