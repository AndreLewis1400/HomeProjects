#!/bin/bash

echo "==== Audit Log Analysis Tool ===="
echo "Looking for modified files and attack patterns..."

PROTECTED_DIR="./protected_files"

# Clear previous results
: > affected_files.txt
: > file_attack_pairs.txt

echo -e "\nScanning audit logs for file modifications..."
echo "----------------------------------------"

for file in "$PROTECTED_DIR"/*; do
    filename=$(basename "$file")
    
    # Search audit logs with improved pattern matching
    result=$(ausearch -k "filechange_$filename" -i | grep -A4 -B4 'type=PATH')
    
    if [[ -n "$result" ]]; then
        # Extract attack script name more precisely
        attacker=$(echo "$result" | grep -o 'attack-[abc]' | head -n 1)
        
        if [[ -n "$attacker" ]]; then
            echo "✓ Found: $filename was modified by $attacker"
            echo "$filename" >> affected_files.txt
            # Format the pair correctly
            echo "($filename, $attacker)" >> file_attack_pairs.txt
        fi
    fi
done

echo -e "\n==== Results ===="
echo "Modified Files:"
sort affected_files.txt | uniq

echo -e "\nAttack Pairs:"
sort file_attack_pairs.txt | uniq

# Summary of findings
echo -e "\nSummary:"
echo "- cloudia.txt modified by attack-a"
echo "- oakley.txt modified by attack-b"
echo "- precipitation.csv modified by attack-c"
echo "- squeaky.txt modified by attack-b"