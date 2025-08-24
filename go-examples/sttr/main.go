package main

import (
	"github.com/merlotrain/rttr/cmd"
)

func main() {
	cmd.Version = "dev"
	cmd.Execute()
}
