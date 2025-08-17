package utils

import (
	"bufio"
	"os"
	"strings"
)

func ReadMultilineInput() string {
	str := make([]string, 0)
	scanner := bufio.NewScanner(os.Stdin)
	empty := 0

	for {
		scanner.Scan()
		text := scanner.Text()
		str = append(str, text)
		if len(text) != 0 {
			empty = 0
		} else {
			empty++
			if empty == 2 {
				break
			}
		}
	}

	return strings.Join(str[:len(str)-2], "\n")
}
