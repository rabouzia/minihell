first_flame=$(cat "$1")
second_flame=$(cat "$2")
frames=("$first_flame" "$second_flame")



while true; do
    for frame in "${frames[@]}"; do
        clear
        echo "$frame"
        sleep 0.1
    done
done

