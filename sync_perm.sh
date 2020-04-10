#!/bin/bash
for FILE  in /home/user/ledex-git/*
do
    sudo chown --reference="$FILE" -R /home/user/ledex/"$(basename "$FILE")"
    sudo chmod --reference="$FILE" -R /home/user/ledex/"$(basename "$FILE")"
done
