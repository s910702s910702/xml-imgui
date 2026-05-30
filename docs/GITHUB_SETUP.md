# GitHub Repository Setup

This local project is ready to publish to GitHub once you choose an owner and repository name.

Suggested repository name:

```txt
xml-imgui
```

## Option A: GitHub CLI

```sh
git init
git add .
git commit -m "Initial xml-imgui infrastructure"
gh repo create xml-imgui --private --source=. --remote=origin --push
```

Use `--public` instead of `--private` if you want an open-source repository.

## Option B: GitHub Web UI

1. Create an empty repository named `xml-imgui`.
2. Do not initialize it with README, license, or `.gitignore`.
3. Run:

```sh
git init
git add .
git commit -m "Initial xml-imgui infrastructure"
git remote add origin git@github.com:<owner>/xml-imgui.git
git push -u origin main
```
