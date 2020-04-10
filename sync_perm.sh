#!/bin/bash
for FILE  in /home/user/ledex-git/*
do
    chown --reference="$FILE" -R /home/user/ledex/"$(basename "$FILE")"
    chmod --reference="$FILE" -R /home/user/ledex/"$(basename "$FILE")"
done
