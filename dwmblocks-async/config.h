#ifndef CONFIG_H
#define CONFIG_H

// String used to delimit block outputs in the status.
#define DELIMITER " | "

// Maximum number of Unicode characters that a block can output.
#define MAX_BLOCK_OUTPUT_LENGTH 60

// Control whether blocks are clickable.
#define CLICKABLE_BLOCKS 1

// Control whether a leading delimiter should be prepended to the status.
#define LEADING_DELIMITER 0

// Control whether a trailing delimiter should be appended to the status.
#define TRAILING_DELIMITER 0

// Define blocks for the status feed as X(icon, cmd, interval, signal).
#define BLOCKS(X)                                                             \
    X("Hideout: ", "ip route get 1 | awk '{print $7;exit}'", 60, 0)           \
    X("Ear Bleed: ",                                                          \
      "wpctl get-volume @DEFAULT_AUDIO_SINK@ | awk '{print $2}'", 0, 5)       \
    X("Life Support: ",                                                       \
      "cat /sys/class/power_supply/BAT1/capacity 2>/dev/null | sed 's/$/%/' " \
      "|| echo 'N/A'",                                                        \
      30, 0)                                                                  \
    X("Doomsday: ", "date '+%A, %Y年%-m月%-d日'", 60, 0)

#endif  // CONFIG_H
