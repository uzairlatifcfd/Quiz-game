P.F Final Project

This repository contains a C++ trivia quiz program with easy/medium/hard questions across various categories (maths, science, history, sports).

Files
- Main source file.cpp: The main entrypoint for the program.
- easy_*.txt, med_*.txt, hard_*.txt: Question files for different difficulties and categories.
- high_scorers.txt: Leaderboard storage.

How to push this repository to GitHub (Windows PowerShell)
1. Install Git for Windows if needed: https://git-scm.com/download/win
2. Open PowerShell, navigate to the project folder:

    cd "C:\Users\Lio\Desktop\C++ Programs\P. F final project"

3. Configure git user (if not set):

    git config --global user.name "Your Name"
    git config --global user.email "youremail@example.com"

4. Initialize, add, and commit files:

    git init
    git add .
    git commit -m "Initial commit: Add quiz project files"

5. Add your GitHub remote and push to the main branch:

    git branch -M main
    git remote add origin https://github.com/M-Ali05/P.F-final-project.git
    git push -u origin main

If push fails due to authentication, create a Personal Access Token (PAT) in your GitHub settings and run:

    git remote set-url origin https://<username>:<PAT>@github.com/M-Ali05/P.F-final-project.git
    git push -u origin main

Notes
- Replace <username> and <PAT> with your GitHub username and token.
- After the initial push, you can use `git push` to push changes.
- If you use an IDE, you can also use built-in Git integration.
