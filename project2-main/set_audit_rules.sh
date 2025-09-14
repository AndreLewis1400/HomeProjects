#!/bin/bash
# filepath: ./set_audit_rules.sh

echo "Setting audit rules for files in ./protected_files..."

cd protected_files || {
    echo "Error: protected_files directory not found."
    exit 1
}

for file in *; do
    full_path=$(realpath "$file")
    echo "Adding audit rule for: $full_path"
    sudo auditctl -w "$full_path" -p w -k "filechange_$file"
done

echo "Done setting audit rules."