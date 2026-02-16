# Scripts

## Commit message hook

To avoid commit messages like "Remove emojis and user guides from docs" in this repo or in **MenuMap** / **Gecko_Guardian** (or any other clone):

```bash
cp scripts/commit-msg-hook.sh .git/hooks/commit-msg
chmod +x .git/hooks/commit-msg
```

Run the above from the root of each repository (HomeProjects, MenuMap, Gecko_Guardian) where you want the rule applied.
