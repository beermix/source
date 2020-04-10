#!/bin/bash
for FILE  in /home/user/ledex-git/*
do
    chown --reference="$FILE" /home/user/ledex/"$(basename "$FILE")"
    chmod --reference="$FILE" /home/user/ledex/"$(basename "$FILE")"
done
