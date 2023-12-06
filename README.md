### Feature Branchを作る前に必ず下記を実行
- git checkout develop
- git pull

### Feature Branchを作成・コードを作成
- git checkout -b feature/{your_name}/{branch_name}
- git add "{updated file}"
- git commit -m "{commit name}"

### Featureの作成が終わったら 
- git checkout develop
- git merge feature/{your_name}/{branch_name}
- git push


