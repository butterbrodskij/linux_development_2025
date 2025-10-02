#!/bin/dash
#тестовая строчка
d=$1

if [ -z "$d" ]; then
    d=0.1
fi

clear
lines=$(tput lines)
cols=$(tput cols)

{
    y=0
    while IFS= read -r line; do
        echo "$line" | grep -o . | {
            x=0
            while IFS= read -r char; do
                if [ "$char" != " " ] && [ $y -ge 0 ] && [ $y -lt $lines ] && [ $x -ge 0 ] && [ $x -lt $cols ]; then
                    printf '%s %d %d\n' "$char" "$x" "$y"
                fi
                x=$((x + 1))
            done
        }
        y=$((y + 1))
    done
} | shuf | while IFS= read -r line; do
    echo "$line" | {
        read -r char x y
        tput cup "$y" "$x"
        printf '%s' "$char"
        sleep "$d"
    }
done

tput cup $((lines - 1)) 0