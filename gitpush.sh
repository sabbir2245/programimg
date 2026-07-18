#!/usr/bin/bash

msg="some random msg "

git add . || exit 1
git commit -m "$msg" || exit 1
git push origin main || exit 1

echo "Successfully pushed to GitHub." 